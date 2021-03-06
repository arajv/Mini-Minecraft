#include "shaderprogram.h"
#include <QFile>
#include <QStringBuilder>

#include <SOIL.h>
#include "scene/chunk.h"


ShaderProgram::ShaderProgram(GLWidget277 *context)
    : vertShader(), fragShader(), prog(),
      attrPos(-1), attrNor(-1), attrCol(-1),attrUV(-1),attrTangent(-1),attrBitangent(-1),attrCosPow(-1), attrAnimate(-1),
      unifModel(-1), unifModelInvTr(-1), unifViewProj(-1), unifColor(-1), unifSampler(-1),  unifNMapSampler(-1), unifCameraEye(-1),unifSkyDaySampler(-1),unifSkyNightSampler(-1),
      unifTime(-1),unifLightDirection(-1),
      context(context)
{}

void ShaderProgram::create(const char *vertfile, const char *fragfile)
{
    // Allocate space on our GPU for a vertex shader and a fragment shader and a shader program to manage the two
    vertShader = context->glCreateShader(GL_VERTEX_SHADER);
    fragShader = context->glCreateShader(GL_FRAGMENT_SHADER);
    prog = context->glCreateProgram();
    // Get the body of text stored in our two .glsl files
    QString qVertSource = qTextFileRead(vertfile);
    QString qFragSource = qTextFileRead(fragfile);

    char* vertSource = new char[qVertSource.size()+1];
    strcpy(vertSource, qVertSource.toStdString().c_str());
    char* fragSource = new char[qFragSource.size()+1];
    strcpy(fragSource, qFragSource.toStdString().c_str());


    // Send the shader text to OpenGL and store it in the shaders specified by the handles vertShader and fragShader
    context->glShaderSource(vertShader, 1, &vertSource, 0);
    context->glShaderSource(fragShader, 1, &fragSource, 0);
    // Tell OpenGL to compile the shader text stored above
    context->glCompileShader(vertShader);
    context->glCompileShader(fragShader);
    // Check if everything compiled OK
    GLint compiled;
    context->glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(vertShader);
    }
    context->glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(fragShader);
    }

    // Tell prog that it manages these particular vertex and fragment shaders
    context->glAttachShader(prog, vertShader);
    context->glAttachShader(prog, fragShader);
    context->glLinkProgram(prog);

    // Check for linking success
    GLint linked;
    context->glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) {
        printLinkInfoLog(prog);
    }

    // Get the handles to the variables stored in our shaders
    // See shaderprogram.h for more information about these variables

    attrPos = context->glGetAttribLocation(prog, "vs_Pos");
    attrNor = context->glGetAttribLocation(prog, "vs_Nor");
    attrCol = context->glGetAttribLocation(prog, "vs_Col");
    attrUV = context->glGetAttribLocation(prog, "vs_UV");
    attrTangent = context->glGetAttribLocation(prog, "vs_Tangent");
    attrBitangent = context->glGetAttribLocation(prog,"vs_Bitangent");
    attrCosPow = context->glGetAttribLocation(prog,"vs_CosPow");
    attrAnimate = context->glGetAttribLocation(prog,"vs_Animate");


    unifModel      = context->glGetUniformLocation(prog, "u_Model");
    unifModelInvTr = context->glGetUniformLocation(prog, "u_ModelInvTr");
    unifViewProj   = context->glGetUniformLocation(prog, "u_ViewProj");
    unifColor      = context->glGetUniformLocation(prog, "u_Color");
    unifSampler    = context->glGetUniformLocation(prog, "u_Sampler");
    unifNMapSampler = context->glGetUniformLocation(prog, "u_SamplerNMap");
    unifCameraEye = context->glGetUniformLocation(prog, "u_CameraEye");
    unifTime = context->glGetUniformLocation(prog,"u_Time");
    unifLightDirection = context->glGetUniformLocation(prog,"u_LightVec");
    unifSkyDaySampler = context->glGetUniformLocation(prog,"u_SkyDaySampler");
    unifSkyNightSampler = context->glGetUniformLocation(prog,"u_SkyNightSampler");

    setupTexture();

}

void ShaderProgram::useMe()
{
    context->glUseProgram(prog);
}

void ShaderProgram::setModelMatrix(const glm::mat4 &model)
{
    useMe();

    if (unifModel != -1) {
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix4fv(unifModel,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &model[0][0]);
    }

    if (unifModelInvTr != -1) {
        glm::mat4 modelinvtr = glm::inverse(glm::transpose(model));
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix4fv(unifModelInvTr,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &modelinvtr[0][0]);
    }
}

