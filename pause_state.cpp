#include "pause_state.h"
#include <sstream>
#include "game_state.h"
#include "settings_state.h"

PauseState::PauseState(GameDataRef data) : _data(data) { }

void PauseState::init() {
	this->_data->assets.loadFont("FONT2", "texts/Montserrat-BlackItalic.ttf");
	this->_data->assets.loadTexture("BG_pauseS", "images/BG_pauseState.png");
	this->_data->assets.loadTexture("BackButt", "images/Back-Button.png");
	this->_data->assets.loadTexture("ButtonSettMesh", "images/ButtSett_meshWhite.png");

	this->_text.setFont(_data->assets.GetFont("FONT2"));
	this->BG.setTexture(_data->assets.GetTexture("BG_pauseS"));

	this->_data->window->setView(_data->window->getDefaultView());

	this->initBackB();
	this->initButtonSett();
	this->initButtSett_mesh();
}

void PauseState::initButtonSett()
{
	this->Button_sett.setFont(_data->assets.GetFont("FONT2"));
	this->Button_sett.setString("SETTING");
	this->Button_sett.setFillColor(sf::Color::White);
	this->Button_sett.setCharacterSize(40);
	this->Button_sett.setPosition(350.f, 450.f);
}

void PauseState::initButtSett_mesh()
{
	this->ButtSett_mesh.setPosition(340.f, 450.f);
	this->ButtSett_mesh.setSize(sf::Vector2f(220.f, 70.f));
	this->ButtSett_mesh.setFillColor(sf::Color::Transparent); 
	this->ButtSett_meshWh.setPosition(290.f, 427.f);
	this->ButtSett_meshWh.setTexture(_data->assets.GetTexture("ButtonSettMesh"));
	this->ButtSett_meshWh.setScale(0, 0);
}

void PauseState::initBackB()
{
	this->BackButt.setTexture(_data->assets.GetTexture("BackButt"));
	this->BackButt.setPosition(760, 55);
}

void PauseState::Back()
{
	if (this->BackButt.getGlobalBounds().contains(mousePos)) {
		_data->machine.RemoveState();
	}
}

void PauseState::ButtonSettPress()
{
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
			sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
			mousePos = _data->window->mapPixelToCoords(mousePixel);

			this->ButtonSettPress();
			this->Back();
		}
	}
}

void PauseState::updateButtonSett()
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);

	sf::Color start = sf::Color::White;
	sf::Color end = sf::Color::Black;
	sf::Color current;

	if (this->ButtSett_mesh.getGlobalBounds().contains(mousePos)) {
		this->ButtSett_meshWh.setScale(1.5, 1.5);

		if (this->Button_sett.getFillColor() != sf::Color::Black) {
			
			if (t < 1.f) {
				t += 0.1f;

				current.r = start.r + (end.r - start.r) * t;
				current.g = start.g + (end.g - start.g) * t;
				current.b = start.b + (end.b - start.b) * t;
				this->Button_sett.setFillColor(current);
			}
		}
	}
	else {
		this->ButtSett_meshWh.setScale(0, 0);
		this->Button_sett.setFillColor(sf::Color::White);
		t = 0;
	}
}
void PauseState::update(float dt)
{
	this->updateButtonSett();
}

void PauseState::renderButtonSett(sf::RenderTarget& target)
{
	target.draw(this->Button_sett);
}

void PauseState::renderBG(sf::RenderTarget& target)
{
	this->_data->window->draw(this->BG);
}

void PauseState::renderBackB(sf::RenderTarget& target)
{
	this->_data->window->draw(this->BackButt);
}

void PauseState::render(float dt)
{
	this->renderBG(*this->_data->window);
	this->renderBackB(*this->_data->window);
	this->_data->window->draw(this->ButtSett_meshWh);
	this->_data->window->draw(this->_text);
	this->_data->window->draw(this->Button_sett);
	this->_data->window->draw(this->ButtSett_mesh);

}