#include "skybox.h"
#include "chunk.h"

static const int CUB_IDX_COUNT = 36;
static const int CUB_VERT_COUNT = 24;

Skybox::Skybox(GLWidget277* context): Drawable(context){

}

void Skybox::create()
{
    GLuint cub_idx[CUB_IDX_COUNT];

    std::vector<vboStruct> vboStructProps;

    vboStruct vboProp;


    int idx = 0;
    for(int i = 0; i < 6; i++){
        cub_idx[idx++] = i*4;
        cub_idx[idx++] = i*4+1;
        cub_idx[idx++] = i*4+2;
        cub_idx[idx++] = i*4;
        cub_idx[idx++] = i*4+2;
        cub_idx[idx++] = i*4+3;
    }

    //Front face
    //UR
    vboProp.pos = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,1,0);
    vboProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
    vboProp.UV = glm::vec2(2/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //LR
    vboProp.pos = glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,1,0);
    vboProp.UV = glm::vec2(2/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,1,0);
    vboProp.UV = glm::vec2(1/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //UL
    vboProp.pos = glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,1,0);
    vboProp.UV = glm::vec2(1/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //Right face
    //UR
    vboProp.pos = glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(1,0,0,0);
    vboProp.UV = glm::vec2(3/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LR
    vboProp.pos = glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(1,0,0,0);
    vboProp.UV = glm::vec2(3/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(1,0,0,0);
    vboProp.UV = glm::vec2(2/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //UL
    vboProp.pos = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(1,0,0,0);
    vboProp.UV = glm::vec2(2/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //Left face
    //UR
    vboProp.pos = glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(-1,0,0,0);
    vboProp.UV = glm::vec2(1.0/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LR
    vboProp.pos = glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(-1,0,0,0);
    vboProp.UV = glm::vec2(1.0/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(-1,0,0,0);
    vboProp.UV = glm::vec2(0.0/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //UL
    vboProp.pos = glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(-1,0,0,0);
    vboProp.UV = glm::vec2(0.0/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //Back face
    //UR
    vboProp.pos = glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,-1,0);
    vboProp.UV = glm::vec2(4/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LR
    vboProp.pos = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,-1,0);
    vboProp.UV = glm::vec2(4/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,-1,0);
    vboProp.UV = glm::vec2(3/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //UL
    vboProp.pos = glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,0,-1,0);
    vboProp.UV = glm::vec2(3/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //Top face
    //UR
    vboProp.pos = glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,1,0,0);
    vboProp.UV = glm::vec2(2/4.0,0.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LR
    vboProp.pos = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,1,0,0);
    vboProp.UV = glm::vec2(2/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,1,0,0);
    vboProp.UV = glm::vec2(1/4.0,1/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //UL
    vboProp.pos = glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,1,0,0);
    vboProp.UV = glm::vec2(1/4.0,0.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    //Bottom face
    //UR
    vboProp.pos = glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,-1,0,0);
    vboProp.UV = glm::vec2(2/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LR
    vboProp.pos = glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,-1,0,0);
    vboProp.UV = glm::vec2(2/4.0,3/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //LL
    vboProp.pos = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,-1,0,0);
    vboProp.UV = glm::vec2(1/4.0,3/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);
    //UL
    vboProp.pos = glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
    vboProp.nor = glm::vec4(0,-1,0,0);
    vboProp.UV = glm::vec2(1/4.0,2/3.0);
    vboProp.cosPow = 2;
    vboProp.animate = 0;

    vboStructProps.push_back(vboProp);

    count = CUB_IDX_COUNT;

    // Create a VBO on our GPU and store its handle in bufIdx
    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, CUB_IDX_COUNT * sizeof(GLuint), cub_idx, GL_STATIC_DRAW);


    generateProps();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufProps);
    context->glBufferData(GL_ARRAY_BUFFER, vboStructProps.size() * sizeof(vboStruct), vboStructProps.data(), GL_STATIC_DRAW);
}
