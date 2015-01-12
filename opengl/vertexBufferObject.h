#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <string>
#include <vector>

using namespace std;


class CVertexBufferObject
{
public:
	void createVBO(int a_iSize = 0);
	void releaseVBO();

	void* mapBufferToMemory(int iUsageHint);
    void* mapSubBufferToMemory(int iUsageHint, unsigned int uiOffset, unsigned int uiLength);
	void unmapBuffer();

	void bindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void uploadDataToGPU(int iUsageHint);
	
    void addData(void* ptrData, unsigned int uiDataSize);

    char* getDataPointer();
    unsigned int getBuffer();

	CVertexBufferObject();

private:
    unsigned int uiBuffer;
	int iSize;
	int iBufferType;
    vector<char> data;

	bool bDataUploaded;
};
