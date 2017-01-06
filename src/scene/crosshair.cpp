#include "crosshair.h"
#include "chunk.h"


crosshair::crosshair(GLWidget277 *context) :
    Drawable(context), pos(glm::vec4(32, 39, 38, 1)), up(glm::vec4(0, 0.2, 0, 0)), right(glm::vec4(0.2, 0, 0, 0))
{}

void crosshair::create()
{
    GLuint ch_idx[4];
    for (int i = 0; i < 4; i++)
    {
        ch_idx[i] = i;
    }
    glm::vec4 ch_vert_pos[4];
    ch_vert_pos[0] = pos + up;
    ch_vert_pos[1] = pos - up;
    ch_vert_pos[2] = pos + right;
    ch_vert_pos[3] = pos - right;

    glm::vec4 ch_vert_col[4];
    for (int i = 0; i < 4; i++)
    {
        ch_vert_col[i] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    glm::vec4 ch_vert_props[12];

    vector<vboStruct> vboStruct_vert_props;
    vboStruct vertProp;


    for(int i = 0; i< 4; i++){
        ch_vert_props[i*3] = ch_vert_pos[i];
        ch_vert_props[i*3 + 1] = glm::vec4(1,0,0,1);
        ch_vert_props[i*3 + 2] = ch_vert_col[i];

        vertProp.pos = ch_vert_pos[i];
        vertProp.nor = glm::vec4(1,0,0,1);
        vertProp.col = ch_vert_col[i];
        vboStruct_vert_props.push_back(vertProp);

    }

    count = 4;

    // Create a VBO on our GPU and store its handle in bufIdx
    generateIdx();
    // Tell OpenGL that we want to perform subsequent operations on the VBO referred to by bufIdx
    // and that it will be treated as an element array buffer (since it will contain triangle indices)
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    // Pass the data stored in cyl_idx into the bound buffer, reading a number of bytes equal to
    // SPH_IDX_COUNT multiplied by the size of a GLuint. This data is sent to the GPU to be read by shader programs.
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), ch_idx, GL_STATIC_DRAW);

    // The next few sets of function calls are basically the same as above, except bufPos and bufNor are
    // array buffers rather than element array buffers, as they store vertex attributes like position.
//    generatePos();
//    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
//    context->glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), ch_vert_pos, GL_STATIC_DRAW);

//    generateCol();
//    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
//    context->glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), ch_vert_col, GL_STATIC_DRAW);

    generateProps();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufProps);
    //context->glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(glm::vec4), ch_vert_props, GL_STATIC_DRAW);
    context->glBufferData(GL_ARRAY_BUFFER, vboStruct_vert_props.size() * sizeof(vboStruct), vboStruct_vert_props.data(), GL_STATIC_DRAW);


}

GLenum crosshair::drawMode()
{
    return GL_LINES;
}
