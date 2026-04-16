#include "Game_Engine.h"
#include "game_state.h"

void Game_Engine::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;

	while (this->_data->window->isOpen())
	{
		this->_data->machine.ProcessStateChanges();

		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		};

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->handleevent();
			this->_data->machine.GetActiveState()->update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->window->clear();

		this->_data->machine.GetActiveState()->render(interpolation);

		this->_data->window->display();
	};
}

Game_Engine::Game_Engine() {
	_data->window = new sf::RenderWindow(sf::VideoMode(860, 600), "Can we go home", sf::Style::Titlebar | sf::Style::Close);
	_data->window->setFramerateLimit(60);
	_data->machine.AddState(Sonar::StateRef(new Gamestate(_data)));
	this->Run();
}

