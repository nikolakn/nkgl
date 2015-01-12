#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glew.h>

#ifdef WIN32
#include <windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif


#include <GL/glu.h>

#include "models/scena2.h"
#include "models/scenaindex.h"
#include "opengl/camera.h"
class NKOpengl
{
public:
    NKOpengl();
    ~NKOpengl();
    bool initGL(int w, int h);

    void render();
private:
    NKscenaIndex s2;
    NKCamera kamera;
};

#endif // OPENGL_H
