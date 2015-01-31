#ifndef NKTUT1_H
#define NKTUT1_H

#include "nkmodel.h"



class NKTut1 : public NkModel
{
public:
    NKTut1();
    ~NKTut1();

    // NKModel interface
private:
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
};

#endif // NKTUT1_H
