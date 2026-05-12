#pragma once

#include <iostream>
#include <vector>
#include "Animation.h"
#include "Hero.h"

#include "State.h"
#include "Game_Engine.h"

class Gamestate : public State
{
public:
	Gamestate(GameDataRef data);

	const bool Running() const;

	void init();

	void handleevent();

	void UpdateEnemies();
	void UpdateText();
	void update(float dt);

	void renderEnemies(sf::RenderTarget& target);
	void renderBackround();
	void renderText(sf::RenderTarget& target);
	void render(float dt);

private:
	GameDataRef _data;
	Animation anim;

	sf::Mouse mouse;
	sf::Vector2f mousePos;

	int points;
	int limit;
	int max_enemies;
	sf::Texture exitTexture;
	sf::Sprite _enemy;
	std::vector<sf::Sprite> enemies;

	Hero Main_Hero;

	sf::View view;

	sf::Sound Enemy_Defeted;

	sf::Sprite _BG;
	sf::Text _text;
	sf::Text _stats;

	void initExits();
	void initText();

	void dyingExit();
	void SwordKilling();

	void VolumeUpdate();
};
