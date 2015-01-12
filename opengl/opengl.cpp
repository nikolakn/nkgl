#include "opengl.h"

opengl::opengl()
{
    //s2 = new scena2();
}

opengl::~opengl()
{

}

bool  opengl::initGL(int duzina, int visina)
{
    //glShadeModel( GL_SMOOTH );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    kamera.setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);
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

    return true;
}


void opengl::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //kvadrat1->render();
    s2.RenderScene(kamera.getProjectionMat());
}
