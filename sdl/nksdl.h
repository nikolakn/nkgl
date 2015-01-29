#ifndef NKSDL_H
#define NKSDL_H
#define NK_FULL_SCREEN
#define GLM_FORCE_RADIANS
#include <GL/glew.h>

#ifdef WIN32
#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif


//#include <GL/glu.h>
#include <iostream>
#include <string>

#include "sdl/ltimer.h"
#include "opengl/opengl.h"

using namespace std;


class NKSDL
{
public:
    NKSDL();
    ~NKSDL();
    void close();
    void handleKeys(SDL_Event event, int x, int y);
    void loop();
private:

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    //OpenGL context
    SDL_GLContext gContext;
    //Keep track of the frame count
    NKOpengl *GL;
    int frame;
    int avergeFrame;
    //The frames per second timer
    LTimer fpsTimer;
    GLsizei duzina;
    GLsizei  visina;
    bool nkfullScrean;
};

#endif // NKSDL_H
