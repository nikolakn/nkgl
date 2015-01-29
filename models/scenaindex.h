#include "models/nkmodel.h"
#define HM_SIZE_X 4 // Dimensions of our heightmap
#define HM_SIZE_Y 4

class NKscenaIndex : public NKModel
{
private:

    unsigned int uiVBOHeightmapData; // Here are stored heightmap data (vertices)
    unsigned int uiVBOIndices; // And here indices for rendering heightmap

    unsigned int uiVAOHeightmap; // One VAO for heightmap

    bool bShowFPS = false;
    bool bVerticalSync = true;


float fRotationAngle;
const float PIover180 = 3.1415f/180.0f;


public:
    NKscenaIndex();
    void init();
    void render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView);
    void releaseScene();
	
};
