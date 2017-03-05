#ifndef __COMMON_H__
#define __COMMON_H__

#include "Base.h"
#include <iostream>
#include <functional>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
 
// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int StartDraw(Base* test);

#endif //__COMMON_H__