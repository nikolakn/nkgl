#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include "opengl/cshader.h"


class NKscena1
{
private:


float fTriangle[9]; // Data to render triangle (3 vertices, each has 3 floats)
float fQuad[12]; // Data to render quad using triangle strips (4 vertices, each has 3 floats)
float fTriangleColor[9];
float fQuadColor[12];

unsigned int uiVBO[4];
unsigned int uiVAO[2];

CShader shVertex, shFragment;
CShaderProgram spMain;

public:
    NKscena1();
	void RenderScene();
	void ReleaseScene();
	
};
