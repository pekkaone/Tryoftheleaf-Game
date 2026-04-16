#include "settings_state.h"
#include "pause_state.h"


SettingState::SettingState(GameDataRef data)
	: _data(data) {}

void SettingState::init()
{
	this->_data->assets.loadTexture("setting_BG", "images/settings_BG.png");
	this->_data->assets.loadTexture("BackButt", "images/Back-Button.png");
	this->_data->assets.loadTexture("RightButt", "images/RightButton.png");

	this->initBG();
	this->initSkins();
	this->initSoundVol();
	this->initBackB();
}

void SettingState::initSkins()
{
	this->skin_option.setString("Skin Option");
	this->skin_option.setFont(this->_data->assets.GetFont("FONT1"));
	this->skin_option.setPosition(160, 325);

	this->SpriteSkinChange();
	this->Current_Hero.setPosition(190, 365);
	this->Current_Hero.setScale(2.5f, 2.5f);

	this->SO_mesh.setTexture(this->_data->assets.GetTexture("RightButt"));
	this->SO_mesh.setPosition(197, 440);
}

void SettingState::initSoundVol()
{
}

void SettingState::initBG()
{
	this->BG.setTexture(this->_data->assets.GetTexture("setting_BG"));
}

void SettingState::initBackB()
{
	this->BackButt.setTexture(_data->assets.GetTexture("BackButt"));
	this->BackButt.setPosition(760, 55);
}

void SettingState::Back()
{
	if (this->BackButt.getGlobalBounds().contains(mousePos)) {
		_data->machine.RemoveState();
	}
}

void SettingState::SkinChange()
{
	

	if (this->SO_mesh.getGlobalBounds().contains(this->mousePos)) {
		if (this->_data->CurrentSkin <= 2)
		{
			this->_data->CurrentSkin += 1;
		}
		else {
			this->_data->CurrentSkin = 1;
		}
		SpriteSkinChange();
	}
}

void SettingState::SpriteSkinChange()
{
	if (this->_data->CurrentSkin == 1)
	{
		this->Current_Hero.setTexture(this->_data->assets.GetTexture("tHero1"));
	}
	if (this->_data->CurrentSkin == 2)
	{
		this->Current_Hero.setTexture(this->_data->assets.GetTexture("tHero2"));
	}
}

void SettingState::handleevent()
{
	sf::Event ev;
	while (_data->window->pollEvent(ev)) {
		if (sf::Event::Closed == ev.type) {
			_data->window->close();
		}

		if (sf::Event::MouseButtonPressed == ev.type) {
			sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
			mousePos = this->_data->window->mapPixelToCoords(mousePixel);

			Back();
			SkinChange();
		}
	}
}

void SettingState::update(float dt)
{
}

void SettingState::renderBG(sf::RenderTarget& target)
{
	this->_data->window->draw(this->BG);
}

void SettingState::renderBackB(sf::RenderTarget& target)
{
	this->_data->window->draw(this->BackButt);
}

void SettingState::renderSkinsChange(sf::RenderTarget& target)
{
	this->_data->window->draw(this->SO_mesh);
	this->_data->window->draw(this->skin_option);
	this->_data->window->draw(this->Current_Hero);
}

void SettingState::render(float dt)
{
	renderBG(*this->_data->window);
	renderSkinsChange(*this->_data->window);
	renderBackB(*this->_data->window);
}


