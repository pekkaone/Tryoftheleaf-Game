#pragma once

#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "Game_Engine.h"

class PauseState : public State
{
public:
	PauseState(GameDataRef data);

	void init();

	void handleevent();

	void updateButtonSett();
	void update(float dt);

	void renderButtonSett(sf::RenderTarget& target);
	void renderBG(sf::RenderTarget& target);
	void render(float dt);

private:
	GameDataRef _data;

	void initButtonSett();
	void initButtSett_mesh();
	void ButtonSettPress();

	sf::Sprite BG;

	sf::Mouse mouse;
	sf::Vector2f mousePos;

	sf::RectangleShape ButtSett_mesh;
	sf::Text Button_sett;

	sf::View view;

	sf::Text _text;
};
