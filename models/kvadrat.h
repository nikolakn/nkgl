#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>

class NKkvadrat
{
private:
	//Graphics program
	GLuint gProgramID;
	GLint gVertexPos2DLocation;
	GLuint gVBO;
	GLuint gIBO;


public:
    NKkvadrat();
	void render();

private:
	void loadShaders();
	void printProgramLog( GLuint program );
	void printShaderLog( GLuint shader );
	
};
