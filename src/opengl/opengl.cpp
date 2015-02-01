#include "opengl.h"

NkOpengl::NkOpengl()
{

}

NkOpengl::~NkOpengl()
{

}

bool  NkOpengl::initGL(int duzina, int visina)
{
    m_duzina = duzina;
    m_visina = visina;

    kamera.setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);
    glClearColor( 0.f, 50.f, 200.f, 1.f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_2D);

    /* Enable blending, necessary for our alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    nktext.Init(duzina,visina);
    texscen.init();
    hex.init();
    return true;
}


void NkOpengl::render(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    texscen.render(kamera.getProjectionMat(),kamera.modelView());
    hex.render(kamera.getProjectionMat(),kamera.modelView());
    nktext.render();

}

void NkOpengl::moveLeft()
{
    //texscen.moveLeft();
    //kamera.setX(kamera.getX()-0.5);
    kamera.rotate(0.05f);

}

void NkOpengl::moveRight()
{
    // texscen.moveRight();
    //kamera.setX(kamera.getX()+0.5);
    kamera.rotate(-0.05f);
}
void NkOpengl::moveUp()
{
    texscen.moveUp();
    kamera.rotatex(0.05f);
}

void NkOpengl::moveDown()
{
     texscen.moveDown();
     kamera.rotatex(-0.05f);
}


