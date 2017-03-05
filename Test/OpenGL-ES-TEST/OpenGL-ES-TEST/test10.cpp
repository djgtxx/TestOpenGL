#include "test10.h"

const GLchar* vertexShaderSource = 
	"#version 330 core			                                    \n"
    "layout (location = 0) in vec3 position;                        \n"
    "void main()                                                    \n"
    "{                                                              \n"
    "   gl_Position = vec4(position.x,position.y,position.z,1.0);   \n"
    "}                                                              \n"
;

const GLchar* fragmentShaderSource = 
    "#version 330 core                      \n"
    "out vec4 color;                        \n"
    "void main()                            \n"
    "{                                      \n"
    "   color = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
    "}                                       \n"
;


void Test10::Init()
{
	GLfloat vertices[] = {
		-0.5f,	-0.5f,	0.0f,
		 0.5f,	-0.5f,	0.0f,
		 0.0f,	 0.5f,	0.0f
	};

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR:SHADER:VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout << "ERROR:PROGRAM:LINK_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Test10::Draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);
}
