#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>



MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      geom_cube(this), geom_cube_red(this), skybox(this), geom_ch(this),
      prog_lambert(this), prog_flat(this),prog_text(this),prog_skybox(this),
      gl_camera(), mouseX(0), mouseY(0),time(0),animateIdx(0),footStepsSound("..\\mini_minecraft_m1_3.3\\grass1.wav"),
      isKeyPressed(0),lightDirection(glm::vec4(1,0,0,0)),backCol(0.37f, 0.74f, 1.0f, 1),dayLightFrac(1),
      currType(1)
{
    // Connect the timer to a function so that when the timer ticks the function is executed
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    // Tell the timer to redraw 60 times per second
    timer.start(50);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    flyby = false;
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    geom_cube.destroy();
    geom_cube_red.destroy();
    geom_ch.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.37f, 0.74f, 1.0f, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instance of Cube
    geom_cube.create();
    //geom_cube_red.create();
    geom_ch.create();

    skybox.create();

    // Create and set up the diffuse shader
    prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");
    prog_text.create(":/glsl/texture.vert.glsl", ":/glsl/texture.frag.glsl");
    prog_skybox.create(":/glsl/skyboxtexture.vert.glsl", ":/glsl/skyboxtexture.frag.glsl");

    Chunk::populateTextureCords();


    // Set a color with which to draw geometry since you won't have one
    // defined until you implement the Node classes.
    // This makes your geometry render green.
    // prog_lambert.setGeometryColor(glm::vec4(0,1,0,1));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    //    vao.bind();
    glBindVertexArray(vao);
    curr_centre = make_tuple(scene.dimensions.x/2, scene.dimensions.y/2, scene.dimensions.z/2);
    tuple<int,int,int> centre1 = make_tuple(3*scene.dimensions.x/2, scene.dimensions.y/2, scene.dimensions.z/2);
    tuple<int,int,int> centre2 = make_tuple(scene.dimensions.x/2, scene.dimensions.y/2, 3*scene.dimensions.z/2);
    tuple<int,int,int> centre3 = make_tuple(3*scene.dimensions.x/2, scene.dimensions.y/2, 3*scene.dimensions.z/2);


    scene.make_caves(curr_centre);
    visited_cavecentres[curr_centre] = 1;
    createChunkObjs();

    scene.make_caves(centre1);
    visited_cavecentres[centre1] = 1;
    createChunkObjs();

    scene.make_caves(centre2);
    visited_cavecentres[centre2] = 1;
    createChunkObjs();

    scene.make_caves(centre3);
    visited_cavecentres[centre3] = 1;
    createChunkObjs();



    scene.CreateTestScene();
    createChunkObjs();
    visited_centres[curr_centre] = 1;



    scene.modify_scene(centre1);
    visited_centres[centre1] = 1;
    createChunkObjs();



    scene.modify_scene(centre2);
    visited_centres[centre2] = 1;
    createChunkObjs();



    scene.modify_scene(centre3);
    visited_centres[centre3] = 1;
    createChunkObjs();


    scene.create_biome(curr_centre);
    createChunkObjs();
    scene.create_biome(centre1);
    createChunkObjs();
    scene.create_biome(centre2);
    createChunkObjs();
    scene.create_biome(centre3);
    createChunkObjs();

    //generateSimpleRiver();
    //generateComplexRiver();
    //makeSimpleRiver();
    //makeComplexRiver();

    removedBlocks.insert(make_pair(-1, 0));
    for (int i = 1; i < 14; i++)
    {
        removedBlocks.insert(make_pair(i, 0));
    }
    emit sig_updateInventory(getInventory());
    emit sig_updateInventoryList(getInventoryList());

    //prog_text.setLightDirection(vec4(1,0,0,0));
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    //    gl_camera = Camera(w, h);
    gl_camera = Camera(w, h, glm::vec3(scene.dimensions.x/2, scene.dimensions.y/2 + 17, scene.dimensions.z/2),
                       glm::vec3(scene.dimensions.x/2, scene.dimensions.y/2 + 17, scene.dimensions.z/2 + 1), glm::vec3(0,1,0));
    glm::mat4 viewproj = gl_camera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    prog_lambert.setViewProjMatrix(viewproj);
    prog_flat.setViewProjMatrix(viewproj);
    prog_text.setViewProjMatrix(gl_camera.getViewProj());
    prog_text.activateTexture();

    prog_skybox.setViewProjMatrix(viewproj);
    prog_skybox.activateTexture();


    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
//DO NOT CONSTRUCT YOUR SCENE GRAPH IN THIS FUNCTION!
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec4 skyColor = backCol * (0.3f + dayLightFrac);
    glClearColor(skyColor.r,skyColor.g,skyColor.b, 1);


    prog_skybox.setViewProjMatrix(gl_camera.getViewProj());
    glm::mat4 skyBoxModel = glm::mat4(200.0f);

    skyBoxModel[3][0] = gl_camera.eye.x;
    skyBoxModel[3][1] = gl_camera.eye.y;
    skyBoxModel[3][2] = gl_camera.eye.z;
    skyBoxModel[3][3] = 1;
    prog_skybox.setModelMatrix(skyBoxModel);
    prog_skybox.activateTexture();
    prog_skybox.draw(skybox);


    prog_text.setViewProjMatrix(gl_camera.getViewProj());
    prog_text.activateTexture();
    prog_text.setCameraEye(gl_camera.get_eye());


    GLDrawScene();

    prog_flat.setViewProjMatrix(gl_camera.getViewProj());
    prog_lambert.setViewProjMatrix(gl_camera.getViewProj());
    glDisable(GL_DEPTH_TEST);
    prog_flat.setModelMatrix(glm::mat4(1.0f));
    createCrosshair();
    prog_flat.draw(geom_ch);
    glEnable(GL_DEPTH_TEST);

}

