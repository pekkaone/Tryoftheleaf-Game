#pragma once

#include <iostream>
#include <vector>

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

	int max_exits;
	sf::RectangleShape exit;
	std::vector<sf::RectangleShape> exits;
	int max_bullets;
	sf::RectangleShape bullet;
	std::vector<sf::RectangleShape> bullets;
	

	sf::Texture tHero;
	sf::Sprite sHero;

	bool UP, DOWN, RIGH, LEFT;

	void initVariables();
	void initWindow();
	void initExit();
	void initHero();
	void initExits();

	void Shooting();
	void Moving();

public:
	Game_Engine();
	virtual ~Game_Engine();

	const bool Running() const;

	void UpdateBullets();

	void pollEvents();

	void update();

	void renderHero(sf::RenderTarget& target);
	// void renderExit(sf::RenderTarget& target);
	void renderExits(sf::RenderTarget& target);
	void renderBullets(sf::RenderTarget& target);
	void render();
};

