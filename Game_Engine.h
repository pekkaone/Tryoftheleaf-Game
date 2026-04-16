#pragma once

#include <iostream>
#include <vector>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

struct GameData
{
	Sonar::StateMachine machine;
	AssetManager assets;
	InputManager input;
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	float volume = 100;
	int CurrentSkin = 1;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game_Engine
{
private:
	
	sf::VideoMode videomode;
	sf::Event ev;

	sf::Clock clock;
	const float dt = 1.f / 60.f;
	GameDataRef _data = std::make_shared<GameData>();

	void Run();

public:
	Game_Engine();
};

