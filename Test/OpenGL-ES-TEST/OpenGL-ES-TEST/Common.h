#ifndef __COMMON_H__
#define __COMMON_H__

#include "headFile.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int StartDraw(Base* test);

#endif //__COMMON_H__