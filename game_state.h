#pragma once

#include <iostream>
#include <vector>

#include "State.h"
#include "Game_Engine.h"

class Gamestate : public State
{
public:
	Gamestate(GameDataRef data);

	const bool Running() const;

	void init();

	void handleevent();

	void UpdateBullets();
	void UpdateEnemies();
	void UpdateMoving();
	void UpdateText();
	void update(float dt);

	void renderHero(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void renderBullets(sf::RenderTarget& target);
	void renderBackround();
	void renderText(sf::RenderTarget& target);
	void render(float dt);

private:

	int points;

	int max_enemies;
	sf::Texture exitTexture;
	sf::Sprite _enemy;
	std::vector<sf::Sprite> enemies;

	int max_bullets;
	struct BulletS
	{
		sf::Vector2f velocity;
		sf::RectangleShape sprite;
		int direction;
		// 2 - Left, 1 - Right, 3 - Up, 4 - Down 
	};

	sf::RectangleShape bullet;
	std::vector<BulletS> bullets;
	bool up;
	bool down;
	bool left;
	bool right;

	sf::Sprite _hero;

	sf::View view;

	sf::Sound Enemy_Defeted;

	GameDataRef _data;
	
	sf::Sprite _BG;
	sf::Text _text;
	sf::Text _stats;

	void initHero();
	void initExits();
	void initText();

	void dyingExit();
	void Shooting();
	void SkinUpdate();
};
