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

#include <iostream>
#include <string>

#include "sdl/ltimer.h"
#include "opengl/opengl.h"

using namespace std;

/**
* Create window for OpenGl rendering
*/
class NkSdl
{
public:
    NkSdl();
    ~NkSdl();
    void close();
    void handleKeys(SDL_Event event, int x, int y);
    void loop();
private:
    SDL_Window* gWindow = NULL; /**< The window we'll be rendering to */
    SDL_GLContext gContext;     /**< OpenGL context */
    NkOpengl *GL;               /**< OpenGL render */
    int frame;
    int avergeFrame;
    LTimer fpsTimer;            /**< The frames per second timer */
    GLsizei duzina;
    GLsizei  visina;
    bool nkfullScrean;
};

#endif // NKSDL_H
