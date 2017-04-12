#include "Simple_Texture2D.h"

const char vShaderSrc[] = 
	"#version 330 es 	\n"
	"layout(location = 0) in vec4 a_position; \n"
	"layout(location = 0) in vec2 a_texCoord; \n"
	"out vec2 v_texCoord; \n"
	"void main() \n"
	"{	\n"
	" 	gl_Position = a_position; \n"
	"	v_texCoord = a_texCoord; \n"
	"} \n";

const char fShaderSrc[] = 
	"#version 330 es \n"
	"precision medium float; \n"
	"in vec2 v_texCoord; \n"
	"layout(laction = 0) out vec4 outColor; \n"
	"uniform sampler2D s_texture; \n"
	"void main() \n"
	"{ \n"
	"	outColor = texture(s_texture,v_texCoord);\n"
	"} \n";


void Simple_Texture2D::Init(){
	GLuint programObject = this->loadProgram(vShaderSrc,fShaderSrc);
	textureLocation = glGetUniformLocation(programObject, "s_texture");

	textureID = CreateSimpleTexture2D ();

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}

void Simple_Texture2D::Draw(){
   	GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           -0.5f, -0.5f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };
  	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   	glClear ( GL_COLOR_BUFFER_BIT );

   	glUseProgram(program);

	   // Load the vertex position
	   glVertexAttribPointer ( 0, 3, GL_FLOAT,
	                           GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
	   // Load the texture coordinate
	   glVertexAttribPointer ( 1, 2, GL_FLOAT,
	                           GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );

	   glEnableVertexAttribArray ( 0 );
	   glEnableVertexAttribArray ( 1 );

	   // Bind the texture
	   glActiveTexture ( GL_TEXTURE0 );
	   glBindTexture ( GL_TEXTURE_2D, textureID );

	   // Set the sampler texture unit to 0
	   glUniform1i ( textureLocation, 0 );

	   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

GLuint Simple_Texture2D::loadProgram(const char* vShaderSrc, const char* fShaderSrc)
{
	GLuint vShader,fShader,program;
	GLint linked;

	vShader = loadShader(GL_VERTEX_SHADER, vShaderSrc);
	fShader = loadShader(GL_FRAGMENT_SHADER, fShaderSrc);

	if(vShader > 0 && fShader > 0){
		program = glCreateProgram();

		glAttachShader(program,vShader);
		glAttachShader(program,fShader);

		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if(!linked){
			char infoLog[512];
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout <<"ERROR::LINKED::FAILED::"<< infoLog << std::endl;
			return 0;
		}
	}else{
		return 0;
	}

	return program;
}

GLuint Simple_Texture2D::CreateSimpleTexture2D( )
{
   // Texture object handle
   GLuint textureId;

   // 2x2 Image, 3 bytes per pixel (R, G, B)
   GLubyte pixels[4 * 3] =
   {
      255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
      255, 255,   0  // Yellow
   };

   // Use tightly packed data
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

   // Generate a texture object
   glGenTextures ( 1, &textureId );

   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );

   // Load the texture
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );

   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

   return textureId;
}

GLuint Simple_Texture2D::loadShader(GLenum type, const char* shaderSrc)
{
	GLint compiled;

	GLuint vShader = glCreateShader(type);
	glShaderSource(vShader, 1, &shaderSrc, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &compiled);
	if(!compiled){
		char infoLog[512];
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILE_FAILED::" << infoLog << std::endl;

		glDeleteShader(vShader);

		return 0;
	}
	return vShader;
}