void MyGL::GLDrawScene()
{

    glm::vec3 cameraPos = gl_camera.get_eye();

    int curChunkX = floor(cameraPos[0]/16.0);
    int curChunkY = floor(cameraPos[1]/16.0);
    int curChunkZ = floor(cameraPos[2]/16.0);


    prog_text.setModelMatrix(glm::mat4(1.0f));
    for(unordered_map<tuple<int,int,int>, Chunk>::iterator itr = chunkObjMap.begin(); itr!= chunkObjMap.end(); itr++){
        tuple<int,int,int> curTuple = itr->first;
        if(!(abs(curChunkX - get<0>(curTuple)) >=32 || abs(curChunkY - get<1>(curTuple))>=32||abs(curChunkZ - get<2>(curTuple)) >=32)){
            chunkObj = itr->second;
            prog_text.draw(chunkObj);
        }

    }

}

void MyGL::createCrosshair()
{
    geom_ch.pos = glm::vec4(gl_camera.eye + (gl_camera.look * 7.0f),1);
    geom_ch.up = glm::vec4(gl_camera.up * 0.2f, 0);
    geom_ch.right = glm::vec4(gl_camera.right * 0.2f, 0);
    geom_ch.create();
}

void MyGL::keyPressEvent(QKeyEvent *e)
{

    float amount = 2.0f;
    float amount2 = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used, but I really dislike their
    // syntax so I chose to be lazy and use a long
    // chain of if statements instead
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        gl_camera.RotateAboutUp(-amount2);
    } else if (e->key() == Qt::Key_Left) {
        gl_camera.RotateAboutUp(amount2);
    } else if (e->key() == Qt::Key_Up) {
        gl_camera.RotateAboutRight(-amount2);
    } else if (e->key() == Qt::Key_Down) {
        gl_camera.RotateAboutRight(amount2);
    } else if (e->key() == Qt::Key_1) {
        gl_camera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        gl_camera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        checkCollision(gl_camera.look, amount);
        gl_camera.TranslateAlongLook(amount);
        if(!e->isAutoRepeat() ){
            footStepsSound.setLoops(QSound::Infinite);
            footStepsSound.play();
            isKeyPressed=1;
        }

    } else if (e->key() == Qt::Key_S) {
        checkCollision(gl_camera.look, -amount);
        gl_camera.TranslateAlongLook(-amount);
        if(!e->isAutoRepeat()){
            footStepsSound.setLoops(QSound::Infinite);
            footStepsSound.play();
            isKeyPressed=1;
        }
    } else if (e->key() == Qt::Key_D) {
        checkCollision(gl_camera.right, amount);
        gl_camera.TranslateAlongRight(amount);
        if(!e->isAutoRepeat()){
            footStepsSound.setLoops(QSound::Infinite);
            footStepsSound.play();
            isKeyPressed=1;
        }
    } else if (e->key() == Qt::Key_A) {
        checkCollision(gl_camera.right, -amount);
        gl_camera.TranslateAlongRight(-amount);
        if(!e->isAutoRepeat()){
            footStepsSound.setLoops(QSound::Infinite);
            footStepsSound.play();
            isKeyPressed=1;
        }
    } else if (e->key() == Qt::Key_Q) {
        checkCollision(gl_camera.up, -amount);
        gl_camera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        checkCollision(gl_camera.up, amount);
        gl_camera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        gl_camera = Camera(this->width(), this->height());
    } else if (e->key() == Qt::Key_F) {
        toggleFlyby();
    } else if (e->key() == Qt::Key_K) {
        generateSimpleRiver();
    }

    gl_camera.RecomputeAttributes();
    //update();
    updateScene();

    update();  // Calls paintGL, among other things
}

