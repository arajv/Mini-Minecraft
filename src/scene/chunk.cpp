#include "chunk.h"

std::vector<std::vector<std::vector<float>>> Chunk::textureCords;
int Chunk::numTextures;
std::vector<float> Chunk::textureAnimate;
std::vector<float> Chunk::textureCosPower;

Chunk::Chunk():Drawable(nullptr)
{}

Chunk::Chunk(GLWidget277* context): Drawable(context){}


void Chunk::create(){

    vector<glm::vec4> cub_vert_props;
    vector<vboStruct> vboStruct_vert_props;
    vector<GLuint> cub_vert_idx;

    int idx = 0;

    for(unordered_map<tuple<int,int,int>, int>::iterator itr = mapBlocks.begin(); itr!= mapBlocks.end(); itr++){
        if (itr->second!=-1 && itr->second!=0){
            tuple<int,int,int> currentTuple = itr->first;
            int blockTypeIndex = (itr->second - 1) * 6;

            int currX = get<0>(currentTuple);
            int currY = get<1>(currentTuple);
            int currZ = get<2>(currentTuple);

            vboStruct vertProp;

            glm::vec4 color;
            if (mapBlocks[make_tuple(currX ,currY,currZ)]==1){
                color = vec4(0.2,1,0.6,0);
            }
            else if (mapBlocks[make_tuple(currX ,currY,currZ)]==10){
                color = vec4(1,0,0,0);
            }
            else if (mapBlocks[make_tuple(currX ,currY,currZ)]==8){
                color = vec4(0,0,1,0);
            }
            else if (mapBlocks[make_tuple(currX ,currY,currZ)]==9){
                color = vec4(1,1,0,0);
            }
            else if (mapBlocks[make_tuple(currX ,currY,currZ)]==11){
                color = vec4(0,0,1,0);
            }

            //Front face

            if(mapBlocks.find(make_tuple(currX ,currY,currZ +1)) == mapBlocks.end() || mapBlocks[make_tuple(currX ,currY,currZ +1)] == -1){

                //UR
                cub_vert_props.push_back(glm::vec4(0.5f + currX, 0.5f + currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f + currX, 0.5f + currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex][0][0],textureCords[blockTypeIndex][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                //LR
                cub_vert_props.push_back(glm::vec4(0.5f + currX, -0.5f + currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f + currX, -0.5f + currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex][1][0],textureCords[blockTypeIndex][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                //LL
                cub_vert_props.push_back(glm::vec4(-0.5f + currX, -0.5f + currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f + currX, -0.5f + currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex][2][0],textureCords[blockTypeIndex][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //UL
                cub_vert_props.push_back(glm::vec4(-0.5f + currX, 0.5f + currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f + currX, 0.5f + currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex][3][0],textureCords[blockTypeIndex][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;


           }

            //Right face
            if(mapBlocks.find(make_tuple(currX+1 ,currY,currZ)) == mapBlocks.end() || mapBlocks[make_tuple(currX+1 ,currY,currZ)] == -1){


                //UR
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+1][0][0],textureCords[blockTypeIndex+1][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //LR
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+1][1][0],textureCords[blockTypeIndex+1][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //LL
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+1][2][0],textureCords[blockTypeIndex+1][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                //UL
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, 0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, 0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+1][3][0],textureCords[blockTypeIndex+1][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);



                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;

            }

            //Left face
            if(mapBlocks.find(make_tuple(currX-1 ,currY,currZ)) == mapBlocks.end() || mapBlocks[make_tuple(currX-1 ,currY,currZ)] == -1){

                //UR
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, 0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(-1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, 0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(-1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+2][0][0],textureCords[blockTypeIndex+2][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //LR
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(-1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(-1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+2][1][0],textureCords[blockTypeIndex+2][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //LL
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(-1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(-1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+2][2][0],textureCords[blockTypeIndex+2][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //UL
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(-1,0,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(-1,0,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+2][3][0],textureCords[blockTypeIndex+2][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);


                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;
            }

            //Back face
            if(mapBlocks.find(make_tuple(currX ,currY,currZ -1)) == mapBlocks.end()|| mapBlocks[make_tuple(currX ,currY,currZ-1)] == -1){

                //UR
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,-1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,-1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+3][0][0],textureCords[blockTypeIndex+3][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //LR
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,-1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,-1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+3][1][0],textureCords[blockTypeIndex+3][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //LL
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,-1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,-1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+3][2][0],textureCords[blockTypeIndex+3][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //UL
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,0,-1,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, 0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,0,-1,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+3][3][0],textureCords[blockTypeIndex+3][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);


                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;
            }

            //Top Face
            if(mapBlocks.find(make_tuple(currX ,currY+1,currZ)) == mapBlocks.end() || mapBlocks[make_tuple(currX ,currY+1,currZ)] == -1){


                //UR
                cub_vert_props.push_back(glm::vec4(0.5f + currX, 0.5f + currY, -0.5f + currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f + currX, 0.5f + currY, -0.5f + currZ, 1.0f);
                vertProp.nor = glm::vec4(0,1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+4][0][0],textureCords[blockTypeIndex+4][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //LR
                cub_vert_props.push_back(glm::vec4(0.5f + currX, 0.5f + currY, 0.5f + currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f + currX, 0.5f + currY, 0.5f + currZ, 1.0f);
                vertProp.nor = glm::vec4(0,1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+4][1][0],textureCords[blockTypeIndex+4][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //LL
                cub_vert_props.push_back(glm::vec4(-0.5f + currX, 0.5f + currY, 0.5f + currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f + currX, 0.5f + currY, 0.5f + currZ, 1.0f);
                vertProp.nor = glm::vec4(0,1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+4][2][0],textureCords[blockTypeIndex+4][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //UL
                cub_vert_props.push_back(glm::vec4(-0.5f + currX, 0.5f + currY, -0.5f + currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,1,0,0));
                cub_vert_props.push_back(color);
                vertProp.pos = glm::vec4(-0.5f + currX, 0.5f + currY, -0.5f + currZ, 1.0f);
                vertProp.nor = glm::vec4(0,1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+4][3][0],textureCords[blockTypeIndex+4][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;
            }

            //Bottom face
            if(mapBlocks.find(make_tuple(currX ,currY-1,currZ)) == mapBlocks.end()|| mapBlocks[make_tuple(currX ,currY-1,currZ)] == -1){


                //UR
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,-1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,-1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+5][0][0],textureCords[blockTypeIndex+5][0][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //LR
                cub_vert_props.push_back(glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,-1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,-1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(1/16.0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+5][1][0],textureCords[blockTypeIndex+5][1][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];
                vboStruct_vert_props.push_back(vertProp);

                //LL
                cub_vert_props.push_back(glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,-1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, -0.5f+ currY, -0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,-1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,1/16.0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+5][2][0],textureCords[blockTypeIndex+5][2][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);

                //UL
                cub_vert_props.push_back( glm::vec4(-0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f));
                cub_vert_props.push_back(glm::vec4(0,-1,0,0));
                cub_vert_props.push_back(color);

                vertProp.pos = glm::vec4(-0.5f+ currX, -0.5f+ currY, 0.5f+ currZ, 1.0f);
                vertProp.nor = glm::vec4(0,-1,0,0);
                vertProp.col = glm::vec4(0.2f, 1.0f, 0.6f, 1);
                //vertProp.UV = glm::vec2(0,0);
                vertProp.UV = glm::vec2(textureCords[blockTypeIndex+5][3][0],textureCords[blockTypeIndex+5][3][1]);
                vertProp.cosPow = textureCosPower[(itr->second - 1)];
                vertProp.animate = textureAnimate[(itr->second - 1)];

                vboStruct_vert_props.push_back(vertProp);


                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+1);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4);
                cub_vert_idx.push_back(idx*4+2);
                cub_vert_idx.push_back(idx*4+3);

                idx++;
            }
        }

    }

    //Calculate the tangent and the bitangent
    for(unsigned int i=0; i< cub_vert_idx.size(); i+=3){
        vboStruct vertProp1 = vboStruct_vert_props[cub_vert_idx[i]];
        vboStruct vertProp2 = vboStruct_vert_props[cub_vert_idx[i+1]];
        vboStruct vertProp3 = vboStruct_vert_props[cub_vert_idx[i+2]];

        glm::vec4 vert1 = vertProp1.pos;
        glm::vec4 vert2 = vertProp2.pos;
        glm::vec4 vert3 = vertProp3.pos;

        glm::vec2 uv1 = vertProp1.UV;
        glm::vec2 uv2 = vertProp2.UV;
        glm::vec2 uv3 = vertProp3.UV;

        glm::vec4 deltaPos1 = vert2-vert1;
        glm::vec4 deltaPos2 = vert3-vert1;

        glm::vec2 deltaUV1 = uv2-uv1;
        glm::vec2 deltaUV2 = uv3-uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec4 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * f;
        glm::vec4 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * f;

        vertProp1.tangent += tangent;
        vertProp2.tangent += tangent;
        vertProp3.tangent += tangent;

        vertProp1.bitangent += bitangent;
        vertProp2.bitangent += bitangent;
        vertProp3.bitangent += bitangent;


        vboStruct_vert_props[cub_vert_idx[i]] = vertProp1;
        vboStruct_vert_props[cub_vert_idx[i+1]] = vertProp2;
        vboStruct_vert_props[cub_vert_idx[i+2]] = vertProp3;

    }

    count = cub_vert_idx.size();

    // Create a VBO on our GPU and store its handle in bufIdx
    generateIdx();
    // Tell OpenGL that we want to perform subsequent operations on the VBO referred to by bufIdx
    // and that it will be treated as an element array buffer (since it will contain triangle indices)
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    // Pass the data stored in cyl_idx into the bound buffer, reading a number of bytes equal to
    // SPH_IDX_COUNT multiplied by the size of a GLuint. This data is sent to the GPU to be read by shader programs.
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), cub_vert_idx.data(), GL_STATIC_DRAW);


    generateProps();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufProps);
    //context->glBufferData(GL_ARRAY_BUFFER, cub_vert_props.size() * sizeof(glm::vec4), cub_vert_props.data(), GL_STATIC_DRAW);
    context->glBufferData(GL_ARRAY_BUFFER, vboStruct_vert_props.size() * sizeof(vboStruct), vboStruct_vert_props.data(), GL_STATIC_DRAW);

}

void Chunk::setMapBlocks(const std::unordered_map<std::tuple<int,int,int>, int>& mapBlocks){
    this->mapBlocks = mapBlocks;
}


int Chunk::removeBlock(glm::vec3 position)
{
    tuple<int, int, int> posCeil = make_tuple(ceil(position.x), ceil(position.y), ceil(position.z));
    int type = mapBlocks.at(posCeil);
    mapBlocks.erase(posCeil);
    return type;
}

void Chunk::addBlock(int type, glm::vec3 position)
{
    vector<tuple<int, int, int>> v;
    v.push_back(make_tuple(ceil(position.x), ceil(position.y), ceil(position.z) - 1));
    v.push_back(make_tuple(ceil(position.x), ceil(position.y) + 1, ceil(position.z)));
    v.push_back(make_tuple(ceil(position.x) - 1, ceil(position.y), ceil(position.z)));
    v.push_back(make_tuple(ceil(position.x) + 1, ceil(position.y), ceil(position.z)));

    for (tuple<int, int, int> t : v)
    {
        if (mapBlocks.count(t) == 0)
        {
            mapBlocks.emplace(t, type);
            break;
        }
    }

}

bool Chunk::findBlock(glm::vec3 position)
{
    tuple<int, int, int> posCeil = make_tuple(ceil(position.x), ceil(position.y), ceil(position.z));
    if (mapBlocks.count(posCeil) == 0)
    {
        return false;
    }
    return true;
}

void Chunk::addWater(glm::vec3 position)
{
    if (position.y < 38)
    {
        tuple<int, int, int> posCeil = make_tuple(ceil(position.x), ceil(position.y), ceil(position.z));
        tuple<int, int, int> posFloor = make_tuple(floor(position.x), floor(position.y), floor(position.z));
        if (findBlock(position))
        {
            mapBlocks[posCeil] = 11;
            mapBlocks[posFloor] = 11;
        }
        else
        {
            mapBlocks.emplace(posCeil, 11);
            mapBlocks.emplace(posFloor, 11);
        }
    }
    else
    {
        removeBlock(position);
    }
}


void Chunk::populateTextureCords(){
    numTextures = 13;

    Chunk::textureCords.resize(numTextures * 6);
      for (int i = 0; i < numTextures * 6; ++i) {
        textureCords[i].resize(4);

        for (int j = 0; j < 4; ++j)
          textureCords[i][j].resize(2);
      }

      //***************************************************************************
      //***************************************************************************
      //Default/Green Block
      //Index 1

      for(int i = (0*6); i<(0*6 + 4)  ; i++){
          textureCords[i][0][0] = 4/16.0;
          textureCords[i][0][1] = 0/16.0;

          textureCords[i][1][0] = 4/16.0;
          textureCords[i][1][1] = 1/16.0;

          textureCords[i][2][0] = 3/16.0;
          textureCords[i][2][1] = 1/16.0;

          textureCords[i][3][0] = 3/16.0;
          textureCords[i][3][1] = 0/16.0;
      }

      //Grass Block Top

      textureCords[(0*6 + 4)][0][0] = 9/16.0;
      textureCords[(0*6 + 4)][0][1] = 2/16.0;

      textureCords[(0*6 + 4)][1][0] = 9/16.0;
      textureCords[(0*6 + 4)][1][1] = 3/16.0;

      textureCords[(0*6 + 4)][2][0] = 8/16.0;
      textureCords[(0*6 + 4)][2][1] = 3/16.0;

      textureCords[(0*6 + 4)][3][0] = 8/16.0;
      textureCords[(0*6 + 4)][3][1] = 2/16.0;

      //Grass Block Bottom

      textureCords[(0*6 + 5)][0][0] = 3/16.0;
      textureCords[(0*6 + 5)][0][1] = 0/16.0;

      textureCords[(0*6 + 5)][1][0] = 3/16.0;
      textureCords[(0*6 + 5)][1][1] = 1/16.0;

      textureCords[(0*6 + 5)][2][0] = 2/16.0;
      textureCords[(0*6 + 5)][2][1] = 1/16.0;

      textureCords[(0*6 + 5)][3][0] = 2/16.0;
      textureCords[(0*6 + 5)][3][1] = 0/16.0;

      //***************************************************************************
      //***************************************************************************
      //Grass Block
      //Index 2

      //Grass Block in order of Front, Rigth, Left, Back,

      for(int i = (1*6); i<(1*6 + 4)  ; i++){
          textureCords[i][0][0] = 4/16.0;
          textureCords[i][0][1] = 0/16.0;

          textureCords[i][1][0] = 4/16.0;
          textureCords[i][1][1] = 1/16.0;

          textureCords[i][2][0] = 3/16.0;
          textureCords[i][2][1] = 1/16.0;

          textureCords[i][3][0] = 3/16.0;
          textureCords[i][3][1] = 0/16.0;
      }

      //Grass Block Top

      textureCords[(1*6 + 4)][0][0] = 9/16.0;
      textureCords[(1*6 + 4)][0][1] = 2/16.0;

      textureCords[(1*6 + 4)][1][0] = 9/16.0;
      textureCords[(1*6 + 4)][1][1] = 3/16.0;

      textureCords[(1*6 + 4)][2][0] = 8/16.0;
      textureCords[(1*6 + 4)][2][1] = 3/16.0;

      textureCords[(1*6 + 4)][3][0] = 8/16.0;
      textureCords[(1*6 + 4)][3][1] = 2/16.0;

      //Grass Block Bottom

      textureCords[(1*6 + 5)][0][0] = 3/16.0;
      textureCords[(1*6 + 5)][0][1] = 0/16.0;

      textureCords[(1*6 + 5)][1][0] = 3/16.0;
      textureCords[(1*6 + 5)][1][1] = 1/16.0;

      textureCords[(1*6 + 5)][2][0] = 2/16.0;
      textureCords[(1*6 + 5)][2][1] = 1/16.0;

      textureCords[(1*6 + 5)][3][0] = 2/16.0;
      textureCords[(1*6 + 5)][3][1] = 0/16.0;


      //***************************************************************************
      //***************************************************************************
      //Dirt Block
      //Index 3

      for(int i = (2*6); i<(2*6 + 6)  ; i++){
          textureCords[i][0][0] = 3/16.0;
          textureCords[i][0][1] = 0/16.0;

          textureCords[i][1][0] = 3/16.0;
          textureCords[i][1][1] = 1/16.0;

          textureCords[i][2][0] = 2/16.0;
          textureCords[i][2][1] = 1/16.0;

          textureCords[i][3][0] = 2/16.0;
          textureCords[i][3][1] = 0/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Wood Block
      //Index 4

      for(int i = (3*6); i<(3*6 + 4)  ; i++){
          textureCords[i][0][0] = 5/16.0;
          textureCords[i][0][1] = 1/16.0;

          textureCords[i][1][0] = 5/16.0;
          textureCords[i][1][1] = 2/16.0;

          textureCords[i][2][0] = 4/16.0;
          textureCords[i][2][1] = 2/16.0;

          textureCords[i][3][0] = 4/16.0;
          textureCords[i][3][1] = 1/16.0;
      }

      for(int i = (3*6 + 4); i<(3*6 + 6)  ; i++){
          textureCords[i][0][0] = 6/16.0;
          textureCords[i][0][1] = 1/16.0;

          textureCords[i][1][0] = 6/16.0;
          textureCords[i][1][1] = 2/16.0;

          textureCords[i][2][0] = 5/16.0;
          textureCords[i][2][1] = 2/16.0;

          textureCords[i][3][0] = 5/16.0;
          textureCords[i][3][1] = 1/16.0;
      }


      //***************************************************************************
      //***************************************************************************
      //Leaf Block
      //Index 5

      for(int i = (4*6); i<(4*6 + 6)  ; i++){
          textureCords[i][0][0] = 6/16.0;
          textureCords[i][0][1] = 3/16.0;

          textureCords[i][1][0] = 6/16.0;
          textureCords[i][1][1] = 4/16.0;

          textureCords[i][2][0] = 5/16.0;
          textureCords[i][2][1] = 4/16.0;

          textureCords[i][3][0] = 5/16.0;
          textureCords[i][3][1] = 3/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Stone Block
      //Index 6

      for(int i = (5*6); i<(5*6 + 6)  ; i++){
          textureCords[i][0][0] = 2/16.0;
          textureCords[i][0][1] = 0/16.0;

          textureCords[i][1][0] = 2/16.0;
          textureCords[i][1][1] = 1/16.0;

          textureCords[i][2][0] = 1/16.0;
          textureCords[i][2][1] = 1/16.0;

          textureCords[i][3][0] = 1/16.0;
          textureCords[i][3][1] = 0/16.0;
      }


      //***************************************************************************
      //***************************************************************************
      //Bedrock Block
      //Index 7

      for(int i = (6*6); i<(6*6 + 6)  ; i++){
          textureCords[i][0][0] = 2/16.0;
          textureCords[i][0][1] = 1/16.0;

          textureCords[i][1][0] = 2/16.0;
          textureCords[i][1][1] = 2/16.0;

          textureCords[i][2][0] = 1/16.0;
          textureCords[i][2][1] = 2/16.0;

          textureCords[i][3][0] = 1/16.0;
          textureCords[i][3][1] = 1/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Coal Block
      //Index 8

      for(int i = (7*6); i<(7*6 + 6)  ; i++){
          textureCords[i][0][0] = 3/16.0;
          textureCords[i][0][1] = 2/16.0;

          textureCords[i][1][0] = 3/16.0;
          textureCords[i][1][1] = 3/16.0;

          textureCords[i][2][0] = 2/16.0;
          textureCords[i][2][1] = 3/16.0;

          textureCords[i][3][0] = 2/16.0;
          textureCords[i][3][1] = 2/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Iron ore Block
      //Index 9

      for(int i = (8*6); i<(8*6 + 6)  ; i++){
          textureCords[i][0][0] = 2/16.0;
          textureCords[i][0][1] = 2/16.0;

          textureCords[i][1][0] = 2/16.0;
          textureCords[i][1][1] = 3/16.0;

          textureCords[i][2][0] = 1/16.0;
          textureCords[i][2][1] = 3/16.0;

          textureCords[i][3][0] = 1/16.0;
          textureCords[i][3][1] = 2/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Lava Block
      //Index 10

      for(int i = (9*6); i<(9*6 + 6)  ; i++){
          textureCords[i][0][0] = 14/16.0;
          textureCords[i][0][1] = 14/16.0;

          textureCords[i][1][0] = 14/16.0;
          textureCords[i][1][1] = 15/16.0;

          textureCords[i][2][0] = 13/16.0;
          textureCords[i][2][1] = 15/16.0;

          textureCords[i][3][0] = 13/16.0;
          textureCords[i][3][1] = 14/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Water Block
      //Index 11

      for(int i = (10*6); i<(10*6 + 6)  ; i++){
          textureCords[i][0][0] = 14/16.0;
          textureCords[i][0][1] = 12/16.0;

          textureCords[i][1][0] = 14/16.0;
          textureCords[i][1][1] = 13/16.0;

          textureCords[i][2][0] = 13/16.0;
          textureCords[i][2][1] = 13/16.0;

          textureCords[i][3][0] = 13/16.0;
          textureCords[i][3][1] = 12/16.0;
      }


      //***************************************************************************
      //***************************************************************************
      //Snow Block
      //Index 12

      for(int i = (11*6); i<(11*6 + 6)  ; i++){
          textureCords[i][0][0] = 3/16.0;
          textureCords[i][0][1] = 4/16.0;

          textureCords[i][1][0] = 3/16.0;
          textureCords[i][1][1] = 5/16.0;

          textureCords[i][2][0] = 2/16.0;
          textureCords[i][2][1] = 5/16.0;

          textureCords[i][3][0] = 2/16.0;
          textureCords[i][3][1] = 4/16.0;
      }

      //***************************************************************************
      //***************************************************************************
      //Sand Block
      //Index 13

      for(int i = (12*6); i<(12*6 + 6)  ; i++){
          textureCords[i][0][0] = 1/16.0;
          textureCords[i][0][1] = 12/16.0;

          textureCords[i][1][0] = 1/16.0;
          textureCords[i][1][1] = 13/16.0;

          textureCords[i][2][0] = 0/16.0;
          textureCords[i][2][1] = 13/16.0;

          textureCords[i][3][0] = 0/16.0;
          textureCords[i][3][1] = 12/16.0;
      }

      //Popualate animation coordinates;
      textureAnimate.resize(numTextures,0);
      textureCosPower.resize(numTextures,2);

      //Animate = 1, Do no animate = 0. By default - do not animate
      textureAnimate[9] = 1;
      textureAnimate[10] = 1;

      //Set the texture shininess score for each block. Range - 1-7

      textureCosPower[0]= 7;
      textureCosPower[1]= 4;
      textureCosPower[2]= 5;
      textureCosPower[3]= 3;
      textureCosPower[4]= 3;
      textureCosPower[5]= 3;
      textureCosPower[6]= 3;
      textureCosPower[7]= 3;
      textureCosPower[8]= 3;
      textureCosPower[9]= 3;
      textureCosPower[10]= 3;
      textureCosPower[11]= 3;
      textureCosPower[12]= 3;


}

std::vector<std::vector<std::vector<float>>> Chunk::getTextureCords(){
    return textureCords;
}
