/*
* dmObj.hpp
*
* Created on: Jan 24, 2012
* Author: Tofs
*/

#pragma once

#include "GL_utilities.h"
#include <algorithm>
#include <list>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>


class dMobj
{
	private:
		//GPU data
		unsigned int vertexBufferObjID;
		unsigned int indexBufferObjID;
		unsigned int normalBufferObjID;
		unsigned int texCoordBufferObjID;
		GLuint program;


		unsigned int vertexArrayObjID;
		unsigned int textureID;
		GLfloat * transformMatrix;

		//Raw vertexdata
		GLuint verticessize;
		GLfloat *vertices;
		GLuint normalsize;
		GLfloat *normals;
		GLuint vindexsize;
		GLushort *vindex;
		GLuint nindexsize;
		GLushort *nindex;
		
		//Class management
		bool init;
		int fileload(std::string path);
	public:
		dMobj();
		void dumpInfo();
		void render();
		int loadObjFromFile(std::string path);
		int loadShaderFromFile(std::string vShader, std::string fShader);
};

