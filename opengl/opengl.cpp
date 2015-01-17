#include "opengl.h"

NKOpengl::NKOpengl()
{
    //s2 = new scena2();

    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
      fprintf(stderr, "Could not init freetype library\n");
    }
    if(FT_New_Face(ft, "FreeSans.ttf", 0, &face)) {
      fprintf(stderr, "Could not open font\n");
    }

}

NKOpengl::~NKOpengl()
{

}

bool  NKOpengl::initGL(int duzina, int visina)
{

    kamera.setProjection3D(45.0f, (float)duzina/(float)visina , 0.001f, 1000.0f);

    glClearColor( 0.f, 50.f, 200.f, 1.f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    FT_Set_Pixel_Sizes(face, 0, 48);
    if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
      fprintf(stderr, "Could not load character 'X'\n");
    }
    return true;
}


void NKOpengl::render(){

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );;
    texscen.RenderScene(kamera.getProjectionMat(),kamera.modelView());
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
