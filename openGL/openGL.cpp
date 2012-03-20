// openGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engien.h"
#include "openGLwrap.hpp"
#include "stdafx.h"
#include <iostream>
#include <fstream>

//Linking
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")







unsigned int vertexArrayObjID;
sf::Shader shader;


GLfloat vertices[] = {	
	-0.5f,	-0.5f,	0.0f,
	-0.5f,	0.5f,	0.0f,
	0.5f,	-0.5f,	0.0f 
};


int program;

int sfInit()
{
	glewExperimental=true;
	glewInit();

	return 0;

}




int sfRender()
{

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	

	glBindVertexArray(vertexArrayObjID); // Bind our Vertex Array Object
	glDrawArrays(GL_TRIANGLES, 0, 3); // Draw our square
	glBindVertexArray(0); // Unbind our Vertex Array Object


	glFlush();



	
	return 0;

}



int _tmain(int argc, _TCHAR* argv[])
{
	sfInit();

	Engien moop;
	moop.init(600,400, false);
	moop.addScen(new scen(), "test_scen");
	moop.activateScen("test_scen");

	moop.start();
	return 0;
}

