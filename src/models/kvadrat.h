#include <GL/glew.h>
#include <iostream>
#include <string>

class NkKvadrat
{
private:
	//Graphics program
	GLuint gProgramID;
	GLint gVertexPos2DLocation;
	GLuint gVBO;
	GLuint gIBO;


public:
    NkKvadrat();
	void render();

private:
	void loadShaders();
	void printProgramLog( GLuint program );
	void printShaderLog( GLuint shader );
	
};
