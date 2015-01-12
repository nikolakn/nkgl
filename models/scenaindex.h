#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include "opengl/cshader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define HM_SIZE_X 4 // Dimensions of our heightmap
#define HM_SIZE_Y 4

class NKscenaIndex
{
private:

    unsigned int uiVBOHeightmapData; // Here are stored heightmap data (vertices)
    unsigned int uiVBOIndices; // And here indices for rendering heightmap

    unsigned int uiVAOHeightmap; // One VAO for heightmap

    bool bShowFPS = false;
    bool bVerticalSync = true;


CShader shVertex, shFragment;
CShaderProgram spMain;

float fRotationAngle;
const float PIover180 = 3.1415f/180.0f;


public:
    NKscenaIndex();
    void RenderScene(glm::mat4 *ProjectionMatrix);
	void ReleaseScene();
	
};
