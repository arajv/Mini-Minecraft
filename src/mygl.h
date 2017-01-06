#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cube.h>
#include <scene/cube_red.h>
#include <scene/crosshair.h>
#include "camera.h"
#include <scene/scene.h>
#include <scene/chunk.h>
#include <unordered_map>
#include <hashtuple.h>

#include <tuple>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QMouseEvent>

#include <simpleriver.h>
#include <complexriver.h>
#include <scene/skybox.h>

#include <QSound>

class MyGL
    : public GLWidget277
{
    Q_OBJECT
private:
    Cube geom_cube;// The instance of a unit cube we can use to render any cube. Should NOT be used in final version of your project.
    Cube_red geom_cube_red;
    Skybox skybox;
    crosshair geom_ch;
    ShaderProgram prog_lambert;// A shader program that uses lambertian reflection
    ShaderProgram prog_flat;// A shader program that uses "flat" reflection (no shadowing at all)
    ShaderProgram prog_text;
    ShaderProgram prog_skybox;

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera gl_camera;
    Scene scene;
    tuple<int,int,int> curr_centre;
    unordered_map <tuple<int,int,int>,int> visited_centres;
    unordered_map <tuple<int,int,int>,int> visited_cavecentres;
    /// Timer linked to timerUpdate(). Fires approx. 60 times per second
    QTimer timer;
    enum box {empty = -1, green = 1, grass = 2, dirt = 3, wood = 4, leaf = 5, stone = 6, bedrock = 7, coal = 8, iron_ore = 9, lava = 10, water = 11, snow = 12, sand = 13};

    unordered_map<tuple<int,int,int>, Chunk> chunkObjMap;

    Chunk chunkObj;

    int mouseX;
    int mouseY;

    vector<glm::vec2> simpleRiver;
    vector<glm::vec2> complexRiver;

    map<int, int> removedBlocks;
    int currType;

    bool flyby;

    int time;
    int animateIdx;

    QSound footStepsSound;
    int isKeyPressed;

    glm::vec4 lightDirection;

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void GLDrawScene();
    void updateScene();

    void createChunkObjs();


    void createCrosshair();

    void mouseListener();

    void addCube(Chunk *submap, glm::vec3 pos);
    void removeCube(Chunk* submap, glm::vec3 pos);

    Chunk* getSubmap(glm::vec3 pos);
    void checkCollision(glm::vec3 direction, float amt);

    bool onGround();
    void applyGravity();

    void toggleFlyby();

    void generateSimpleRiver();
    void extendSimpleRiver(int dir);

    void generateComplexRiver();
    void extendComplexRiver();

    void makeSimpleRiver();
    void makeComplexRiver();

    QString getInventory();
    QStringList getInventoryList();
    QString getNameOfType(int type);
    int getTypeOfName(QString name);
    glm::vec4 backCol;
    float dayLightFrac;

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent *m);
    void keyReleaseEvent(QKeyEvent *e);

private slots:
    /// Slot that gets called ~60 times per second
    virtual void timerUpdate();
public slots:

    void slot_updateCurrType(QString name);
signals:
    void sig_updateInventory(QString);
    void sig_updateInventoryList(QStringList);
};


#endif // MYGL_H
