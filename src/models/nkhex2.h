#ifndef NKHEX2_H
#define NKHEX2_H
#include "include/framework.h"
#include "nkmodel.h"

class NkHex2 : public NkModel
{
public:
    NkHex2();
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
    GLuint createHex();
    GLuint loadTexture(string filenameString,GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
    void LoadShaders();
    void renderSel(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
private:
    const float  HEX_WIDTH=0.2;  	/**<width of one hex */
    const float  HEX_HEIGHT=0.18; 	/**<height of one hex*/
    /***
     *number of hex
     *for selection to work nuber of hex<=65536
     *for more hex: shader program need to be changed to include blue color too
     **/
    const int HEX_SIZE = 50000;
    const int HEX_LINE_NUM = 200;   /**<number of hex in one line*/

    GLuint box;
    GLuint position_vbo;
    GLint gbuffer_instanced_mvp_mat_loc;
    GLint gbuffer_instanced_normal_mat_loc;
    GLint gbuffer_instanced_view;
    GLint  gbuffer_instanced_pos;

    GLint gbuffer_instanced_mvp_mat_loc_sel;
    GLint gbuffer_instanced_normal_mat_loc_sel;
    GLint gbuffer_instanced_view_sel;
    GLint  gbuffer_instanced_pos_sel;

    vector<vec4> positions;
    CTexture hextex;
    GLuint tex;
    GLuint programsel;

};



#endif // NKHEX2_H
