#include "TestTexture.h"
#include <SOIL.h>

char TestTexture_vShaderStr[] = 
	"#version 330 core						\n"
	"layout(location = 0) in vec3 vPosition;\n"
	"layout(location = 1) in vec3 vColor;	\n"
	"layout(location = 2) in vec2 vTexCoord;\n"
	"out vec3 ourColor;						\n"
	"out vec2 TexCoord;						\n"
	"void main() 							\n"
	"{ 										\n"
	"	gl_Position = vec4(vPosition, 1.0f);\n"
	"	ourColor = vColor;					\n"
	"	TexCoord = vTexCoord;				\n"
	"}										\n";

char TestTexture_fShaderStr[] = 
	"#version 330 core							\n"
	"precision mediump float; 					\n"

	"in vec3 ourColor;							\n"
	"in vec2 TexCoord;							\n"

	"out vec4 fragColor; 						\n"

	"uniform sampler2D ourTexture1;				\n"
	"uniform sampler2D ourTexture2;				\n"

	"void main() 								\n"
	"{ 											\n"
	"	vec2 temp = vec2(1 -TexCoord.x, 1 - TexCoord.y);\n"
	"	vec4 texColor = mix(texture(ourTexture1, temp),texture(ourTexture2, temp), 0.0);\n"
	"	if(texColor.a < 0.1)					\n"
	"	{                                       \n"
	"		discard;							\n"
	"	}										\n"
	//"	fragColor = texture(ourTexture2, TexCoord);\n"
	//"	fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
	"	fragColor = texColor;\n"
	"} 											\n";

GLuint 	TestTexture::loadShader(GLenum type,const char* shaderSrc){
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

GLuint TestTexture::loadProgram(char* cVShader, char* cFShader)
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

void TestTexture::Init()
{
	program = loadProgram(TestTexture_vShaderStr, TestTexture_fShaderStr);

	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	GLuint texture[2];
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//GLfloat vertices[] = {
	////     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f    // 左下
	//};
		GLfloat vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.6f, 0.6f,   // 右上
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.6f, 0.5f,   // 右下
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.5f, 0.6f,   // 左上
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 0.5f    // 左下
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glUniform1i(glGetUniformLocation(program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glUniform1i(glGetUniformLocation(program, "ourTexture2"), 1);

	glBindVertexArray(0);
}

void TestTexture::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    glBindVertexArray(0);
}