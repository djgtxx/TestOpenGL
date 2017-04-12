#include "Transfrom.h"
#include <SOIL.h>

char Transfrom_vShaderStr[] = 
	"#version 330 core						\n"
	"layout(location = 0) in vec3 vPosition;\n"
	"layout(location = 1) in vec3 vColor;	\n"
	"layout(location = 2) in vec2 vTexCoord;\n"
	"out vec3 ourColor;						\n"
	"out vec2 TexCoord;						\n"
	"uniform mat4 transform;				\n"
	"uniform mat4 view;						\n"
	"uniform mat4 projection;				\n"
	"void main() 							\n"
	"{ 										\n"
	"	gl_Position = projection * view * transform * vec4(vPosition, 1.0f);\n"
	"	ourColor = vColor;					\n"
	"	TexCoord = vTexCoord;				\n"
	"}										\n";

char Transfrom_fShaderStr[] = 
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
	"	vec4 texColor = mix(texture(ourTexture1, temp),texture(ourTexture2, temp), 0.2);\n"
	"	if(texColor.a < 0.1)					\n"
	"	{                                       \n"
	"		discard;							\n"
	"	}										\n"
	//"	fragColor = texture(ourTexture2, TexCoord);\n"
	//"	fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
	"	fragColor = texColor;\n"
	"} 											\n";

void Transfrom::Init()
{
	Base::Init(Transfrom_vShaderStr, Transfrom_fShaderStr);

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
	////     ---- Î»ÖÃ ----       ---- ÑÕÉ« ----     - ÎÆÀí×ø±ê -
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ÓÒÉÏ
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ÓÒÏÂ
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ×óÉÏ
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f    // ×óÏÂ
	//};
	// GLfloat vertices[] = {
	// //     ---- Î»ÖÃ ----       ---- ÑÕÉ« ----     - ÎÆÀí×ø±ê -
	// 	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ÓÒÉÏ
	// 	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ÓÒÏÂ
	// 	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ×óÉÏ
	// 	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f    // ×óÏÂ
	// };

	GLfloat vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
 //    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glUniform1i(glGetUniformLocation(program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glUniform1i(glGetUniformLocation(program, "ourTexture2"), 1);

	glm::mat4 trans;
	glm::mat4 view;
	glm::mat4 projection;
	GLuint viewLoc, projectionLoc;
	transLoc = glGetUniformLocation(program, "transform");
	viewLoc = glGetUniformLocation(program, "view");
	projectionLoc = glGetUniformLocation(program, "projection");
	// trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
	// trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	trans = glm::rotate(trans, -55.0f, glm::vec3(0.0, 0.0, 1.0));
	view = glm::translate(view, glm::vec3(0.0f, 0, -3.0f));
	projection = glm::perspective(60.0f, 800.0f/600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);

	glBindVertexArray(0);
}

void Transfrom::Draw()
{
	// glm::vec3 cubePositions[] = {
	//   glm::vec3( 0.0f,  0.0f,  0.0f), 
	//   glm::vec3( 2.0f,  5.0f, -15.0f), 
	//   glm::vec3(-1.5f, -2.2f, -2.5f),  
	//   glm::vec3(-3.8f, -2.0f, -12.3f),  
	//   glm::vec3( 2.4f, -0.4f, -3.5f),  
	//   glm::vec3(-1.7f,  3.0f, -7.5f),  
	//   glm::vec3( 1.3f, -2.0f, -2.5f),  
	//   glm::vec3( 1.5f,  2.0f, -2.5f), 
	//   glm::vec3( 1.5f,  0.2f, -1.5f), 
	//   glm::vec3(-1.3f,  1.0f, -1.5f)  
	// };

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
    glBindVertexArray(VAO);

 //    for(GLuint i = 0; i < 10; i++)
	// {
	//   glm::mat4 model;
	//   model = glm::translate(model, cubePositions[i]);
	//   GLfloat angle = (GLfloat)glfwGetTime() * 50.0f * i; 
	//   model = glm::rotate(model, angle, glm::vec3(0.1 * (i + 1), 0.3f, 1 - (0.1f * i)));
	//   glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(model));

	//   glDrawArrays(GL_TRIANGLES, 0, 36);
	// }

	glm::mat4 trans;
	// // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
    trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.4f, 0.2f, 0.7f));
	// // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawArrays(GL_TRIANGLES,0,36);
    // glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    glBindVertexArray(0);
}