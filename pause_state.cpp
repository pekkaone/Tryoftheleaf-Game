#include "pause_state.h"
#include <sstream>
#include "game_state.h"
#include "settings_state.h"

PauseState::PauseState(GameDataRef data) : _data(data) { }

void PauseState::init() {
	this->_data->assets.loadFont("FONT2", "texts/Montserrat-BlackItalic.ttf");
	this->_data->assets.loadTexture("BG_pauseS", "images/BG_pauseState.png");

	this->_text.setFont(_data->assets.GetFont("FONT2"));
	this->BG.setTexture(_data->assets.GetTexture("BG_pauseS"));

	this->_data->window->setView(_data->window->getDefaultView());


	this->initButtonSett();
	this->initButtSett_mesh();
}

void PauseState::initButtonSett()
{
	this->Button_sett.setFont(_data->assets.GetFont("FONT2"));
	this->Button_sett.setString("SETTING");
	this->Button_sett.setCharacterSize(40);
	this->Button_sett.setPosition(350.f, 450.f);
}

void PauseState::initButtSett_mesh()
{
	this->ButtSett_mesh.setPosition(340.f, 450.f);
	this->ButtSett_mesh.setSize(sf::Vector2f(220.f, 70.f));
	this->ButtSett_mesh.setFillColor(sf::Color::Transparent); 
}

void PauseState::ButtonSettPress()
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);

	if (ButtSett_mesh.getGlobalBounds().contains(mousePos))
	{
		std::cout << "Pressed";
		_data->machine.AddState(Sonar::StateRef(new SettingState(_data)), false);
	}
}


void PauseState::handleevent()
{
	sf::Event ev;
	while (_data->window->pollEvent(ev)) {
		if (sf::Event::Closed == ev.type) {
			_data->window->close();
		}

		if (sf::Event::KeyPressed == ev.type) {
			if (sf::Keyboard::P == ev.key.code) {
				_data->machine.RemoveState();
			}
		}
		if (sf::Event::MouseButtonPressed == ev.type) {
			this->ButtonSettPress();
		}
	}
}

void PauseState::updateButtonSett()
{

}

void PauseState::update(float dt)
{
}

void PauseState::renderButtonSett(sf::RenderTarget& target)
{
	target.draw(this->Button_sett);
}

void PauseState::renderBG(sf::RenderTarget& target)
{
	this->_data->window->draw(this->BG);
}

void PauseState::render(float dt)
{
	this->renderBG(*this->_data->window);
	this->_data->window->draw(this->_text);
	this->_data->window->draw(this->Button_sett);
	this->_data->window->draw(this->ButtSett_mesh);

}