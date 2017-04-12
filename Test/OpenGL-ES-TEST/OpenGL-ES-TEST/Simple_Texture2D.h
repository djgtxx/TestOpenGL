#ifndef __SIMEPLE_TEXTURE_2D_H__
#define __SIMEPLE_TEXTURE_2D_H__

#include "base.h"
#include "Common.h"

class Simple_Texture2D : public Base{

public:
	virtual void Init();
	virtual void Draw();
private:
	GLuint loadProgram(const char* vShaderSrc, const char* fShaderSrc);
	GLuint loadShader(GLenum type, const char* shaderSrc);
	GLuint CreateSimpleTexture2D();
private:
	GLuint textureID;
	GLuint textureLocation;
	GLuint program;
};

#endif //__SIMEPLE_TEXTURE_2D_H__