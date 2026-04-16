#include <sstream>
#include "game_state.h"
#include "pause_state.h"

Gamestate::Gamestate(GameDataRef data)
	: _data(data) { }

void Gamestate::init()
{
	_data->videomode.width = 860;
	_data->videomode.height = 600;
	_data->assets.loadFont("FONT1", "texts/Montserrat-BlackItalic.ttf");
	_data->assets.loadTexture("BG", "images/BG2.png");
	_data->assets.loadTexture("tHero1", "images/Hero_Trybyleaf.png");
	_data->assets.loadTexture("tHero2", "images/HeroTexture2.png");
	_data->assets.loadTexture("tEnemy", "images/astolfo.png");
	_data->assets.loadSound("Edeth", "sounds/hentaimoan.wav");

	if (this->_data->CurrentSkin == 1) {
		_hero.setTexture(_data->assets.GetTexture("tHero1"));
	}
	else if (this->_data->CurrentSkin == 2) {
		_hero.setTexture(_data->assets.GetTexture("tHero2"));
	}

	_enemy.setTexture(_data->assets.GetTexture("tEnemy"));

	_BG.setTexture(_data->assets.GetTexture("BG"));

	Enemy_Defeted.setBuffer(_data->assets.GetSound("Edeth"));
	this->Enemy_Defeted.setVolume(this->_data->volume);

	this->points = 0;

	this->max_enemies = 2;
	this->max_bullets = 5;

	this->view.setSize(860, 600);
	this->view.setCenter(430, 300);

	this->initExits();
	this->initHero();
	this->initText();
}


void Gamestate::initExits()
{
	while (this->enemies.size() <= this->max_enemies)
	{
		int side = rand() % 4;
		sf::Vector2f Pos;
		if (side == 0)
		{
			Pos.x = rand() % 4000;
			Pos.y = -150;
		}
		else if (side == 1)
		{
			Pos.x = -150;
			Pos.y = rand() % 2000;
		}
		else if (side == 2)
		{
			Pos.x = this->_data->videomode.width + 150;
			Pos.y = rand() % 2000;
		}
		else
		{
			Pos.x = rand() % 4000;
			Pos.y = this->_data->videomode.height + 150;
		}
		this->_enemy.setPosition(Pos);
		this->_enemy.setScale(sf::Vector2f(0.3f, 0.3f));
		this->enemies.push_back(this->_enemy);
		//std::cout << side << '\n';
	}
}

void Gamestate::dyingExit()
{
	for (int i = this->bullets.size() - 1; i >= 0; i--)
	{
		for (int j = this->enemies.size() - 1; j >= 0; j--)
		{
			if (this->bullets[i].sprite.getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
			{
				this->bullets.erase(bullets.begin() + i);
				this->enemies.erase(enemies.begin() + j);
				Enemy_Defeted.play();

				this->points += 1;
				
				this->initExits();

				break;
			}
		}
	}
}

void Gamestate::UpdateEnemies()
{
	for (int i = static_cast<int>(this->enemies.size()) - 1; i >= 0; i--)
	{
		sf::Vector2f HeroPos = _hero.getPosition();
		sf::Vector2f ExitPos = this->enemies[i].getPosition();
		sf::Vector2f dir = ExitPos - HeroPos;

		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len != 0) dir /= len;
		sf::Vector2f ExitSpeed = -dir * 2.f;
		this->enemies[i].move(ExitSpeed);
	}

	dyingExit();
}

void Gamestate::initHero()
{
	this->_hero.setScale(sf::Vector2f(2.f, 2.f));
	this->_hero.setPosition(sf::Vector2f(2000.f, 1000.f));
}

void Gamestate::Shooting()
{
	BulletS b;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->up = false;
		this->down = false;
		this->left = false;
		this->right = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->up = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->down = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->left = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->right = true;
		}

		if (right) {
			if (this->bullets.size() <= max_bullets)
			{
				b.sprite.setPosition(sf::Vector2f(this->_hero.getPosition().x + 50, this->_hero.getPosition().y + 25));
				b.sprite.setSize(sf::Vector2f(40.f, 10.f));
				b.velocity = sf::Vector2f(6.f, 0);
				b.direction = 1;
				this->bullets.push_back(b);
			}
		}
		else if (left) {
			if (this->bullets.size() <= max_bullets)
			{
				b.sprite.setPosition(sf::Vector2f(this->_hero.getPosition().x - 10, this->_hero.getPosition().y + 25));
				b.sprite.setSize(sf::Vector2f(40.f, 10.f));
				b.velocity = sf::Vector2f(-6.f, 0);
				b.direction = 2;
				this->bullets.push_back(b);
			}
		}
		else if (up) {
			if (this->bullets.size() <= max_bullets)
			{
				b.sprite.setPosition(sf::Vector2f(this->_hero.getPosition().x + 25, this->_hero.getPosition().y - 50));
				b.sprite.setSize(sf::Vector2f(10.f, 40.f));
				b.velocity = sf::Vector2f(0.f, -6.f);
				b.direction = 3;
				this->bullets.push_back(b);
			}
		}
		else if (down) {
			if (this->bullets.size() <= max_bullets)
			{
				b.sprite.setPosition(sf::Vector2f(this->_hero.getPosition().x + 25, this->_hero.getPosition().y + 50));
				b.sprite.setSize(sf::Vector2f(10.f, 40.f));
				b.velocity = sf::Vector2f(0.f, 6.f);
				b.direction = 4;
				this->bullets.push_back(b);
			}
		}
		else {
			if (this->bullets.size() <= max_bullets)
			{
				b.sprite.setPosition(sf::Vector2f(this->_hero.getPosition().x + 50, this->_hero.getPosition().y + 25));
				b.sprite.setSize(sf::Vector2f(40.f, 10.f));
				b.velocity = sf::Vector2f(6.f, 0);
				b.direction = 1;
				this->bullets.push_back(b);
			}
		}
	}
}

