#include "HelloTrangle.h"

char vShaderStr[] = 
	"#version 330 es 						\n"
	"layout(location = 0) in vec4 vPosition;\n"
	"void main() 							\n"
	"{ 										\n"
	"	gl_Position = vPosition; 			\n"
	"}										\n";

char fShaderStr[] = 
	"#version 330 es 							\n"
	"precision mediump float; 					\n"
	"out vec4 fragColor; 						\n"
	"void main() 								\n"
	"{ 											\n"
	"	fragColor = vec4(0.0f,1.0f,1.0f,1.0f); 	\n"
	"} 											\n";

void HelloTrangle::Init(){

	Base::Init(vShaderStr, fShaderStr);

	glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void HelloTrangle::Draw(){
	GLfloat vertices[] = {
		 0.0f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f 
	};

	//clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//use the program object
	glUseProgram(program);

	//load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}