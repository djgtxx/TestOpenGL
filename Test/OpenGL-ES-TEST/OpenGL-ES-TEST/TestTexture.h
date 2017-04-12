#ifndef __TEST_TEXTURE_H__
#define __TEST_TEXTURE_H__

#include "Base.h"
#include "Common.h"

class TestTexture : public Base{

public:
	virtual void 		Init();
	virtual void		Draw();
private:
	GLuint loadShader(GLenum type,const char* shaderSrc);

	GLuint loadProgram(char* cVShader, char* cFShader);

	GLuint VAO;
	GLuint program;
};

#endif //__TEST_TEXTURE_H__