#define GLM_FORCE_RADIANS
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
#include <iostream>
#include <string>

#include "sdl/ltimer.h"
#include "opengl/opengl.h"

using namespace std;

GLsizei duzina = 800;
GLsizei  visina = 600;
//Keep track of the frame count
int frame = 0;
int avergeFrame=0;
//The frames per second timer
LTimer fpsTimer;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//Graphics program
GLuint gProgramID = 0;
//OpenGL context
SDL_GLContext gContext;


void close();


bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        close();
    }
    else
    {
        //Use OpenGL 3.1 core
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
        //SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
        //SDL_GL_SetAttribute(SDL_GL_S);
        //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
        //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        // Get current display mode of all displays.
        SDL_DisplayMode current;
         for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){

           int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

           if(should_be_zero != 0)
             // In case of error...
             SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

           else
             // On success, print the current display mode.
             SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
             duzina = current.w;
             visina = current.h;

         }

        // use double buffering
        //   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // setup depth buffer
        //     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        glDepthMask( 1 );
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, duzina, visina, SDL_WINDOW_OPENGL  |  SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            close();
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if( gContext == NULL )
            {
                cout << "OpenGL context could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
                close();
            }
            else
            {
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if( glewError != GLEW_OK )
                {
                    cout << "Error initializing GLEW! %s\n"<< glewGetErrorString( glewError ) <<endl;
                    close();
                }

                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    cout <<"Warning: Unable to set VSync! SDL Error: "<< SDL_GetError()<<endl;
                }


            }
        }
    }
    return true;
}



void close()
{
    //Destroy window
    if( gWindow != NULL )
        SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
    exit(0);
}

void handleKeys( SDL_Event event, int x __attribute__((unused)), int y __attribute__((unused)))
{
    switch( event.type ){
    /* Look for a keypress */
    case SDL_KEYDOWN:
        /* Check the SDLKey values and move change the coords */
        switch( event.key.keysym.sym ){
        case SDLK_q:
            close();
            break;
        case SDLK_ESCAPE:
            close();
            break;
        case SDLK_LEFT:
            //alien_xvel = -1;
            break;
        case SDLK_RIGHT:
            //alien_xvel =  1;
            break;
        case SDLK_UP:
            //alien_yvel = -1;
            break;
        case SDLK_DOWN:
            //alien_yvel =  1;
            break;
        default:
            break;
        }
        break;
        /* We must also use the SDL_KEYUP events to zero the x */
        /* and y velocity variables. But we must also be       */
        /* careful not to zero the velocities when we shouldn't*/
    case SDL_KEYUP:
        switch( event.key.keysym.sym ){
        case SDLK_LEFT:

            break;
        case SDLK_RIGHT:

            break;
        case SDLK_UP:

            break;
        case SDLK_DOWN:

            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

}




int main( int argc __attribute__((unused)), char* args[] __attribute__((unused)))
{  
    //Start up SDL and create window
    if( !init() )
    {
        cout <<"Failed to initialize!\n";
        close();
    }
    //Initialize OpenGL
    opengl GL;
    if( !GL.initGL(duzina,visina) )
    {
        cout <<"nable to initialize OpenGL!\n";
        close();
    }
     fpsTimer.start();
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //Handle keypress with current mouse position
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                handleKeys( e, x, y );

            }

            //Render quad

            GL.render();
            //SDL_Delay(10);
            SDL_GL_SwapWindow( gWindow );
            frame++;
            //Calculate and correct fps
            if( fpsTimer.getTicks()  >= 1000 )
            {
                if(!avergeFrame)
                    avergeFrame= avergeFrame+frame;
                else
                   avergeFrame= (avergeFrame+frame)/2;
                std::string s = std::to_string(avergeFrame);
                s = "FPS: " + s;
                fpsTimer.start();
                SDL_SetWindowTitle(gWindow,s.c_str());
                frame = 0;
            }

        }

        //Disable text input
        SDL_StopTextInput();


    //Free resources and close SDL
    close();
    return 0;
}
