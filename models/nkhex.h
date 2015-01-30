#ifndef NKHEX_H
#define NKHEX_H

#include "nkmodel.h"

#include "opengl/shader_utils.h"
#include "opengl/framework.h"
class NKHex : public NKModel
{
public:
    NKHex();
    ~NKHex();

    // NKModel interface
public:
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
private:
    int N;            	//size of grid
    int sirina;        	//width of grid
    const float  hexw=0.2f;  	//width of one hex
    const float  hexh=0.18f; 	//height of one hex

    GLuint box;
    GLuint position_vbo;
    GLint gbuffer_instanced_mvp_mat_loc;
    GLint gbuffer_instanced_normal_mat_loc;
    GLint gbuffer_instanced_view;
    GLint  gbuffer_instanced_pos;
    int size;
    vector<vec4> positions;
};

#endif // NKHEX_H
