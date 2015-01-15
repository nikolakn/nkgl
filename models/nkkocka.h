#ifndef NKKOCKA_H
#define NKKOCKA_H

//#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "opengl/shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class NKkocka
{
public:
    NKkocka();
    ~NKkocka();

    void RenderScene(glm::mat4 *ProjectionMatrix);
    void ReleaseScene();

private:
    GLuint colorbuffer;
    GLuint vertexbuffer;
    GLuint MatrixID;
    GLuint programID;
    glm::mat4 MVP ;
};

#endif // NKKOCKA_H
