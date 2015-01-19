#include "opengl.h"

NKOpengl::NKOpengl()
{

}

NKOpengl::~NKOpengl()
{

}

bool  NKOpengl::initGL(int duzina, int visina)
{
    m_duzina = duzina;
    m_visina = visina;
    kamera.setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);

    glClearColor( 0.f, 50.f, 200.f, 1.f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_2D);
    /* Enable blending, necessary for our alpha texture */
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    nktext.Init(duzina,visina);


    return true;
}


void NKOpengl::render(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    texscen.RenderScene(kamera.getProjectionMat(),kamera.modelView());
    nktext.render();
}

void NKOpengl::moveLeft()
{
    //texscen.moveLeft();
    //kamera.setX(kamera.getX()-0.5);
    kamera.rotate(0.05f);

}

void NKOpengl::moveRight()
{
    // texscen.moveRight();
    //kamera.setX(kamera.getX()+0.5);
    kamera.rotate(-0.05f);
}
void NKOpengl::moveUp()
{
    texscen.moveUp();
}

void NKOpengl::moveDown()
{
     texscen.moveDown();
}


