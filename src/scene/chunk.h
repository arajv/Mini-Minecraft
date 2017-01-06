#ifndef CHUNK_H
#define CHUNK_H

#include "drawable.h"
#include <la.h>

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <iostream>

#include <tuple>
#include <hashtuple.h>
#include <unordered_map>

using namespace std;
using namespace glm;

struct vboStruct{
    glm::vec4 pos;
    glm::vec4 nor;
    glm::vec4 col;
    glm::vec2 UV;

    glm::vec4 tangent;
    glm::vec4 bitangent;

    float cosPow;
    float animate;

};



class Chunk : public Drawable
{

public:

    static int numTextures;

    static std::vector<std::vector<std::vector<float>>> textureCords;
    static std::vector<float> textureCosPower;
    static std::vector<float> textureAnimate;

    Chunk();
    Chunk(GLWidget277* context);
    virtual void create();
    std::unordered_map<std::tuple<int,int,int>, int> mapBlocks;

    int removeBlock(glm::vec3 position);
    void addBlock(int type, glm::vec3 position);
    bool findBlock(glm::vec3 position);

    void setMapBlocks(const std::unordered_map<std::tuple<int,int,int>, int>& mapBlocks);

    void addWater(glm::vec3 position);

    static void populateTextureCords();
    static std::vector<std::vector<std::vector<float>>> getTextureCords();

};

#endif // CHUNK_H
