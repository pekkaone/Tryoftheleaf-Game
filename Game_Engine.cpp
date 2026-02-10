#include "Game_Engine.h"

void Game_Engine::initVariables()
{
	this->window = nullptr;

	this->max_exits = 5;
	this->max_bullets = 10;

	this->tHero.loadFromFile("Hero_Trybyleaf.png");
	this->sHero.setTexture(tHero);
}



void Game_Engine::initWindow()
{
	this->videomode.width = 860;
	this->videomode.height = 600;

	this->window = new sf::RenderWindow(this->videomode, "Can we go home", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game_Engine::initExit()
{
	this->exit.setFillColor(sf::Color::Red);
	this->exit.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->exit.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->exit.getSize().y))
	);
	this->exit.setSize(sf::Vector2f(100, 100));
}

void Game_Engine::initHero()
{
	this->sHero.setScale(sf::Vector2f(2.f, 2.f));
	this->sHero.setPosition(sf::Vector2f(videomode.height / 2, videomode.width / 2));
}

void Game_Engine::initExits()
{
	while (this->exits.size() <= max_exits)
	{
		this->exit.setFillColor(sf::Color::Red);
		this->exit.setPosition(
			static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->exit.getSize().x)),
			static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->exit.getSize().y))
		);
		this->exit.setSize(sf::Vector2f(100, 100));
		this->exits.push_back(this->exit);
	}
}

void Game_Engine::Shooting()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (this->bullets.size() <= max_bullets)
		{
			this->bullet.setPosition(sf::Vector2f(this->sHero.getPosition().x + 50 ,this->sHero.getPosition().y + 25));
			this->bullet.setSize(sf::Vector2f(40.f, 10.f));
			this->bullets.push_back(this->bullet);
		}
	}
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
	for (auto& x : this->exits)
	{
		if (this->sHero.getGlobalBounds().intersects(x.getGlobalBounds()))
		{
			this->window->close();
		}
	}
}

Game_Engine::Game_Engine() {
	this->initVariables();
	this->initWindow();
	this->initHero();
	this->initExit();
	this->initExits();
}

Game_Engine::~Game_Engine()
{
	delete this->window;
}

const bool Game_Engine::Running() const
{
	return this->window->isOpen();
}

void Game_Engine::UpdateBullets()
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].move(6.f, 0.f);

		if (this->bullets[i].getPosition().x > this->window->getSize().x)
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
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
			Shooting();
			break;
		};
	}
}

void Game_Engine::update() {
	this->pollEvents();
	this->UpdateBullets();
}

void Game_Engine::renderHero(sf::RenderTarget& target)
{
	this->window->draw(this->sHero);
}

void Game_Engine::renderExits(sf::RenderTarget& target)
{
	for (auto& x : this->exits)
	{
		target.draw(x);
	}
}

void Game_Engine::renderBullets(sf::RenderTarget& target)
{
	for (auto& x : this->bullets)
	{
		target.draw(x);
	}
}

void Game_Engine::render()
{
	this->window->clear();

	this->renderExits(*this->window);
	this->renderBullets(*this->window);
	this->renderHero(*this->window);

	this->window->display();
}

