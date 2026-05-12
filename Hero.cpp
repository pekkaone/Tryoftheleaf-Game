#include "Hero.h"

Hero::Hero(GameDataRef data) 
	: _data(data),
	  an(data)
{}

void Hero::initHero()
{
	_data->assets.loadTexture("tHero1", "images/HeroTryLeaf.png");
	_data->assets.loadTexture("tHero2", "images/HeroTexture2.png");
	_data->assets.loadSound("ADEath", "sounds/Death.wav");
	

	if (this->_data->CurrentSkin == 1) {
		_hero.setTexture(_data->assets.GetTexture("tHero1"));
		_hero.setTextureRect(sf::IntRect(0, 0, 30, 30));
	}
	else if (this->_data->CurrentSkin == 2) {
		_hero.setTexture(_data->assets.GetTexture("tHero2"));
	}

	_hero.setScale(sf::Vector2f(2.f, 2.f));
	_hero.setPosition(sf::Vector2f(2000.f, 1000.f));

	this->max_bullets = 5;
	this->animState = IDLE;

	this->dt = 0.f;
	this->adddt = 0.05f;
}

void Hero::initSword()
{
	_data->assets.loadTexture("d", "images/Swiord.png");

	this->sword.sword_sprite.setTexture(_data->assets.GetTexture("d"));
	this->sword.sword_sprite.setScale(2.5f, 2.5f);
	// this->_hero.getPosition().x + 10, this->_hero.getPosition().y + 10
	this->sword.sword_sprite.setPosition(2000.f, 1000.f);
	this->sword.sword_sprite.setOrigin(0, 4);
}

sf::Vector2f Hero::getPosition() const
{
	return this->_hero.getPosition();
}

sf::Sprite& Hero::getSprite()
{
	return this->_hero;
}

short Hero::getCurrentState()
{
	return this->animState;
}

std::vector<Hero::BulletS>& Hero::getBullets()
{
	return this->bullets;
}

sf::Sprite& Hero::getSword()
{
	return this->sword.sword_sprite;
}

void Hero::Swording(sf::Vector2f mousePos)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);
	sf::Vector2f dir = mousePos - sword.sword_sprite.getPosition();
	sword.direction = atan2(dir.y, dir.x) * 180 / 3.14f;

	this->sword.sword_sprite.setPosition(this->_hero.getPosition().x + 30, this->_hero.getPosition().y + 25);
	this->sword.sword_sprite.setRotation(sword.direction);
}

void Hero::Shooting() {
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

void Hero::SkinUpdate()
{
	if (this->_data->CurrentSkin == 1) {
		this->_hero.setTexture(_data->assets.GetTexture("tHero1"));
	}
	else if (this->_data->CurrentSkin == 2) {
		this->_hero.setTexture(_data->assets.GetTexture("tHero2"));
	}
}

void Hero::UpdateBullets()
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

void Hero::UpdateMoving(const std::vector<sf::Sprite> enemies, sf::View view, sf::Sprite BG)
{
	if (animState == DYING) {
		this->dt += adddt;
		an.UpdateHeroAnimation(this->animState, _data->CurrentSkin, this->_hero);

		if (dt >= 3.f) {
			this->_data->window->close();
		}
		return;
	}
	animState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->_hero.move(sf::Vector2f(-2.12f, -2.12f));
		animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->_hero.move(sf::Vector2f(2.12f, -2.12f));
		animState = MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->_hero.move(sf::Vector2f(2.12f, 2.12f));
		animState = MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->_hero.move(sf::Vector2f(-2.12f, 2.12f));
		animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->_hero.move(sf::Vector2f(-3.f, 0));
		animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->_hero.move(sf::Vector2f(3.f, 0));
		animState = MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->_hero.move(sf::Vector2f(0.f, 3.f));
		animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->_hero.move(sf::Vector2f(0.f, -3.f));
		animState = MOVING_LEFT;
	}


	if (this->_hero.getPosition().x + 450 > BG.getGlobalBounds().getSize().x)
	{
		this->_hero.move(-3.f, 0);
		animState = IDLE;
	}
	if (this->_hero.getPosition().y + 300 > BG.getGlobalBounds().getSize().y)
	{
		this->_hero.move(0.f, -3.f);
		animState = IDLE;
	}
	if (this->_hero.getPosition().x - 435 < (this->_data->window->getSize().x - this->_data->videomode.width))
	{
		this->_hero.move(3.f, 0.f);
		animState = IDLE;
	}
	if (this->_hero.getPosition().y - 300 < (this->_data->window->getSize().y - this->_data->videomode.height))
	{
		this->_hero.move(0.f, 3.f);
		animState = IDLE;
	}
	for (auto& x : enemies)
	{
		if (this->_hero.getGlobalBounds().intersects(x.getGlobalBounds()))
		{
			animState = DYING;
		}
	}

	view.setCenter(this->_hero.getPosition());
	this->_data->window->setView(view);
}

void Hero::renderHero(sf::RenderTarget& target)
{
	target.draw(this->_hero);
}

void Hero::renderBullets(sf::RenderTarget& target)
{
	for (auto& x : this->bullets)
	{
		target.draw(x.sprite);
	}
}

void Hero::renderSword(sf::RenderTarget& target)
{
	target.draw(this->sword.sword_sprite);
}
