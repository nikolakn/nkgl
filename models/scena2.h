#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include "opengl/cshader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef  unsigned int uint;

class scena2
{
private:



float fPyramid[36]; // Pyramid data - 4 triangles of 3 vertices of 3 floats
float fPyramidColor[36]; // Same for color

uint uiVBO[2]; // One VBO for vertices positions, one for colors
uint uiVAO[1]; // One VAO for pyramid

bool bShowFPS = false;
bool bVerticalSync = true;

CShader shVertex, shFragment;
CShaderProgram spMain;

public:
	scena2();
    void RenderScene(glm::mat4 *ProjectionMatrix);
	void ReleaseScene();
	
};
