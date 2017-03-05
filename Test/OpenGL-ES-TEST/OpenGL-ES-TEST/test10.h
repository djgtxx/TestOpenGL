#ifndef __TEST_10_H__
#define __TEST_10_H__

#include "Base.h"
#include "Common.h"

class Test10 : public Base{
public:
	virtual void 		Init();
	virtual void		Draw();
private:
	GLuint VAO;
	GLuint shaderProgram;
};

#endif //__TEST_10_H__