#include <sstream>
#include "game_state.h"
#include "pause_state.h"

Gamestate::Gamestate(GameDataRef data)
	: _data(data),
	  Main_Hero(data),
	  anim(data)
{ }

void Gamestate::init()
{
	_data->videomode.width = 860;
	_data->videomode.height = 600;
	_data->assets.loadFont("FONT1", "texts/Montserrat-BlackItalic.ttf");
	_data->assets.loadTexture("BG", "images/BG2.png");
	_data->assets.loadTexture("tEnemy", "images/astolfo.png");
	_data->assets.loadTexture("tEnemy2", "images/TS2.png");
	_data->assets.loadSound("Edeth", "sounds/hentaimoan.wav");

	_BG.setTexture(_data->assets.GetTexture("BG"));

	Enemy_Defeted.setBuffer(_data->assets.GetSound("Edeth"));
	this->Enemy_Defeted.setVolume(this->_data->volume);

	this->points = 0;

	this->max_enemies = 2;

	this->view.setSize(860, 600);
	this->view.setCenter(430, 300);

	this->initExits();
	Main_Hero.initSword();
	Main_Hero.initHero();
	this->initText();
	this->limit = 5;

	anim.initAnimVariables();
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

		int skin = rand() % 2;
		if (skin == 1) {
			this->_enemy.setTexture(_data->assets.GetTexture("tEnemy"));
		}
		else {
			this->_enemy.setTexture(_data->assets.GetTexture("tEnemy2"));
		}
		
		
		this->_enemy.setPosition(Pos);
		this->_enemy.setScale(sf::Vector2f(0.3f, 0.3f));
		this->enemies.push_back(this->_enemy);
		//std::cout << side << '\n';
	}
}

void Gamestate::dyingExit()
{
	for (int i = this->Main_Hero.getBullets().size() - 1; i >= 0; i--)
	{
		for (int j = this->enemies.size() - 1; j >= 0; j--)
		{
			if (this->Main_Hero.getBullets()[i].sprite.getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
			{
				this->Main_Hero.getBullets().erase(Main_Hero.getBullets().begin() + i);
				this->enemies.erase(enemies.begin() + j);
				Enemy_Defeted.play();

				this->points += 1;
				
				this->initExits();

				break;
			}
		}
	}
}

void Gamestate::SwordKilling()
{
	for (int j = this->enemies.size() - 1; j >= 0; j--)
	{
		if (this->enemies[j].getGlobalBounds().intersects(this->Main_Hero.getSword().getGlobalBounds()))
		{
			this->enemies.erase(enemies.begin() + j);
			Enemy_Defeted.play();

			this->points += 1;
			this->initExits();
			break;
		}
	}
}

void Gamestate::UpdateEnemies()
{
	for (int i = static_cast<int>(this->enemies.size()) - 1; i >= 0; i--)
	{
		sf::Vector2f HeroPos = Main_Hero.getPosition();
		sf::Vector2f ExitPos = this->enemies[i].getPosition();
		sf::Vector2f dir = ExitPos - HeroPos;

		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len != 0) dir /= len;
		sf::Vector2f ExitSpeed = -dir * 2.f;
		this->enemies[i].move(ExitSpeed);

		if (this->points > limit) {
			this->max_enemies += 5;
			this->limit += 5;
		}
	}

	dyingExit();
}

void Gamestate::VolumeUpdate()
{
	this->Enemy_Defeted.setVolume(this->_data->volume);
}

void Gamestate::initText()
{
	this->_text.setPosition(Main_Hero.getPosition().x, Main_Hero.getPosition().y);
	this->_text.setString("hello");
	this->_text.setFillColor(sf::Color::White);
	this->_text.setCharacterSize(40);
	this->_text.setFont(_data->assets.GetFont("FONT1"));
}

void Gamestate::UpdateText()
{
	this->_text.setString(std::to_string(this->points));
	this->_text.setPosition(Main_Hero.getPosition().x - 400, Main_Hero.getPosition().y - 300);
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
				Main_Hero.Shooting();
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
	Main_Hero.Swording(this->mousePos);
	Main_Hero.UpdateBullets();
	Main_Hero.UpdateMoving(this->enemies, this->view, this->_BG);
	this->UpdateEnemies();
	this->UpdateText();
	Main_Hero.SkinUpdate();
	this->SwordKilling();
	this->VolumeUpdate();
	this->anim.UpdateHeroAnimation(Main_Hero.getCurrentState(), _data->CurrentSkin, Main_Hero.getSprite());
}

void Gamestate::renderEnemies(sf::RenderTarget& target)
{
	for (auto& x : this->enemies)
	{
		target.draw(x);
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
	Main_Hero.renderSword(*this->_data->window);
	Main_Hero.renderHero(*this->_data->window);
	this->renderText(*this->_data->window);
	this->renderEnemies(*this->_data->window);
	Main_Hero.renderBullets(*this->_data->window);

}