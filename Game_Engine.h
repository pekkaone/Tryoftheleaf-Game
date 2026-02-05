#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Game_Engine
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;
	sf::RectangleShape hero;

	sf::Texture tHero;
	sf::Sprite sHero;

	bool UP, DOWN, RIGH, LEFT;

	void initVariables();
	void initWindow();
	void initHero();

	void Moving();

public:
	Game_Engine();
	virtual ~Game_Engine();

	const bool Running() const;

	void pollEvents();

	void update();

	void renderHero(sf::RenderTarget& target);
	void render();
};

