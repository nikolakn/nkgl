
#include "models/scenatex.h"



NKscenaTex::NKscenaTex()
{
    fRotationAngle = 0.0;
    fRotationAngleCube = 0.0f;
    fRotationAnglePyramid = 0.0f;
    fCubeRotationSpeed = 0.0f;
    fPyramidRotationSpeed = 0.0f;
    vboSceneObjects=new CVertexBufferObject();
    glm::vec3 vCubeVertices[] =
    {
        // Front face
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),
        // Back face
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),

        // Left face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Right face
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
        // Top face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Bottom face
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f)
    };

    glm::vec2 vCubeTexCoords[] = {glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
                                  glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)};

    glm::vec3 vPyramidVertices[] =
    {
        // Front face
        glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f),
        // Back face
        glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),
        // Left face
        glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),
        // Right face
        glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f)
    };

    glm::vec2 vPyramidTexCoords[] = {glm::vec2(0.5f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f)};

    glm::vec3 vGround[] =
    {
        glm::vec3(-50, -10, -50), glm::vec3(50, -10, -50), glm::vec3(50, -10, 50),
        glm::vec3(50, -10, 50), glm::vec3(-50, -10, 50), glm::vec3(-50, -10, -50)
    };

    vboSceneObjects->createVBO();
    glGenVertexArrays(1, &uiVAO); // Create one VAO
    glBindVertexArray(uiVAO);

    vboSceneObjects->bindVBO();

    // Add cube to VBO
    FOR(i, 36)
    {
        vboSceneObjects->addData(&vCubeVertices[i], sizeof(glm::vec3));
        vboSceneObjects->addData(&vCubeTexCoords[i%6], sizeof(glm::vec2));
    }

    // Add pyramid to VBO

    FOR(i, 12)
    {
        vboSceneObjects->addData(&vPyramidVertices[i], sizeof(glm::vec3));
        vboSceneObjects->addData(&vPyramidTexCoords[i%3], sizeof(glm::vec2));
    }

    // Add ground to VBO

    FOR(i, 6)
    {
        vboSceneObjects->addData(&vGround[i], sizeof(glm::vec3));
        vCubeTexCoords[i] *= 5.0f;
        vboSceneObjects->addData(&vCubeTexCoords[i%6], sizeof(glm::vec2));
    }

    vboSceneObjects->uploadDataToGPU(GL_STATIC_DRAW);

    // Vertex positions start on zero index, and distance between two consecutive is sizeof whole
    // vertex data (position and tex. coord)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)+sizeof(glm::vec2), 0);
    // Texture coordinates start right after positon, thus on (sizeof(glm::vec3)) index,
    // and distance between two consecutive is sizeof whole vertex data (position and tex. coord)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));

    // Load shaders and create shader program

    //shVertex.loadShader("./data/shaders/shadertex.vert", GL_VERTEX_SHADER);

    if(!shVertex.loadShader("./data/shaders/shadertex.vert", GL_VERTEX_SHADER)){
         std::cout<<"grska shadertex.vert" << std::endl;
    }
    if(!shFragment.loadShader("./data/shaders/shadertex.frag", GL_FRAGMENT_SHADER)){
         std::cout<<"grska shadertex.frag" << std::endl;
    }
    spMain.createProgram();
    spMain.addShaderToProgram(&shVertex);
    spMain.addShaderToProgram(&shFragment);

    spMain.linkProgram();



    tGold.loadTexture2D("./data/textures/golddiag.jpg", true);
    tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    tSnow.loadTexture2D("./data/textures/snow.jpg", true);
    tSnow.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
    glBindVertexArray(0);

}

void NKscenaTex::moveLeft()
{
    //fPyramidRotationSpeed -= 2.0f;
 fRotationAnglePyramid += 4.0f;
    fRotationAnglePyramid += fPyramidRotationSpeed;
}

void NKscenaTex::moveRight()
{
    //fPyramidRotationSpeed += 2.0f;
     fRotationAnglePyramid -= 4.0f;
}

void NKscenaTex::moveUp()
{
    //fCubeRotationSpeed += 2.0f;
    fRotationAngleCube += 4.0f;
}

void NKscenaTex::moveDown()
{
    //fCubeRotationSpeed -= 2.0f;
    fRotationAngleCube -= 4.0f;
}


void NKscenaTex::RenderScene(glm::mat4 *ProjectionMatrix,glm::mat4 *mModelView){
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

    // Texture binding - we set GL_ACTIVE_TEXTURE0, and then we tell fragment shader,
    // that gSampler variable will fetch data from GL_ACTIVE_TEXTURE0

    int iSamplerLoc = glGetUniformLocation(spMain.getProgramID(), "gSampler");
    glUniform1i(iSamplerLoc, 0);

    tGold.bindTexture(0);

    // Rendering of pyramid

    mCurrent = glm::translate(*mModelView, glm::vec3(8.0f, 0.0f, 0.0f));
    mCurrent = glm::scale(mCurrent, glm::vec3(10.0f, 10.0f, 10.0f));
    mCurrent = glm::rotate(mCurrent, fRotationAnglePyramid*PIover180, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

    glDrawArrays(GL_TRIANGLES, 36, 12);

    // Rendering of cube

    mCurrent = glm::translate(*mModelView, glm::vec3(-8.0f, 0.0f, 0.0f));
    mCurrent = glm::scale(mCurrent, glm::vec3(10.0f, 10.0f, 10.0f));
    mCurrent = glm::rotate(mCurrent, fRotationAngleCube*PIover180, glm::vec3(1.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    // Render ground

    tSnow.bindTexture(0);

    glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(*mModelView));
    glDrawArrays(GL_TRIANGLES, 48, 6);

    // A little interaction for user
   // tGold.setFiltering((tGold.getMagnificationFilter()+1)%2, tGold.getMinificationFilter());
   // tSnow.setFiltering((tSnow.getMagnificationFilter()+1)%2, tSnow.getMinificationFilter());

    //int iNewMinFilter = tSnow.getMinificationFilter() == TEXTURE_FILTER_MIN_TRILINEAR ? TEXTURE_FILTER_MIN_NEAREST : tSnow.getMinificationFilter()+1;
   // tSnow.setFiltering(tSnow.getMagnificationFilter(), iNewMinFilter);
   // tGold.setFiltering(tGold.getMagnificationFilter(), iNewMinFilter);
    //glBindTexture(GL_TEXTURE_2D,0);
   glBindVertexArray(0);
   glUseProgram(0);
}


void NKscenaTex::ReleaseScene()
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
