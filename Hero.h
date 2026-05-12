#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game_Engine.h"
#include "Animation.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING, MOVING_RIGHT, MOVING_LEFT,	DYING};

class Hero {
private:
	GameDataRef _data;

	bool up;
	bool down;
	bool left;
	bool right;

	short animState;

	Animation an;

	float dt;
	float adddt;
	
	sf::Sprite _hero;
	sf::IntRect sheet;

	int max_bullets;
	struct BulletS
	{
		sf::Vector2f velocity;
		sf::RectangleShape sprite;
		int direction;
		// 2 - Left, 1 - Right, 3 - Up, 4 - Down 
	};

	struct Sword {
		sf::Sprite sword_sprite;
		float direction;
	};

	sf::RectangleShape bullet;
	std::vector<BulletS> bullets;

	Sword sword;
	BulletS b;
public:
	Hero(GameDataRef data);

	void Swording(sf::Vector2f mousePos);
	void Shooting();
	void SkinUpdate();
	void initHero();
	void initSword();

	sf::Vector2f getPosition() const;
	sf::Sprite& getSprite();
	short getCurrentState();
	std::vector<BulletS>& getBullets();
	sf::Sprite& getSword();

	void UpdateBullets();
	void UpdateMoving(std::vector<sf::Sprite> enemies, sf::View view, sf::Sprite BG);

	void renderHero(sf::RenderTarget& target);
	void renderBullets(sf::RenderTarget& target);
	void renderSword(sf::RenderTarget& target);
};