void Gamestate::SkinUpdate()
{
	if (this->_data->CurrentSkin == 1) {
		this->_hero.setTexture(_data->assets.GetTexture("tHero1"));
	}
	else if (this->_data->CurrentSkin == 2) {
		this->_hero.setTexture(_data->assets.GetTexture("tHero2"));
	}
}

void Gamestate::UpdateBullets()
{
	for (int i = static_cast<int>(this->bullets.size()) - 1; i >= 0; i--)
	{
		this->bullets[i].sprite.move(this->bullets[i].velocity);

		if (this->bullets[i].direction == 1) {
			if (this->bullets[i].sprite.getPosition().x > this->_hero.getPosition().x + 500) {
				this->bullets.erase(this->bullets.begin() + i);
			}
		}
		else if (this->bullets[i].direction == 2) {
			if (this->bullets[i].sprite.getPosition().x + 500 < this->_hero.getPosition().x) {
				this->bullets.erase(this->bullets.begin() + i);
			}
		}
		else if (this->bullets[i].direction == 3) {
			if (this->bullets[i].sprite.getPosition().y + 500 < this->_hero.getPosition().y) {
				this->bullets.erase(this->bullets.begin() + i);
			}
		}
		else if (this->bullets[i].direction == 4) {
			if (this->bullets[i].sprite.getPosition().y > this->_hero.getPosition().y + 500) {
				this->bullets.erase(this->bullets.begin() + i);
			}
		}
	}
}

void Gamestate::UpdateMoving()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->_hero.move(sf::Vector2f(-2.12f, -2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->_hero.move(sf::Vector2f(2.12f, -2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->_hero.move(sf::Vector2f(2.12f, 2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->_hero.move(sf::Vector2f(-2.12f, 2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->_hero.move(sf::Vector2f(-3.f, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->_hero.move(sf::Vector2f(3.f, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->_hero.move(sf::Vector2f(0.f, 3.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->_hero.move(sf::Vector2f(0.f, -3.f));
	}


	if (this->_hero.getPosition().x + 450 > this->_BG.getGlobalBounds().getSize().x)
	{
		this->_hero.move(-3.f, 0);
	}
	if (this->_hero.getPosition().y + 300 > this->_BG.getGlobalBounds().getSize().y)
	{
		this->_hero.move(0.f, -3.f);
	}
	if (this->_hero.getPosition().x - 435 < (this->_data->window->getSize().x - this->_data->videomode.width))
	{
		this->_hero.move(3.f, 0.f);
	}
	if (this->_hero.getPosition().y - 300 < (this->_data->window->getSize().y - this->_data->videomode.height))
	{
		this->_hero.move(0.f, 3.f);
	}
	for (auto& x : this->enemies)
	{
		if (this->_hero.getGlobalBounds().intersects(x.getGlobalBounds()))
		{
			this->_data->window->close();
		}
	}

	this->view.setCenter(this->_hero.getPosition());
	this->_data->window->setView(this->view);
}

void Gamestate::initText()
{
	this->_text.setPosition(this->_hero.getPosition().x, this->_hero.getPosition().y);
	this->_text.setString("hello");
	this->_text.setFillColor(sf::Color::White);
	this->_text.setCharacterSize(40);
	this->_text.setFont(_data->assets.GetFont("FONT1"));
}

void Gamestate::UpdateText()
{
	this->_text.setString(std::to_string(this->points));
	this->_text.setPosition(this->_hero.getPosition().x - 400, this->_hero.getPosition().y - 300);
}

void Gamestate::handleevent()
{
	sf::Event ev;
	while (_data->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) {
			_data->window->close();
		}

		if (ev.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::P == ev.key.code)
			{
				_data->machine.AddState(Sonar::StateRef(new PauseState(_data)), false);
			}
			else
			{
				this->Shooting();
			}
		}
	}
}

const bool Gamestate::Running() const
{
	return this->_data->window->isOpen();
}

void Gamestate::update(float dt)
{
	this->handleevent();
	this->UpdateBullets();
	this->UpdateMoving();
	this->UpdateEnemies();
	this->UpdateText();
	this->SkinUpdate();
}

void Gamestate::renderHero(sf::RenderTarget& target)
{
	target.draw(this->_hero);
}

void Gamestate::renderEnemies(sf::RenderTarget& target)
{
	for (auto& x : this->enemies)
	{
		target.draw(x);
	}
}

void Gamestate::renderBullets(sf::RenderTarget& target)
{
	for (auto& x : this->bullets)
	{
		target.draw(x.sprite);
	}
}

void Gamestate::renderBackround()
{
	this->_data->window->draw(this->_BG);
}

void Gamestate::renderText(sf::RenderTarget& target)
{
	this->_data->window->draw(this->_text);
}

void Gamestate::render(float dt)
{

	this->renderBackround();
	this->renderHero(*this->_data->window);
	this->renderText(*this->_data->window);
	this->renderEnemies(*this->_data->window);
	this->renderBullets(*this->_data->window);

}