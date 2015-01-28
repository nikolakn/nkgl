#ifndef NKHEX_H
#define NKHEX_H

#include "nkmodel.h"

#include "opengl/shader_utils.h"

class NKHex : public NKModel
{
public:
    NKHex();
    ~NKHex();

    // NKModel interface
public:
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
private:
    int N;            	//size of grid
    int sirina;        	//width of grid
    const float  hexw=0.2f;  	//width of one hex
    const float  hexh=0.18f; 	//height of one hex

    CVertexBufferObject *vboSceneObjects;
    unsigned int uiVAO; // And one VAO
    CTexture tGold, tSnow;

    float fRotationAngle;
    const float PIover180 = 3.1415f/180.0f;
    float fRotationAngleCube , fRotationAnglePyramid;
    float fCubeRotationSpeed , fPyramidRotationSpeed;

};

#endif // NKHEX_H