void MyGL::keyReleaseEvent(QKeyEvent *e){
    if(!e->isAutoRepeat() ){
        footStepsSound.stop();
        isKeyPressed =0;
    }
}

void MyGL::mouseMoveEvent(QMouseEvent *m)
{
    mouseX = m->localPos().x();
    mouseY = m->localPos().y();
}

void MyGL::mousePressEvent(QMouseEvent *m)
{
    bool cubeFoundForEye = false;
    glm::vec3 pos = glm::vec3(0.0f);
    vector<glm::vec3> points = gl_camera.Raycast(0.0f, 0.0f);
    for (glm::vec3 point : points)
    {
        if (!cubeFoundForEye)
        {
            if (getSubmap(point) != nullptr && getSubmap(point)->findBlock(point))
            {
                pos = point;
                cubeFoundForEye = true;
            }
        }
    }

    if (m->button() == Qt::LeftButton)
    {
        if (getSubmap(pos) != nullptr && cubeFoundForEye)
        {
            removeCube(getSubmap(pos), pos);
        }
    }
    else if (m->button() == Qt::RightButton)
    {
        if (cubeFoundForEye)
        {
            addCube(getSubmap(pos), pos);
        }
    }
}

void MyGL::updateScene(){
    int margin = 25;
    vec3 curr_pos = gl_camera.get_eye();
    tuple<int,int,int> new_centre = curr_centre;
    bool cond1 = (int(round(curr_pos[0]))-get<0>(curr_centre))> scene.dimensions.x/2 - margin;
    bool cond2 = (get<0>(curr_centre)-int(round(curr_pos[0])))> scene.dimensions.x/2 - margin;
    bool cond3 = (int(round(curr_pos[2]))-get<2>(curr_centre))> scene.dimensions.z/2 - margin;
    bool cond4 = (get<2>(curr_centre)-int(round(curr_pos[2])))> scene.dimensions.z/2 - margin;
    bool cond5 = cond1 && cond3;
    bool cond6 = cond1 && cond4;
    bool cond7 = cond2 && cond3;
    bool cond8 = cond2 && cond4;

    //bool cond9 = int(round(curr_pos[1]))<32;

    //    if (cond9){
    //        if(!visited_cavecentres[curr_centre]){
    //            scene.make_caves(curr_centre);
    //            visited_cavecentres[curr_centre]=1;
    //            createChunkObjs();

    //        }
    //    }

    //    if (!cond9){
    //        if(!visited_centres[curr_centre]){
    //            scene.modify_scene(curr_centre);
    //            visited_centres[curr_centre]=1;
    //            createChunkObjs();
    //        }
    //    }





    if (cond1){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre);
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }

    if (cond2){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre);
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }

    if (cond3){
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        get<0>(new_centre) = get<0>(curr_centre);
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();
        }
    }

    if (cond4){
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        get<0>(new_centre) = get<0>(curr_centre);
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }
    if (cond5){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }
    if (cond6){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }
    if (cond7){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }
    if (cond8){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        if(!visited_cavecentres[new_centre]){
            scene.make_caves(new_centre);
            visited_cavecentres[new_centre] = 1;
            createChunkObjs();

        }
    }

    if (cond1){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre);
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }

    if (cond2){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre);
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }

    if (cond3){
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        get<0>(new_centre) = get<0>(curr_centre);
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }

    if (cond4){
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        get<0>(new_centre) = get<0>(curr_centre);
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }
    if (cond5){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }
    if (cond6){
        get<0>(new_centre) = get<0>(curr_centre) + scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }
    if (cond7){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) + scene.dimensions.z;
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }
    if (cond8){
        get<0>(new_centre) = get<0>(curr_centre) - scene.dimensions.x;
        get<2>(new_centre) = get<2>(curr_centre) - scene.dimensions.z;
        if(!visited_centres[new_centre]){
            scene.create_biome(new_centre);
            createChunkObjs();
            scene.modify_scene(new_centre);
            visited_centres[new_centre] = 1;
            createChunkObjs();
            //            makeSimpleRiver();
            //            makeComplexRiver();
        }
    }

    get<0>(curr_centre) = scene.dimensions.x/2 + int(scene.dimensions.x*floor(curr_pos[0]/scene.dimensions.x));
    get<2>(curr_centre) = scene.dimensions.z/2 + int(scene.dimensions.z*floor(curr_pos[2]/scene.dimensions.z));

}

