#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

#include <GL/glew.h>

// Some useful defines

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()

class CShader
{
public:
    bool loadShader(string sFile, int a_iType);
    void deleteShader();

    bool isLoaded();
    unsigned int getShaderID();

	CShader();

private:
    unsigned int uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};


//Wraps OpenGL shader program
//and make its usage easy.


class CShaderProgram
{
public:
    void createProgram();
    void deleteProgram();

    bool addShaderToProgram(CShader* shShader);
    bool linkProgram();

    void useProgram();

    unsigned int getProgramID() {return uiProgram;}

	CShaderProgram();

private:
    unsigned int uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};
