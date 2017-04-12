#ifndef __TRANSFROM_H__
#define __TRANSFROM_H__

#include "Base.h"
#include "Common.h"

class Transfrom : public Base{

public:
	virtual void 		Init();
	virtual void		Draw();
private:
	GLuint VAO;
	GLuint transLoc;
};

#endif //__TRANSFROM_H__