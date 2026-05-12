#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Game_Engine.h"

class Animation
{
private:
	GameDataRef _data;

	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	sf::Sound HeroDeath;

public:
	Animation(GameDataRef data);

	bool SoundPlaying;

	void initAnimVariables();
	void UpdateHeroAnimation(short AnimState,
		bool skin, sf::Sprite& hero);
	void DoNothing();
	bool SoundStatus();
};