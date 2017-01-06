#pragma once

#include "drawable.h"
#include <la.h>

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Cube_red : public Drawable
{
public:
    Cube_red(GLWidget277* context) : Drawable(context){}
    virtual void create();
};
