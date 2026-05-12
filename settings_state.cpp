#include "settings_state.h"
#include "pause_state.h"


SettingState::SettingState(GameDataRef data)
	: _data(data) {}

void SettingState::init()
{
	this->_data->assets.loadTexture("setting_BG", "images/settings_BG.png");
	this->_data->assets.loadTexture("RightButt", "images/RightButton.png");

	this->_data->assets.loadTexture("Sound7", "images/SoundCurrentState_7.png");
	this->_data->assets.loadTexture("Sound6", "images/SoundCurrentState_6.png");
	this->_data->assets.loadTexture("Sound5", "images/SoundCurrentState_5.png");
	this->_data->assets.loadTexture("Sound4", "images/SoundCurrentState_4.png");
	this->_data->assets.loadTexture("Sound3", "images/SoundCurrentState_3.png");
	this->_data->assets.loadTexture("Sound2", "images/SoundCurrentState_2.png");
	this->_data->assets.loadTexture("Sound1", "images/SoundCurrentState_1.png");

	this->_data->assets.loadTexture("SoundUP", "images/SoundUp.png");
	this->_data->assets.loadTexture("SoundDOWN", "images/SoundDown.png");

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
	this->Sound_Current.setTexture(_data->assets.GetTexture("Sound7"));
	this->Sound_Current.setPosition(570, 365);

	this->volumeDOWN.setPosition(578, 450);
	this->volumeDOWN.setTexture(_data->assets.GetTexture("SoundDOWN"));
	this->volumeUP.setPosition(660, 450);
	this->volumeUP.setTexture(_data->assets.GetTexture("SoundUP"));

	this->sound_volume.setString("Volume: " + std::to_string(_data->volume));
	this->sound_volume.setPosition(500, 480);
	this->sound_volume.setFont(this->_data->assets.GetFont("FONT1"));
}

void SettingState::initBG()
{
	this->BG.setTexture(this->_data->assets.GetTexture("setting_BG"));
}

void SettingState::initBackB() {
	this->BackButt.setTexture(_data->assets.GetTexture("BackButt"));
	this->BackButt.setPosition(760, 55);
}

void SettingState::Back() {
	if (this->BackButt.getGlobalBounds().contains(mousePos)) {
		_data->machine.RemoveState();
	}
}

void SettingState::SkinChange() {
	if (this->SO_mesh.getGlobalBounds().contains(this->mousePos)) {
		if (this->_data->CurrentSkin <= 2) {
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

void SettingState::SoundChange()
{
	this->sound_volume.setString("Volume: " + std::to_string(_data->volume));

	if (this->_data->volume >= 85) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound7"));
	}
	else if (this->_data->volume < 85 && this->_data->volume > 70) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound6"));
	}
	else if (this->_data->volume >= 70 && this->_data->volume > 55) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound5"));
	}
	else if (this->_data->volume >= 55 && this->_data->volume > 40) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound4"));
	}
	else if (this->_data->volume >= 40 && this->_data->volume > 25) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound3"));
	}
	else if (this->_data->volume >= 25 && this->_data->volume > 10) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound2"));
	}
	else if (this->_data->volume >= 10 && this->_data->volume >= 0) {
		this->Sound_Current.setTexture(_data->assets.GetTexture("Sound1"));
	}
}

void SettingState::SoundButtonPressed()
{
	if (this->volumeDOWN.getGlobalBounds().contains(mousePos)) {
		this->_data->volume = this->_data->volume - 5;
		if (this->_data->volume < 0) {
			this->_data->volume = 0;
		}
		std::cout << this->_data->volume;
		SoundChange();
	}
	if (this->volumeUP.getGlobalBounds().contains(mousePos)) {
		this->_data->volume = this->_data->volume + 5;
		if (this->_data->volume > 100) {
			this->_data->volume = this->_data->volume - 5;
		}
		SoundChange();
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
			SoundButtonPressed();
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

void SettingState::renderVolumeSettin(sf::RenderTarget& target)
{
	this->_data->window->draw(this->Sound_Current);
	this->_data->window->draw(this->volumeDOWN);
	this->_data->window->draw(this->volumeUP);
	this->_data->window->draw(this->sound_volume);
}

void SettingState::render(float dt)
{
	renderBG(*this->_data->window);

	renderVolumeSettin(*this->_data->window);
	renderSkinsChange(*this->_data->window);
	renderBackB(*this->_data->window);
}


