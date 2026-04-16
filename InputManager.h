#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

	sf::Vector2i GetMousePos(sf::RenderWindow& window);
	
private:

};