#pragma once

#include "State.h"
#include "Game_Engine.h"

class SettingState : public State
{
public:
	SettingState(GameDataRef data);

	void init();

	void handleevent();

	void update(float dt);

	void renderBG(sf::RenderTarget& target);
	void renderBackB(sf::RenderTarget& target);
	void renderSkinsChange(sf::RenderTarget& target);
	void render(float dt);

private:
	GameDataRef _data;

	void initSkins();
	void initSoundVol();
	void initBG();
	void initBackB();
	void Back();
	void SkinChange();
	void SpriteSkinChange();

	sf::Text skin_option;
	sf::Sprite Current_Hero;
	sf::Sprite SO_mesh;

	sf::Text sound_volume;

	sf::RectangleShape volumeUP;
	sf::RectangleShape volumeDOWN;

	sf::Sprite BG;

	sf::Vector2f mousePos;
	sf::Sprite BackButt;
};