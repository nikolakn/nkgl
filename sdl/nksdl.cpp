#include "nksdl.h"

NKSDL::NKSDL()
{
    nkfullScrean = false;
    frame=0;
    avergeFrame=0;
    duzina=800;
    visina=600;
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
        if(nkfullScrean){
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
                gWindow = SDL_CreateWindow( "SDL Tutorial",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, duzina, visina, SDL_WINDOW_OPENGL  |  SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN );
            }
        }
        else{
            gWindow = SDL_CreateWindow( "SDL Tutorial",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, duzina, visina, SDL_WINDOW_OPENGL  | SDL_WINDOW_SHOWN );
        }

        //Create window
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
}

NKSDL::~NKSDL()
{

}


void NKSDL::close()
{
    //Destroy window
    if( gWindow != NULL )
        SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
    exit(0);
}

void NKSDL::handleKeys( SDL_Event event, int x __attribute__((unused)), int y __attribute__((unused)))
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

void NKSDL::loop()
{
    NKOpengl GL;
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

        GL.render();
        SDL_GL_SwapWindow( gWindow );
        if(!nkfullScrean){
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
    }
    //Disable text input
    SDL_StopTextInput();
    //Free resources and close SDL
    close();
}
