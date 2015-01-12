#include "camera.h"

NKCamera::NKCamera()
{

}

NKCamera::~NKCamera()
{

}

void NKCamera::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
}

