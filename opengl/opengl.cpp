#include "opengl.h"

NKOpengl::NKOpengl()
{
    //s2 = new scena2();
}

NKOpengl::~NKOpengl()
{

}

bool  NKOpengl::initGL(int duzina, int visina)
{

     //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    //Initialize Modelview Matrix
    //glMatrixMode( GL_MODELVIEW );
    //glLoadIdentity();
    kamera.setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);
    //glEnable( GL_LINE_SMOOTH );
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    //glCullFace( GL_FRONT);
    //glFrontFace( GL_CW );
    //glEnable( GL_CULL_FACE );

    //glClearStencil(0x0);
    //glEnable(GL_STENCIL_TEST);
    glClearColor( 0.f, 50.f, 200.f, 1.f );
    glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    return true;
}


void NKOpengl::render(){

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //kvadrat1->render();
    //s2.RenderScene(kamera.getProjectionMat());
    texscen.RenderScene(kamera.getProjectionMat(),kamera.modelView());
    //kocka1.RenderScene(kamera.getProjectionMat());
}

void NKOpengl::moveLeft()
{
    //texscen.moveLeft();
    kamera.setX(kamera.getX()-0.5);
}

void NKOpengl::moveRight()
{
    // texscen.moveRight();
    kamera.setX(kamera.getX()+0.5);
}
void NKOpengl::moveUp()
{
    texscen.moveUp();
}

void NKOpengl::moveDown()
{
     texscen.moveDown();
}