void ShaderProgram::setViewProjMatrix(const glm::mat4 &vp)
{
    // Tell OpenGL to use this shader program for subsequent function calls
    useMe();

    if(unifViewProj != -1) {
    // Pass a 4x4 matrix into a uniform variable in our shader
                    // Handle to the matrix variable on the GPU
    context->glUniformMatrix4fv(unifViewProj,
                    // How many matrices to pass
                       1,
                    // Transpose the matrix? OpenGL uses column-major, so no.
                       GL_FALSE,
                    // Pointer to the first element of the matrix
                       &vp[0][0]);
    }
}

void ShaderProgram::setGeometryColor(glm::vec4 color)
{
    useMe();

    if(unifColor != -1)
    {
        context->glUniform4fv(unifColor, 1, &color[0]);
    }
}

//This function, as its name implies, uses the passed in GL widget
void ShaderProgram::draw(Drawable &d)
{
        useMe();

    // Each of the following blocks checks that:
    //   * This shader has this attribute, and
    //   * This Drawable has a vertex buffer for this attribute.
    // If so, it binds the appropriate buffers to each attribute.

    // Remember, by calling bindPos(), we call
    // glBindBuffer on the Drawable's VBO for vertex position,
    // meaning that glVertexAttribPointer associates vs_Pos
    // (referred to by attrPos) with that VBO

    if(d.bindProps()){
        if (attrPos != -1) {
            context->glEnableVertexAttribArray(attrPos);
            //context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, sizeof(glm::vec4) * 3, 0);
            context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, sizeof(vboStruct) , 0);
        }

        if (attrNor != -1) {
            context->glEnableVertexAttribArray(attrNor);
            //context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, sizeof(glm::vec4) * 3, (GLvoid*)(4 * sizeof(GL_FLOAT)));
            context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(4 * sizeof(GL_FLOAT)));

        }

        if (attrCol != -1) {
            context->glEnableVertexAttribArray(attrCol);
            //context->glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, sizeof(glm::vec4) * 3, (GLvoid*)(8 * sizeof(GL_FLOAT)));
            context->glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(8 * sizeof(GL_FLOAT)));

        }

        if (attrUV != -1) {
            context->glEnableVertexAttribArray(attrUV);
            context->glVertexAttribPointer(attrUV, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(12 * sizeof(GL_FLOAT)));
        }

        if(attrTangent != -1){
            context->glEnableVertexAttribArray(attrTangent);
            context->glVertexAttribPointer(attrTangent, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(14 * sizeof(GL_FLOAT)));
        }

        if(attrBitangent != -1){
            context->glEnableVertexAttribArray(attrBitangent);
            context->glVertexAttribPointer(attrBitangent, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(18 * sizeof(GL_FLOAT)));
        }

        if(attrCosPow != -1){
            context->glEnableVertexAttribArray(attrCosPow);
            context->glVertexAttribPointer(attrCosPow, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(22 * sizeof(GL_FLOAT)));
        }

        if(attrAnimate != -1){
            context->glEnableVertexAttribArray(attrAnimate);
            context->glVertexAttribPointer(attrAnimate, 4, GL_FLOAT, false, sizeof(vboStruct) , (GLvoid*)(23 * sizeof(GL_FLOAT)));
        }
    }



    // Bind the index buffer and then draw shapes from it.
    // This invokes the shader program, which accesses the vertex buffers.
    d.bindIdx();
    context->glDrawElements(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0);

    if (attrPos != -1) context->glDisableVertexAttribArray(attrPos);
    if (attrNor != -1) context->glDisableVertexAttribArray(attrNor);
    if (attrCol != -1) context->glDisableVertexAttribArray(attrCol);
    if (attrUV != -1) context->glDisableVertexAttribArray(attrUV);
    if (attrTangent != -1) context->glDisableVertexAttribArray(attrTangent);
    if (attrBitangent != -1) context->glDisableVertexAttribArray(attrBitangent);
    if (attrCosPow !=-1) context->glDisableVertexAttribArray(attrCosPow);
    if (attrAnimate !=-1) context->glDisableVertexAttribArray(attrAnimate);

    context->printGLErrorLog();
}

char* ShaderProgram::textFileRead(const char* fileName) {
    char* text;

    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");

        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);

            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

QString ShaderProgram::qTextFileRead(const char *fileName)
{
    QString text;
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        text = in.readAll();
        text.append('\0');
    }
    return text;
}

void ShaderProgram::printShaderInfoLog(int shader)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    context->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

    // should additionally check for OpenGL errors here

    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        context->glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
        qDebug() << "ShaderInfoLog:" << endl << infoLog << endl;
        delete [] infoLog;
    }

    // should additionally check for OpenGL errors here
}

