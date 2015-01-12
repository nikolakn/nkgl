#pragma once

/********************************

Class:	CShader

Purpose:	Wraps OpenGL shader loading
			and compiling.

********************************/

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
typedef  unsigned int UINT;

class CShader
{
public:
	bool LoadShader(string sFile, int a_iType);
	void DeleteShader();

	bool IsLoaded();
	UINT GetShaderID();

	CShader();

private:
	UINT uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};

/********************************

Class:	CShaderProgram

Purpose: Wraps OpenGL shader program
		and make its usage easy.

********************************/

class CShaderProgram
{
public:
	void CreateProgram();
	void DeleteProgram();

	bool AddShaderToProgram(CShader* shShader);
	bool LinkProgram();

	void UseProgram();

    UINT GetProgramID() {return uiProgram;}

	CShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};
