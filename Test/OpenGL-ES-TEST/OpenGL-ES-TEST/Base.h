#ifndef __BASE_H__
#define __BASE_H__

#include "headFile.h"

class Base{
public:
	virtual void Init(char* cVShader, char* cFShader);
	virtual void Init() = 0;

	virtual void Draw() = 0;

	virtual GLuint loadShader(GLenum type,const char* shaderSrc);

	virtual GLuint loadProgram(char* cVShader, char* cFShader);
protected:
	GLuint program;
};

#endif //__BASE_H__