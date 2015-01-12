#include "camera.h"

camera::camera()
{

}

camera::~camera()
{

}

void camera::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
}

