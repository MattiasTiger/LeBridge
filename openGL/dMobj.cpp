/*
* dmObj.cpp
*
* Created on: Jan 24, 2012
* Author: Tofs
*/

#include "stdafx.h"
#include "dMobj.h"


dMobj::dMobj()
{
	init = false;
}

void dMobj::dumpInfo()
{
	std::cout << "Dumping obj data" << std::endl;
	std::cout << "vertex:" << std::endl;
	for(GLuint i = 0; i < verticessize / 4; i++)
	{
		std::cout
		<< vertices[4*i] << " "
		<< vertices[4*i+1] << " "
		<< vertices[4*i+2] << " "
		<< vertices[4*i+3] << " " << std::endl;
	}


	std::cout << "normals:" << std::endl;
	for(GLuint i = 0; i < normalsize/ 4; i++)
	{
		std::cout
		<< normals[4*i] << " "
		<< normals[4*i+1] << " "
		<< normals[4*i+2] << " "
		<< normals[4*i+3] << " " << std::endl;
	}

	std::cout << "vertexindes:" << std::endl;
	for(GLuint i = 0; i < vindexsize / 3; i++)
	{
		std::cout
		<< vindex[3*i] << " "
		<< vindex[3*i+1] << " "
		<< vindex[3*i+2] << " " << std::endl;
	}

	std::cout << "normalindex:" << std::endl;
	for(GLuint i = 0; i < nindexsize / 3; i++)
	{
		std::cout
		<< nindex[3*i] << " "
		<< nindex[3*i+1] << " "
		<< nindex[3*i+2] << " " << std::endl;
	}


}

int dMobj::loadObjFromFile(std::string path)
{
	fileload(path);

	
	glGenVertexArrays(1, &vertexArrayObjID);
	glGenBuffers(1, &vertexBufferObjID);
	glGenBuffers(1, &indexBufferObjID);
	glGenBuffers(1, &normalBufferObjID);
	glGenBuffers(1, &texCoordBufferObjID);

	glBindVertexArray(vertexArrayObjID);

	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, verticessize*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));	

	// VBO for normal data
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, normalsize*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nindexsize*sizeof(GLuint), nindex, GL_STATIC_DRAW);

	// TEXTURES - coords
	//TODO: Add texure suport

	/*
		if (m->texCoordArray == NULL)
    	{
  		std::cout << "m->texCoordArray == NULL\n";
		int count = m->numVertices*2;
		m->texCoordArray = new GLfloat[count];
		for(int i = 0; i < count; i++) {
			m->texCoordArray[i] = ((float)i)/((float)count);
		}	
	}

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices*2*sizeof(GLfloat), m->texCoordArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "inTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(program, "inTexCoord"));
	*/
}

int loadShaderFromFile(std::string vShader, std::string fShader)
{
	loadShaders(vShader.c_str(), fShader.c_str());
	return 0;
}

void dMobj::render()
{


}




int dMobj::fileload(std::string path)
{
	init = true;

	std::ifstream fileStream(path.c_str(), std::ifstream::in);

	std::list<GLfloat> vList;
	std::list<GLfloat> nList;
	std::list<GLuint> viList;
	std::list<GLuint> niList;

	GLfloat x, y, z;
	GLint n1, n2, n3, v1, v2, v3;

	std::string line;


	//Reads the file
	while(!fileStream.eof())
	{
		getline(fileStream, line);
		if (line.size() == 0)
		{

		}
		else if(line[0] == '#') // Comment
		{

		}
		else if(line[0] == 'g') //Group
		{

		}
		else if(line[0] == 'v' && line[1] == 'n') // Normals
		{
			std::stringstream stream(line);
			std::string str;
			stream >> str;
			stream >> x >> y >> z;
			nList.push_back(x);
			nList.push_back(y);
			nList.push_back(z);
			nList.push_back(1.0f);

		}
		else if(line[0] == 'v') // Vector point
		{
			std::stringstream stream(line);
			std::string str;
			stream >> str;
			stream >> x >> y >> z;
			vList.push_back(x);
			vList.push_back(y);
			vList.push_back(z);
			vList.push_back(1.0f);
		}
		else if (line[0] == 'f') // Faces (combinds stuffs, Needs to handle more then one "case"
		{
			std::replace(line.begin(), line.end(), '/', ' ');
			std::stringstream stream(line);
			std::string str;
			stream >> str;
			stream >> v1 >> n1
			>> v2 >> n2
			>> v3 >> n3;
			viList.push_back(v1);
			viList.push_back(v2);
			viList.push_back(v3);
			niList.push_back(n1);
			niList.push_back(n2);
			niList.push_back(n3);
		}
	}


	//Creates areys from the list containing the data
	verticessize = vList.size();
	vertices = new GLfloat[verticessize];
	for (GLuint i = 0; i < verticessize; i++)
	{
		vertices[i] = vList.front();
		vList.pop_front();
	}

	normalsize = nList.size();
	normals = new GLfloat[normalsize];
	for (GLuint i = 0; i < normalsize; i++)
	{
		normals[i] = nList.front();
		nList.pop_front();
	}


	vindexsize = viList.size();
	vindex = new GLushort[vindexsize];
	for (GLuint i = 0; i < vindexsize; i++)
	{
		vindex[i] = viList.front();
		viList.pop_front();
	}


	nindexsize = niList.size();
	nindex = new GLushort[nindexsize];
	for (GLuint i = 0; i < nindexsize; i++)
	{
		nindex[i] = niList.front();
		niList.pop_front();
	}




	return 0;

}