void MyGL::timerUpdate()
{
    mouseListener();
    if (!flyby && !onGround() && gl_camera.eye.y > 34)
    {
        applyGravity();
    }

    time = (time + 1) % 100000;

    if(time % 1 == 0){

        float angleDeg = (1 * time) % 360;

        glm::vec4 newLightDirection ;

        newLightDirection =  glm::rotate( glm::mat4(1.0f),glm::radians(angleDeg), glm::vec3(0,0,1)) * lightDirection;

        prog_text.setTimeVar(time / 1);
        prog_text.setLightDirection(newLightDirection);

        prog_skybox.setTimeVar(time / 1);
        prog_skybox.setLightDirection(newLightDirection);

        float lightAngle = angleDeg;

        lightAngle = glm::radians(lightAngle);

        dayLightFrac = (sin(lightAngle));

        update();
    }
}

void MyGL::mouseListener()
{
    if (mouseY <= 20 && mouseX >= 40 && mouseX<= this->width() - 40) {
        gl_camera.RotateAboutRight(2.0f);
    }
    else if (mouseY >= this->height() - 20 && mouseX >= 40 && mouseX<= this->width() - 40) {
        gl_camera.RotateAboutRight(-2.0f);
    }
    else if (mouseX <= 40 && mouseY >= 20 && mouseY<= this->height() - 20) {
        gl_camera.RotateAboutUp(2.0f);
    }
    else if (mouseX >= this->width() - 40 && mouseY >= 20 && mouseY<= this->height() - 20) {
        gl_camera.RotateAboutUp(-2.0f);
    }
    else if (mouseX <= 20 && mouseY <= 20) {
        gl_camera.RotateAboutRight(2.0f);
        gl_camera.RotateAboutUp(2.0f);
    }
    else if (mouseX >= this->width() - 40 && mouseY <= 20) {
        gl_camera.RotateAboutRight(2.0f);
        gl_camera.RotateAboutUp(-2.0f);
    }
    else if (mouseX <= 40 && mouseY >= this->height() - 20) {
        gl_camera.RotateAboutRight(-2.0f);
        gl_camera.RotateAboutUp(2.0f);
    }
    else if (mouseX >= this->width() - 40 && mouseY >= this->height() - 20) {
        gl_camera.RotateAboutRight(-2.0f);
        gl_camera.RotateAboutUp(-2.0f);
    }

    update();
}

