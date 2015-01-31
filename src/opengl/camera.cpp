#include "camera.h"

NKCamera::NKCamera()
{
    x=0.0;
    y=12.0;
    z=27.0;
    xo=0.0;
    yo=0.0;
    zo=0.0;
    a=0.0;
    b=1.0;
    g=0.0;
    m_position = glm::vec3(x, y, z);
    m_direction = glm::vec3(xo, yo, zo);
    m_up = glm::vec3(a, b, g);
    setlookAt();
}

NKCamera::~NKCamera()
{

}

void NKCamera::setlookAt(){

    mModelView= glm::lookAt(glm::vec3(x,y,z), glm::vec3(xo,yo,zo), glm::vec3(a,b,g));

}
float NKCamera::getX() const
{
    return x;
}

void NKCamera::setX(float value)
{
    x = value;
    setlookAt();
}
float NKCamera::getY() const
{
    return y;
}

void NKCamera::setY(float value)
{
    y = value;
    setlookAt();
}
float NKCamera::getZ() const
{
    return z;
}

void NKCamera::setZ(float value)
{
    z = value;
    setlookAt();
}
float NKCamera::getA() const
{
    return a;
}

void NKCamera::setA(float value)
{
    a = value;
    setlookAt();
}
float NKCamera::getB() const
{
    return b;
}

void NKCamera::setB(float value)
{
    b = value;
    setlookAt();
}
float NKCamera::getG() const
{
    return g;
}

void NKCamera::setG(float value)
{
    g = value;
    setlookAt();
}
float NKCamera::getXo() const
{
    return xo;
}

void NKCamera::setXo(float value)
{
    xo = value;
    setlookAt();
}
float NKCamera::getYo() const
{
    return yo;
}

void NKCamera::setYo(float value)
{
    yo = value;
    setlookAt();
}
float NKCamera::getZo() const
{
    return zo;
}

void NKCamera::setZo(float value)
{
    zo = value;
    setlookAt();
}
void NKCamera::setModelView(const glm::mat4 &modelView)
{
    mModelView = modelView;
}
void NKCamera::rotate(float amount)
{
    mModelView = glm::rotate(mModelView, amount, glm::vec3(0.0f, 1.0f, 0.0f));

}
void NKCamera::rotatex(float amount)
{
    mModelView = glm::rotate(mModelView, amount, glm::vec3(1.0f, 0.0f, 0.1f));

}
void NKCamera::updateRot()
{
    mModelView = glm::lookAt(m_position, m_position + m_direction, m_up);
}
void NKCamera::translate(glm::vec3& direction)
{
    m_position += direction;
}
void NKCamera::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);

}

