#include "Base.h"

void Base::Init(char* cVShader, char* cFShader)
{
	program = loadProgram(cVShader, cFShader);
}

GLuint 	Base::loadShader(GLenum type,const char* shaderSrc){
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

GLuint Base::loadProgram(char* cVShader, char* cFShader)
{
	GLint success;
    GLchar infoLog[512];

	GLuint vShader = this->loadShader(GL_VERTEX_SHADER, cVShader);
	GLuint fShader = this->loadShader(GL_FRAGMENT_SHADER, cFShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success){
        glGetProgramInfoLog(program,512,NULL,infoLog);
        std::cout << "ERROR:PROGRAM:LINK_FAILED\n" << infoLog << std::endl;
		return 0;
    }
	glUseProgram(program);
	
    glDeleteShader(vShader);
    glDeleteShader(fShader);

	return program;
}