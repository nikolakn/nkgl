#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "opengl/cshader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl/texture.h"
#include "opengl/vertexBufferObject.h"

class NKscenaTex
{
private:

    CVertexBufferObject *vboSceneObjects;
    unsigned int uiVAO; // And one VAO

    CShader shVertex, shFragment;
    CShaderProgram spMain;

    CTexture tGold, tSnow;

float fRotationAngle;
const float PIover180 = 3.1415f/180.0f;
float fRotationAngleCube , fRotationAnglePyramid;
float fCubeRotationSpeed , fPyramidRotationSpeed;

public:
    NKscenaTex();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void RenderScene(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
	void ReleaseScene();
	
};
