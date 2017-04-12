#ifndef __TEST_TEXTURE_H__
#define __TEST_TEXTURE_H__

#include "Base.h"
#include "Common.h"

class TestTexture : public Base{

public:
	virtual void 		Init();
	virtual void		Draw();
private:
	GLuint VAO;
};

#endif //__TEST_TEXTURE_H__