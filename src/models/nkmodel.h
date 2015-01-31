#ifndef NKMODEL_H
#define NKMODEL_H

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl/texture.h"
#include "opengl/vertexBufferObject.h"
#include "opengl/shader.hpp"
class NKModel
{
    virtual	void init() = 0;
    virtual void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView) = 0;
    virtual	void releaseScene() = 0;


 protected:
    GLuint program;
};

#endif // NKMODEL_H
