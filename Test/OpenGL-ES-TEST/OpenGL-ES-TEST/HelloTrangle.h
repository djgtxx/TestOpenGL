#pragma once
#include "base.h"
#include "Common.h"
class HelloTrangle :
	public Base
{
public:
	virtual void Init();
	virtual void Draw();
private:
	GLuint 	loadShader(GLenum type,const char* shaderSrc);
	GLuint shaderProgram;
};

