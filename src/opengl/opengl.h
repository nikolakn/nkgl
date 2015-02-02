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
#include "models/nkhex.h"
#include "models/nkhex2.h"
#include "opengl/nkgltext.h"

class NkOpengl
{
public:
    NkOpengl();
    ~NkOpengl();
    bool initGL(int w, int h);

    void render();

    void moveLeft();
    void moveRight();

    void moveUp();
    void moveDown();
    //void RenderText(std::string message, SDL_Color color, int x, int y, int size);
    void leftClick(int x, int y);
private:
    NkHex2 hex;
    NkScenaTex texscen;
    NkCamera kamera;
    NkGlText nktext;

    int m_duzina;
    int m_visina;
    bool selected;
};

#endif // OPENGL_H
