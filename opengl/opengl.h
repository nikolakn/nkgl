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


#include "models/scena2.h"
#include "models/scenaindex.h"
#include "opengl/camera.h"
#include "models/scenatex.h"
#include "models/nkkocka.h"

class NKOpengl
{
public:
    NKOpengl();
    ~NKOpengl();
    bool initGL(int w, int h);

    void render();

    void moveLeft();
    void moveRight();

    void moveUp();
    void moveDown();
private:
    //NKscenaIndex s2;
    NKscenaTex texscen;
    NKCamera kamera;

};

#endif // OPENGL_H
