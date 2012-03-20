#include "StdAfx.h"
#include "Engien.h"
#include <algorithm>
#include <iterator>

Engien::Engien(void)
{
}


Engien::~Engien(void)
{
}





int Engien::init(int x,int y,bool fullscreen)
{


	if(fullscreen)
		window = new sf::Window(sf::VideoMode(x, y, 32), "Engien", sf::Style::Fullscreen, sf::ContextSettings(32, 8, 16, 4, 2));
	else
		window = new sf::Window(sf::VideoMode(x, y, 32), "Engien", sf::Style::Close, sf::ContextSettings(32, 8, 16, 4, 2));

	window->SetActive();
	activeScen = NULL;

	return 0;
}


int Engien::start()
{
	

	// Start the game loop
	while (window->IsOpen())
	{
		// Process events
		sf::Event event;
		while (window->PollEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
				window->Close();
		}

		activeScen->scenRef->renderScen();
		

		// Update the window
		window->Display();

	}

	return 0;
}



void Engien::activateScen(std::string referens)
{
	std::list<scenDub*>::iterator it;

	for(it = scens.begin(); it != scens.end(); it++)
	{
		if ((*it)->stringRef == referens)
		{
			activeScen = *it;
			return;
		}
	}
}

int Engien::addScen(scen *newScen, std::string referens)
{
	scenDub *newscendup = new scenDub;

	newscendup->scenRef = newScen;
	newscendup->stringRef = referens;

	scens.push_back(newscendup);

	if (activeScen == NULL)
	{
		activeScen = newscendup;
	}

	return 0;
}