void ShaderProgram::printLinkInfoLog(int prog)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    context->glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

    // should additionally check for OpenGL errors here

    if (infoLogLen > 0) {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        context->glGetProgramInfoLog(prog, infoLogLen, &charsWritten, infoLog);
        qDebug() << "LinkInfoLog:" << endl << infoLog << endl;
        delete [] infoLog;
    }
}

void ShaderProgram::setupTexture(){
    useMe();
    context->glGenTextures(1,&textureHandle);
    context->glActiveTexture(GL_TEXTURE0);
    context->glBindTexture(GL_TEXTURE_2D, textureHandle);

    context->glUniform1i(unifSampler, 0);

    int width, height;

    unsigned char* image = SOIL_load_image("..\\mini_minecraft_m1_3.3\\minecraft_textures_all.png", &width, &height, 0 , SOIL_LOAD_RGB);

    printf("SOIL results: '%s'\n", SOIL_last_result());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
    image);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Load the normal map texture.
    context->glGenTextures(1,&textureNMapHandle);
    context->glActiveTexture(GL_TEXTURE1);
    context->glBindTexture(GL_TEXTURE_2D, textureNMapHandle);
    context->glUniform1i(unifNMapSampler, 1);


    int widthNMap, heightNMap;

    unsigned char* imageNMap = SOIL_load_image("..\\mini_minecraft_m1_3.3\\minecraft_normals_all.png", &widthNMap, &heightNMap, 0 , SOIL_LOAD_RGB);

    printf("SOIL results: '%s'\n", SOIL_last_result());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthNMap, heightNMap, 0, GL_RGB, GL_UNSIGNED_BYTE,
    imageNMap);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //Load the skybox day texture

    context->glGenTextures(1,&textureSkyDayHandle);
    context->glActiveTexture(GL_TEXTURE2);
    context->glBindTexture(GL_TEXTURE_2D, textureSkyDayHandle);
    context->glUniform1i(unifSkyDaySampler, 2);


    int widthSkyDay, heightSkyDay;

    unsigned char* imageSkyDay = SOIL_load_image("..\\mini_minecraft_m1_3.3\\day.jpg", &widthSkyDay, &heightSkyDay, 0 , SOIL_LOAD_RGB);

    printf("SOIL results SkyDay: '%s'\n", SOIL_last_result());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthSkyDay, heightSkyDay, 0, GL_RGB, GL_UNSIGNED_BYTE,
    imageSkyDay);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //Load the skybox Night texture

    context->glGenTextures(1,&textureSkyNightHandle);
    context->glActiveTexture(GL_TEXTURE3);
    context->glBindTexture(GL_TEXTURE_2D, textureSkyNightHandle);
    context->glUniform1i(unifSkyNightSampler, 3);


    int widthSkyNight, heightSkyNight;

    unsigned char* imageSkyNight = SOIL_load_image("..\\mini_minecraft_m1_3.3\\night.png", &widthSkyNight, &heightSkyNight, 0 , SOIL_LOAD_RGB);

    printf("SOIL results SkyNight: '%s'\n", SOIL_last_result());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthSkyNight, heightSkyNight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    imageSkyNight);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


}


void ShaderProgram::activateTexture(){
    useMe();
    context->glActiveTexture(GL_TEXTURE0);
    context->glBindTexture(GL_TEXTURE_2D, textureHandle);

    context->glActiveTexture(GL_TEXTURE1);
    context->glBindTexture(GL_TEXTURE_2D, textureNMapHandle);

    context->glActiveTexture(GL_TEXTURE2);
    context->glBindTexture(GL_TEXTURE_2D, textureSkyDayHandle);

    context->glActiveTexture(GL_TEXTURE3);
    context->glBindTexture(GL_TEXTURE_2D, textureSkyNightHandle);
}

void ShaderProgram::setCameraEye(glm::vec3 eye){
    useMe();

    glm::vec4 eyePos = glm::vec4(eye,1);

    if(unifCameraEye != -1)
    {
        context->glUniform4fv(unifCameraEye, 1, &eyePos[0]);
    }
}

void ShaderProgram::setTimeVar(int time){
    useMe();
    if(unifTime!= -1){
        context->glUniform1f(unifTime,time);
    }
}


void ShaderProgram::setLightDirection(glm::vec4 lightDirec)
{
    useMe();

    if(unifLightDirection != -1){
        context->glUniform4fv(unifLightDirection, 1, &lightDirec[0]);
    }

}

