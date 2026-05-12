#include "Animation.h"

Animation::Animation(GameDataRef data) : _data(data) {}

void Animation::initAnimVariables()
{
	this->animationTimer.restart();
	this->currentFrame = sf::IntRect(0, 0, 30, 30);
	this->HeroDeath.setBuffer(_data->assets.GetSound("ADEath"));
	this->SoundPlaying = false;
}

void Animation::UpdateHeroAnimation(short AnimState, bool skin, sf::Sprite& hero)
{
	if (AnimState == 0) { // IDLE
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f) {
			 
			if (skin == 1) {
				this->currentFrame.top = 0;
				this->currentFrame.left += 30;
				if (this->currentFrame.left >= 60) {
					this->currentFrame.left = 0;
				}
			}

			else if (skin == 2) {
				DoNothing();
			}
		
			this->animationTimer.restart();
			hero.setTextureRect(this->currentFrame);
		}
	}

	else if (AnimState == 1 || AnimState == 3) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
			if (skin == 1) {
				this->currentFrame.top = 30;
				this->currentFrame.left += 30;
				if (this->currentFrame.left >= 60) {
					this->currentFrame.left = 0;
				}
			}

			else if (skin == 2) {
				DoNothing();
			}

			this->animationTimer.restart();
			hero.setScale(2.f, 2.f);
			hero.setOrigin(0, 0);
			hero.setTextureRect(this->currentFrame);
		}
		
	}
	else if (AnimState == 2) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
			if (skin == 1) {
				this->currentFrame.top = 30;
				this->currentFrame.left += 30;
				if (this->currentFrame.left >= 60) {
					this->currentFrame.left = 0;
				}
			}

			else if (skin == 2) {
				DoNothing();
			}

			this->animationTimer.restart();
			hero.setScale(-2.f, 2.f);
			hero.setOrigin(hero.getGlobalBounds().width / 2,
				hero.getGlobalBounds().height - 60);
			hero.setTextureRect(this->currentFrame);
		}
	}
	else if (AnimState == 4) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
			if (skin == 1) {
				this->currentFrame.top = 0;
				this->currentFrame.left = 60;
				
				
				if (!this->SoundPlaying) {
					this->HeroDeath.setVolume(_data->volume);
					this->HeroDeath.play();
					this->SoundPlaying = true;
				}
				
				if (HeroDeath.getStatus() != sf::Sound::Playing) {
					this->SoundPlaying = false;
				}
			}

			if (skin == 2) {
				this->DoNothing();
			}

			hero.setScale(2.f, 2.f);
			hero.setOrigin(0, 0);
			hero.setTextureRect(this->currentFrame);
		}
	}
	else {
		this->animationTimer.restart();
	}
}

void Animation::DoNothing()
{
}

bool Animation::SoundStatus()
{
	return this->SoundPlaying;
}
