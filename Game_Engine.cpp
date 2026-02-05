#include "Game_Engine.h"

void Game_Engine::initVariables()
{
	this->window = nullptr;

	this->UP = 0;
	this->DOWN = 0;
	this->RIGH = 0;
	this->LEFT = 0;

	this->tHero.loadFromFile("Hero_Trybyleaf.png");
	this->sHero.setTexture(tHero);
}



void Game_Engine::initWindow()
{
	this->videomode.width = 600;
	this->videomode.height = 600;

	this->window = new sf::RenderWindow(this->videomode, "Can we go home", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game_Engine::initHero()
{
	this->sHero.setScale(sf::Vector2f(2.f, 2.f));
	this->sHero.setPosition(sf::Vector2f(videomode.height / 2, videomode.width / 2));
}

void Game_Engine::Moving()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->sHero.move(sf::Vector2f(-30.f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->sHero.move(sf::Vector2f(30.f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->sHero.move(sf::Vector2f(0.f, 30.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->sHero.move(sf::Vector2f(0.f, -30.f));
	}

}

Game_Engine::Game_Engine() {
	this->initVariables();
	this->initWindow();
	this->initHero();
}

Game_Engine::~Game_Engine()
{
	delete this->window;
}

const bool Game_Engine::Running() const
{
	return this->window->isOpen();
}


void Game_Engine::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			Moving();
			break;
		};
	}
}

void Game_Engine::update() {
	this->pollEvents();
}

void Game_Engine::renderHero(sf::RenderTarget& target)
{
	this->window->draw(this->sHero);
}

void Game_Engine::render()
{
	this->window->clear();

	this->renderHero(*this->window);

	this->window->display();
}

