#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <drawable.h>
#include <la.h>

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <iostream>

class crosshair : public Drawable
{
public:
    crosshair(GLWidget277* context);
    glm::vec4 pos;
    glm::vec4 up;
    glm::vec4 right;
    void create();
    GLenum drawMode();
};

#endif // CROSSHAIR_H
