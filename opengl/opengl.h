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
#include "opengl/camera.h"
class opengl
{
public:
    opengl();
    ~opengl();
    bool initGL(int w, int h);

    void render();
private:
    scena2 s2;
    camera kamera;
};

#endif // OPENGL_H
