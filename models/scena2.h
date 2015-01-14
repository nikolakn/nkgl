#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "opengl/cshader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class NKscena2
{
private:

float fPyramid[36]; // Pyramid data - 4 triangles of 3 vertices of 3 floats
float fPyramidColor[36]; // Same for color

unsigned int uiVBO[2]; // One VBO for vertices positions, one for colors
unsigned int uiVAO[1]; // One VAO for pyramid

bool bShowFPS = false;
bool bVerticalSync = true;

CShader shVertex, shFragment;
CShaderProgram spMain;

float fRotationAngle;
const float PIover180 = 3.1415f/180.0f;


public:
    NKscena2();
    void RenderScene(glm::mat4 *ProjectionMatrix);
	void ReleaseScene();
	
};
