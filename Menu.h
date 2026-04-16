#pragma once

#include <SFML/Graphics.hpp>

class Menu {
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	void initWindow();
	void initVariables();
public:
	Menu();
	virtual ~Menu();

	void render();
	void update();
};