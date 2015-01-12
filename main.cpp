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

#include "models/kvadrat.h"
#include "models/scena2.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "sdl/ltimer.h"

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

kvadrat *kvadrat1 = 0;
scena2 *s2 =0;
glm::mat4 *mProjection;
//Starts up SDL, creates window, and initializes OpenGL
bool init();
//Initializes rendering program and clear color
bool initGL();

void setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    (*mProjection) = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
}

bool init()
{

    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
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
            success = false;
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if( gContext == NULL )
            {
                cout << "OpenGL context could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
                success = false;
                exit(-1);
            }
            else
            {
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if( glewError != GLEW_OK )
                {
                    cout << "Error initializing GLEW! %s\n"<< glewGetErrorString( glewError ) <<endl;
                }

                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    cout <<"Warning: Unable to set VSync! SDL Error: "<< SDL_GetError()<<endl;
                }

                //Initialize OpenGL
                if( !initGL() )
                {
                    cout <<"nable to initialize OpenGL!\n";
                    success = false;
                }
            }
        }
    }

    //kvadrat1= new kvadrat();
    s2 = new scena2();
    return success;
}

bool initGL()
{
    //glShadeModel( GL_SMOOTH );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    mProjection = new glm::mat4();
    setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);
    glEnable( GL_LINE_SMOOTH );
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    //glCullFace( GL_FRONT_AND_BACK);
    //glFrontFace( GL_CCW );
    //glEnable( GL_CULL_FACE );
    //glEnable(GL_DEPTH_TEST);
    //glClearStencil(0x0);
    //glEnable(GL_STENCIL_TEST);
    glClearColor( 0.f, 50.f, 200.f, 1.f );
    fpsTimer.start();
    return true;
}

void close()
{
    //Deallocate program
    glDeleteProgram( gProgramID );

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    delete s2;
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



void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //kvadrat1->render();
    s2->RenderScene(mProjection);
}

int main( int argc __attribute__((unused)), char* args[] __attribute__((unused)))
{  
    //Start up SDL and create window
    if( !init() )
    {
        cout <<"Failed to initialize!\n";
    }
    else
    {
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

            render();
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
    }

    //Free resources and close SDL
    close();

    return 0;
}
