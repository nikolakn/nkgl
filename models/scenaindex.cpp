
#include "models/scenaindex.h"


NKscenaIndex::NKscenaIndex()
{
    fRotationAngle = 0.0;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Setup heightmap

    glGenVertexArrays(1, &uiVAOHeightmap); // Create one VAO
    glGenBuffers(1, &uiVBOHeightmapData); // One VBO for data
    glGenBuffers(1, &uiVBOIndices); // And finally one VBO for indices

    glBindVertexArray(uiVAOHeightmap);
    glBindBuffer(GL_ARRAY_BUFFER, uiVBOHeightmapData);

    glm::vec3 vHeightmapData[HM_SIZE_X*HM_SIZE_Y]; // Here the heightmap vertices will be stored temporarily

    float fHeights[HM_SIZE_X*HM_SIZE_Y] =
    {
        4.0f, 2.0f, 3.0f, 1.0f,
        3.0f, 5.0f, 8.0f, 2.0f,
        7.0f, 10.0f, 12.0f, 6.0f,
        4.0f, 6.0f, 8.0f, 3.0f
    };

    float fSizeX = 40.0f, fSizeZ = 40.0f;

    FOR(i, HM_SIZE_X*HM_SIZE_Y)
    {
        float column = float(i%HM_SIZE_X), row = float(i/HM_SIZE_X);
        vHeightmapData[i] = glm::vec3(
            -fSizeX/2+fSizeX*column/float(HM_SIZE_X-1), // X Coordinate
            fHeights[i],									// Y Coordinate (it's height)
            -fSizeZ/2+fSizeZ*row/float(HM_SIZE_Y-1)	// Z Coordinate
            );
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*HM_SIZE_X*HM_SIZE_Y, vHeightmapData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &uiVBOIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBOIndices);
    int iIndices[] =
    {
        0, 4, 1, 5, 2, 6, 3, 7, 16, // First row, then restart
        4, 8, 5, 9, 6, 10, 7, 11, 16, // Second row, then restart
        8, 12, 9, 13, 10, 14, 11, 15, // Third row, no restart
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iIndices), iIndices, GL_STATIC_DRAW);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(HM_SIZE_X*HM_SIZE_Y);

    // Load shaders and create shader program

    shVertex.LoadShader("./data/shaders/shaderindex.vert", GL_VERTEX_SHADER);
    shFragment.LoadShader("./data/shaders/shaderindex.frag", GL_FRAGMENT_SHADER);

    spMain.CreateProgram();
    spMain.AddShaderToProgram(&shVertex);
    spMain.AddShaderToProgram(&shFragment);

    spMain.LinkProgram();


}

void NKscenaIndex::RenderScene(glm::mat4 *ProjectionMatrix)
{
    spMain.UseProgram();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(uiVAOHeightmap);

    int iModelViewLoc = glGetUniformLocation(spMain.GetProgramID(), "modelViewMatrix");
    int iProjectionLoc = glGetUniformLocation(spMain.GetProgramID(), "projectionMatrix");
    glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));

    glm::mat4 mModelView = glm::lookAt(glm::vec3(0, 60, 30), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mCurrent = glm::rotate(mModelView, fRotationAngle*PIover180, glm::vec3(0.0f, 1.0f, 0.0f));
    mCurrent = glm::scale(mCurrent, glm::vec3(2.0, 2.0, 2.0));
    glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
    glBindVertexArray(uiVAOHeightmap);
    glDrawElements(GL_TRIANGLE_STRIP, HM_SIZE_X*(HM_SIZE_Y-1)*2+HM_SIZE_Y-2, GL_UNSIGNED_INT, 0);

    fRotationAngle += 1.0f;


}


void NKscenaIndex::ReleaseScene()
{
    glDeleteBuffers(1, &uiVBOHeightmapData);
    glDeleteBuffers(1, &uiVBOIndices);
    glDeleteVertexArrays(1, &uiVAOHeightmap);

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}

