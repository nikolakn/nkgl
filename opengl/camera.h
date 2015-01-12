#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class NKCamera
{
public:
    NKCamera();
    ~NKCamera();

    void setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar);
    glm::mat4* getProjectionMat(void) {return &mProjection;}
private:
    glm::mat4 mProjection;
};

#endif // CAMERA_H
