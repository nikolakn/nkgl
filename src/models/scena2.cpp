
#include "models/scena2.h"


NkScena2::NkScena2()
{
    fRotationAngle = 0.0;
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Setup pyramid

	// Front face
	fPyramid[0] = 0.0f; fPyramid[1] = 5.0f; fPyramid[2] = 0.0f;
	fPyramid[3] = -3.0f; fPyramid[4] = 0.0f; fPyramid[5] = 3.0f;
	fPyramid[6] = 3.0f; fPyramid[7] = 0.0f; fPyramid[8] = 3.0f;

	// Back face
	fPyramid[9] = 0.0f; fPyramid[10] = 5.0f; fPyramid[11] = 0.0f;
	fPyramid[12] = 3.0f; fPyramid[13] = 0.0f; fPyramid[14] = -3.0f;
	fPyramid[15] = -3.0f; fPyramid[16] = 0.0f; fPyramid[17] = -3.0f;

	// Left face
	fPyramid[18] = 0.0f; fPyramid[19] = 5.0f; fPyramid[20] = 0.0f;
	fPyramid[21] = -3.0f; fPyramid[22] = 0.0f; fPyramid[23] = -3.0f;
	fPyramid[24] = -3.0f; fPyramid[25] = 0.0f; fPyramid[26] = 3.0f;

	// Right face
	fPyramid[27] = 0.0f; fPyramid[28] = 5.0f; fPyramid[29] = 0.0f;
	fPyramid[30] = 3.0f; fPyramid[31] = 0.0f; fPyramid[32] = 3.0f;
	fPyramid[33] = 3.0f; fPyramid[34] = 0.0f; fPyramid[35] = -3.0f;

	// Setup pyramid color

	FOR(i, 4)
	{
		fPyramidColor[i*9] = 1.0f; fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+2] = 0.0f;
		if(i < 2)
		{
			fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+4] = 1.0f; fPyramidColor[i*9+5] = 0.0f;
			fPyramidColor[i*9+2] = 0.0f; fPyramidColor[i*9+7] = 0.0f; fPyramidColor[i*9+8] = 1.0f;
		}
		else
		{
			fPyramidColor[i*9+2] = 0.0f; fPyramidColor[i*9+7] = 1.0f; fPyramidColor[i*9+8] = 0.0f;
			fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+4] = 0.0f; fPyramidColor[i*9+5] = 1.0f;
		}
	}
 
	glGenVertexArrays(1, uiVAO);
	glGenBuffers(2, uiVBO);

	// Setup whole pyramid
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36*sizeof(float), fPyramid, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 36*sizeof(float), fPyramidColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


    if(!shVertex.loadShader("./data/shaders/shaderm.vert", GL_VERTEX_SHADER)){
        std::cout << "vertex shader greska" << std::endl;
    }
    if(!shFragment.loadShader("./data/shaders/shaderm.frag", GL_FRAGMENT_SHADER)){
         std::cout << "fragment shader greska" << std::endl;
    }

    spMain.createProgram();
    spMain.addShaderToProgram(&shVertex);
    spMain.addShaderToProgram(&shFragment);

    spMain.linkProgram();

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	
}

void NkScena2::RenderScene(glm::mat4 *ProjectionMatrix)
{
	// We just clear color

    spMain.useProgram();

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(uiVAO[0]);

    int iModelViewLoc = glGetUniformLocation(spMain.getProgramID(), "modelViewMatrix");
    int iProjectionLoc = glGetUniformLocation(spMain.getProgramID(), "projectionMatrix");
    glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));

	glm::mat4 mModelView = glm::lookAt(glm::vec3(0, 15, 40), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Render rotating pyramid in the middle

    glm::mat4 mCurrent = glm::rotate(mModelView, fRotationAngle*PIover180, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
	glDrawArrays(GL_TRIANGLES, 0, 12);

	// Render translating pyramids

	// One on the left
    mCurrent = glm::translate(mModelView, glm::vec3(-20.0f, 10.0f*float(sin(fRotationAngle*PIover180)), 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
	glDrawArrays(GL_TRIANGLES, 0, 12);

	// One on the right
    mCurrent = glm::translate(mModelView, glm::vec3(20.0f, -10.0f*float(sin(fRotationAngle*PIover180)), 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
	glDrawArrays(GL_TRIANGLES, 0, 12);

	// And one translating and rotating on top

    mCurrent = glm::translate(mModelView, glm::vec3(25.0f*float(sin(fRotationAngle*PIover180)), 15.0f, 0.0f));
    mCurrent = glm::scale(mCurrent, glm::vec3(2.0, 2.0, 2.0));
    mCurrent = glm::rotate(mCurrent, fRotationAngle*PIover180, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
	glDrawArrays(GL_TRIANGLES, 0, 12);

	// And lastly - render scaling pyramid that rotates

    float fScaleValue = 1.5f+float(sin(fRotationAngle*PIover180))*0.5f;
	mCurrent = glm::translate(mModelView, glm::vec3(0.0f, -10.0f, 0.0f));
	mCurrent = glm::scale(mCurrent, glm::vec3(fScaleValue, fScaleValue, fScaleValue));
    mCurrent = glm::rotate(mCurrent, fRotationAngle*PIover180, glm::vec3(1.0f, 0.0f, 0.0f));
    mCurrent = glm::rotate(mCurrent, fRotationAngle*PIover180, glm::vec3(0.0f, 1.0f, 0.0f));
    mCurrent = glm::rotate(mCurrent, fRotationAngle*PIover180, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));
	glDrawArrays(GL_TRIANGLES, 0, 12);

    fRotationAngle += 2.0f;
}


void NkScena2::ReleaseScene()
{
    spMain.deleteProgram();

	glDeleteBuffers(2, uiVBO);
	glDeleteVertexArrays(1, uiVAO);

    shVertex.deleteShader();
    shFragment.deleteShader();
}
