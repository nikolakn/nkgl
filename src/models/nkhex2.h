#ifndef NKHEX2_H
#define NKHEX2_H
#include "include/framework.h"
#include "nkmodel.h"

class NKHex2 : public NKModel
{
public:
    NKHex2();
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
    GLuint create_hex();
private:
    int sirina;        	//width of grid
    const float  HEX_WIDTH=0.2;  	//width of one hex
    const float  HEX_HEIGHT=0.18; 	//height of one hex
    const int HEX_SIZE = 50000; //number of hex
    GLuint box;
    GLuint position_vbo;
    GLint gbuffer_instanced_mvp_mat_loc;
    GLint gbuffer_instanced_normal_mat_loc;
    GLint gbuffer_instanced_view;
    GLint  gbuffer_instanced_pos;
    int size;
    vector<vec4> positions;

};



#endif // NKHEX2_H