#include "camera.h"

NkCamera::NkCamera()
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

NkCamera::~NkCamera()
{

}

void NkCamera::setlookAt(){

    mModelView= glm::lookAt(glm::vec3(x,y,z), glm::vec3(xo,yo,zo), glm::vec3(a,b,g));

}
float NkCamera::getX() const
{
    return x;
}

void NkCamera::setX(float value)
{
    x = value;
    setlookAt();
}
float NkCamera::getY() const
{
    return y;
}

void NkCamera::setY(float value)
{
    y = value;
    setlookAt();
}
float NkCamera::getZ() const
{
    return z;
}

void NkCamera::setZ(float value)
{
    z = value;
    setlookAt();
}
float NkCamera::getA() const
{
    return a;
}

void NkCamera::setA(float value)
{
    a = value;
    setlookAt();
}
float NkCamera::getB() const
{
    return b;
}

void NkCamera::setB(float value)
{
    b = value;
    setlookAt();
}
float NkCamera::getG() const
{
    return g;
}

void NkCamera::setG(float value)
{
    g = value;
    setlookAt();
}
float NkCamera::getXo() const
{
    return xo;
}

void NkCamera::setXo(float value)
{
    xo = value;
    setlookAt();
}
float NkCamera::getYo() const
{
    return yo;
}

void NkCamera::setYo(float value)
{
    yo = value;
    setlookAt();
}
float NkCamera::getZo() const
{
    return zo;
}

void NkCamera::setZo(float value)
{
    zo = value;
    setlookAt();
}
void NkCamera::setModelView(const glm::mat4 &modelView)
{
    mModelView = modelView;
}
void NkCamera::rotate(float amount)
{
    mModelView = glm::rotate(mModelView, amount, glm::vec3(0.0f, 1.0f, 0.0f));

}
void NkCamera::rotatex(float amount)
{
    mModelView = glm::rotate(mModelView, amount, glm::vec3(1.0f, 0.0f, 0.1f));

}
void NkCamera::updateRot()
{
    mModelView = glm::lookAt(m_position, m_position + m_direction, m_up);
}
void NkCamera::translate(glm::vec3& direction)
{
    m_position += direction;
}
void NkCamera::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);

}


