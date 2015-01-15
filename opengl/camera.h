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
    glm::mat4* modelView() {return &mModelView;}

    void setlookAt();
    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

    float getA() const;
    void setA(float value);

    float getB() const;
    void setB(float value);

    float getG() const;
    void setG(float value);

    float getXo() const;
    void setXo(float value);

    float getYo() const;
    void setYo(float value);

    float getZo() const;
    void setZo(float value);

    glm::mat4* modelView() const;
    void setModelView(const glm::mat4 &modelView);

private:
    glm::mat4 mProjection;
    glm::mat4 mModelView;
    float x, y, z; //position
    float a,b,g;   //angles
    float xo, yo, zo; //lookat
};

#endif // CAMERA_H
