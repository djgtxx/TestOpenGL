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

GLuint 	HelloTrangle::loadShader(GLenum type,const char* shaderSrc){
	GLuint shader;
	GLint compiled;

	//Create the shader object
	shader = glCreateShader(type);

	if(shader == 0)
	{
		return 0;
	}

	//load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	//Compile the shader
	glCompileShader(shader);

	//check the compile statsu
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled){
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 0){
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILE::FAILED::" << infoLog << std::endl;
		}

		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

void HelloTrangle::Init(){
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	//load the vertex/fragment shaders
	vertexShader = loadShader(GL_VERTEX_SHADER,vShaderStr);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER,fShaderStr);

	//create the program object
	shaderProgram = glCreateProgram();

	if(shaderProgram == 0){
		return;
	}

	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);

	//Link the program
	glLinkProgram(shaderProgram);

	//check the link status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if(!linked){
		GLint infoLen  = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &linked);

		if(infoLen > 0){
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::LINK::FAILED::" << infoLog << std::endl;
		}
		glDeleteProgram(shaderProgram);
		return;
	}

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
	glUseProgram(shaderProgram);

	//load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}