QString MyGL::getInventory()
{
    bool empty = true;
    QString text = "";
    for (pair<int, int> p : removedBlocks)
    {
        if (p.first == -1)
        {
            continue;
        }
        if (p.second > 0)
        {
            if (empty == true)
            {
                currType = p.first;
            }
            empty = false;
            text+="\n" + getNameOfType(p.first) + " x" + QString::number(p.second);
        }
    }

    if (empty)
    {
        return "No blocks available.";
    }
    return text;
}

QStringList MyGL::getInventoryList()
{
    bool empty = true;
    QStringList textList;
    for (pair<int, int> p : removedBlocks)
    {
        if (p.first == -1)
        {
            continue;
        }
        if (p.second > 0)
        {
            empty = false;
            textList.append(getNameOfType(p.first));
        }
    }

    if (empty)
    {
        textList.append("empty");
        return textList;
    }
    return textList;
}

QString MyGL::getNameOfType(int type)
{
    if (type == -1)
        return "empty";
    else if (type == 1)
        return "green";
    else if (type == 2)
        return "grass";
    else if (type == 3)
        return "dirt";
    else if (type == 4)
        return "wood";
    else if (type == 5)
        return "leaf";
    else if (type == 6)
        return "stone";
    else if (type == 7)
        return "bedrock";
    else if (type == 8)
        return "coal";
    else if (type == 9)
        return "iron ore";
    else if (type == 10)
        return "lava";
    else if (type == 11)
        return "water";
    else if (type == 12)
        return "snow";
    else if (type == 13)
        return "sand";
    return "invalid block";
}

int MyGL::getTypeOfName(QString name)
{
    if (name == "empty")
        return -1;
    else if (name =="green")
        return 1;
    else if (name =="grass")
        return 2;
    else if (name =="dirt")
        return 3;
    else if (name =="wood")
        return 4;
    else if (name =="leaf")
        return 5;
    else if (name =="stone")
        return 6;
    else if (name =="bedrock")
        return 7;
    else if (name =="coal")
        return 8;
    else if (name =="iron ore")
        return 9;
    else if (name =="lava")
        return 10;
    else if (name =="water")
        return 11;
    else if (name =="snow")
        return 12;
    else if (name =="sand")
        return 13;
    return  -1;
}

void MyGL::slot_updateCurrType(QString name)
{
    currType = getTypeOfName(name);
}

void MyGL::addCube(Chunk *submap, glm::vec3 pos)
{
    if (submap->findBlock(pos) && removedBlocks[currType] > 0)
    {
        submap->addBlock(currType, pos);
        removedBlocks[currType]--;
    }
    submap->create();
    emit sig_updateInventory(getInventory());
    emit sig_updateInventoryList(getInventoryList());
    update();
}

void MyGL::removeCube(Chunk *submap, glm::vec3 pos)
{
    if (submap->findBlock(pos))
    {
        int type = submap->removeBlock(pos);
        removedBlocks[type]++;
    }
    submap->create();
    emit sig_updateInventory(getInventory());
    emit sig_updateInventoryList(getInventoryList());
    update();
}

