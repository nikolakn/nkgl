#include "nkhex.h"

NKHex::NKHex()
{
}

NKHex::~NKHex()
{

}



void NKHex::init()
{
    N=35000;
    sirina=200;
    fRotationAngle = 0.0;
    fRotationAngleCube = 0.0f;
    fRotationAnglePyramid = 0.0f;
    fCubeRotationSpeed = 0.0f;
    fPyramidRotationSpeed = 0.0f;
    vboSceneObjects=new CVertexBufferObject();


    float hx = hexw/2;
    float ym = hexh/3;
    float yh = hexh-ym;

    glm::vec3 vCubeVertices[] =
    {
        // Front face
        glm::vec3(0, 0, 0),
        glm::vec3(-hx, ym, 0),
        glm::vec3(0, yh, 0),
        glm::vec3(hx, ym, 0),
        glm::vec3(hx, -ym, 0),
        glm::vec3(0, -yh, 0),
        glm::vec3(-hx, -ym, 0),
        glm::vec3(-hx, ym, 0)

    };

    glm::vec2 vCubeTexCoords[] = {glm::vec2(0, 0), glm::vec2(0, 0.2),
                                  glm::vec2(0.5, 0),glm::vec2(1, 0.2),
                                  glm::vec2(1, 0.8), glm::vec2(0.5, 1),
                                  glm::vec2(0, 0.8),glm::vec2(0, 0.2)
                                 };


            // Create a new Vertex Array Object in memory and select it (bind)


    vboSceneObjects->createVBO();
    glGenVertexArrays(1, &uiVAO); // Create one VAO

glBindVertexArray(uiVAO);
    vboSceneObjects->bindVBO(GL_ARRAY_BUFFER);

    // Add cube to VBO
    FOR(i, 8)
    {
        vboSceneObjects->addData(&vCubeVertices[i], sizeof(glm::vec3));
        vboSceneObjects->addData(&vCubeTexCoords[i], sizeof(glm::vec2));

    }

    vboSceneObjects->uploadDataToGPU(GL_DYNAMIC_DRAW);

    // Vertex positions start on zero index, and distance between two consecutive is sizeof whole
    // vertex data (position and tex. coord)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(glm::vec3)+ sizeof(glm::vec2), 0);
    // Texture coordinates start right after positon, thus on (sizeof(glm::vec3)) index,
    // and distance between two consecutive is sizeof whole vertex data (position and tex. coord)
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,  sizeof(glm::vec3)+ sizeof(glm::vec2), (void*)sizeof(glm::vec3));

    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));

    //G/L20.glVertexAttribPointer(1, VertexData.colorElementCount, GL11.GL_FLOAT,
    //                false, VertexData.stride, VertexData.colorByteOffset);
    // Load shaders and create shader program

    //shVertex.loadShader("./data/shaders/shadertex.vert", GL_VERTEX_SHADER);
    //LoadShaders("./data/shaders/vertexHex.glsl","./data/shaders/fragmentHex.glsl");
    //create_shader("./data/shaders/vertexHex.glsl", GL_VERTEX_SHADER);

    if(!shVertex.loadShader("./data/shaders/shadertex.vert", GL_VERTEX_SHADER)){
        std::cout<<"grska hex.vert" << std::endl;
    }
    if(!shFragment.loadShader("./data/shaders/shadertex.frag", GL_FRAGMENT_SHADER)){
        std::cout<<"grska hex.frag" << std::endl;
    }
    spMain.createProgram();
    spMain.addShaderToProgram(&shVertex);
    spMain.addShaderToProgram(&shFragment);

    spMain.linkProgram();



    tGold.loadTexture2D("./data/textures/552.png", true);
    tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    glBindVertexArray(0);

}

void NKHex::render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView)
{
    //glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    //glDepthFunc(GL_LESS);
    spMain.useProgram();
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    int iModelViewLoc = glGetUniformLocation(spMain.getProgramID(), "modelViewMatrix");
    int iProjectionLoc = glGetUniformLocation(spMain.getProgramID(), "projectionMatrix");
    glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));

    //glm::mat4 mModelView = glm::lookAt(glm::vec3(0, 12, 27), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mCurrent;

    glBindVertexArray(uiVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Texture binding - we set GL_ACTIVE_TEXTURE0, and then we tell fragment shader,
    // that gSampler variable will fetch data from GL_ACTIVE_TEXTURE0

    //int iSamplerLoc = glGetUniformLocation(spMain.getProgramID(), "gSampler");
    //glUniform1i(iSamplerLoc, 0);

    tGold.bindTexture(0);

    // Rendering of cube

    mCurrent = glm::translate(*mModelView, glm::vec3(-8.0f, 0.0f, 0.0f));
    mCurrent = glm::scale(mCurrent, glm::vec3(10.0f, 10.0f, 10.0f));
    mCurrent = glm::rotate(mCurrent, fRotationAngleCube*PIover180, glm::vec3(1.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

    vboSceneObjects->bindVBO(GL_ARRAY_BUFFER);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    glDrawElementsInstancedBaseVertex(GL_TRIANGLE_FAN, 8 ,GL_UNSIGNED_BYTE,0, 1, 0);
    // Render ground



    // A little interaction for user
    // tGold.setFiltering((tGold.getMagnificationFilter()+1)%2, tGold.getMinificationFilter());
    // tSnow.setFiltering((tSnow.getMagnificationFilter()+1)%2, tSnow.getMinificationFilter());

    //int iNewMinFilter = tSnow.getMinificationFilter() == TEXTURE_FILTER_MIN_TRILINEAR ? TEXTURE_FILTER_MIN_NEAREST : tSnow.getMinificationFilter()+1;
    // tSnow.setFiltering(tSnow.getMagnificationFilter(), iNewMinFilter);
    // tGold.setFiltering(tGold.getMagnificationFilter(), iNewMinFilter);

    glBindSampler(0,0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void NKHex::releaseScene()
{
    spMain.deleteProgram();

    shVertex.deleteShader();
    shFragment.deleteShader();

    vboSceneObjects->releaseVBO();
    delete  vboSceneObjects;
    glDeleteVertexArrays(1, &uiVAO);

    tGold.releaseTexture();
    tSnow.releaseTexture();
}
