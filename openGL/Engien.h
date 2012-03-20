#pragma once


#include <string>
#include <gl\glew.h>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Window.hpp>
#include <list>
#include "scen.h"


struct scenDub
{
	std::string stringRef;
	scen* scenRef;
};

class Engien
{
private:
	std::list<scenDub*> scens;
	scenDub* activeScen;
	sf::Window * window;
public:
	Engien(void);
	~Engien(void);

	int init(int x,int y,bool fullscreen);
	int addScen(scen *newScen, std::string referens); 
	int start();
	void activateScen(std::string referens);
};