void MyGL::createChunkObjs(){
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> >& chunks = scene.getChunks();

    for(unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> >::iterator itr = chunks.begin(); itr!= chunks.end(); itr++){


        tuple<int,int,int> currentTuple = itr->first;
        unordered_map<tuple<int,int,int>,int> currentSubMap = itr->second;


        if (chunkObjMap.find(currentTuple)!=chunkObjMap.end()){
            unordered_map<tuple<int,int,int>,int> existingSubMap = chunkObjMap[currentTuple].mapBlocks;
            for(unordered_map< tuple<int,int,int>, int> ::iterator itr2 = currentSubMap.begin(); itr2!= currentSubMap.end(); itr2++){
                existingSubMap[itr2->first] = itr2->second;
            }
            Chunk& tempChunkObj = chunkObjMap[currentTuple];
            //tempChunkObj.destroy();
            tempChunkObj.setMapBlocks(existingSubMap);
            tempChunkObj.create();
            //chunkObjMap[currentTuple] = tempChunkObj;

        }
        else{
            Chunk tempChunkObj = Chunk(this);
            tempChunkObj.setMapBlocks(currentSubMap);
            tempChunkObj.create();
            chunkObjMap[currentTuple] = tempChunkObj;
        }


    }

}

Chunk* MyGL::getSubmap(glm::vec3 pos)
{
    tuple<int, int, int> chunkNumber = make_tuple(floor(pos.x/16.0), floor(pos.y/16.0), floor(pos.z/16.0));
    if (chunkObjMap.count(chunkNumber) != 0)
    {
        return &chunkObjMap.at(chunkNumber);
    }
    return nullptr;
}

void MyGL::checkCollision(glm::vec3 direction, float amt) {
    if (flyby)
    {
        return;
    }
    glm::vec3 translate = direction * amt;
    glm::vec3 newPos = gl_camera.eye + translate;
    for (int i = 0; i < 3; i++)
    {
        if ((getSubmap(newPos) == nullptr || getSubmap(newPos)->findBlock(newPos) || !onGround()))
        {
            gl_camera.isColliding = true;
            break;
        }
        newPos+=translate;
    }
}

bool MyGL::onGround() {
    glm::vec3 ground = gl_camera.eye - glm::vec3(0.0f, 2.0f, 0.0f);
    return getSubmap(ground) != nullptr && getSubmap(ground)->findBlock(ground);
}

void MyGL::applyGravity() {
    gl_camera.TranslateAlongUp(-0.5f);
}

void MyGL::toggleFlyby()
{
    flyby = !flyby;
}

void MyGL::generateSimpleRiver()
{
    SimpleRiver r = SimpleRiver();
    r.generateRiver(glm::vec2(0, 30), 128, 0);
    simpleRiver = r.coordinates;
}

void MyGL::generateComplexRiver()
{
    ComplexRiver r = ComplexRiver();
    r.generateRiver(glm::vec2(20, 30), 128, 0.4);
    complexRiver = r.coordinates;
}

void MyGL::makeSimpleRiver()
{
    for (int i = 33; i < 50; i++)
    {
        for (glm::vec2 rc : simpleRiver)
        {
            glm::vec3 riverpos = glm::vec3(rc.x, i, rc.y);

            Chunk* submap = getSubmap(riverpos);
            if (submap != nullptr)
            {
                submap->addWater(riverpos);
                submap->create();
            }
        }
    }
    //update();
}

void MyGL::makeComplexRiver()
{
    for (int i = 0; i < 50; i++)
    {
        for (glm::vec2 rc : complexRiver)
        {
            glm::vec3 riverpos = glm::vec3(rc.x, i, rc.y);

            Chunk* submap = getSubmap(riverpos);
            if (submap != nullptr)
            {
                submap->addWater(riverpos);
                submap->create();
            }
        }
    }
    //update();
}
