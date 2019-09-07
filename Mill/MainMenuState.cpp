#include "MainMenuState.h"
#include <sstream>
#include <iostream>
#include "DEFINITIONS.h"
#include "GameState.h"


namespace NWP {
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {

	}

	void MainMenuState::Init() {
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Background"));

		this->_data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		this->_data->assets.LoadTexture("Title", MAIN_MENU_TITLE_PATH);
		_title.setTexture(this->_data->assets.GetTexture("Title"));


		this->_playButton.setPosition((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2),
			((SCREEN_HEIGHT / 3) * 2 ) - (this->_playButton.getGlobalBounds().height / 2));


		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2),
			this->_title.getGlobalBounds().height * 0.1);
	}

	void MainMenuState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_playButton,sf::Mouse::Left,this->_data->window)) {
				// play the game
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt) {
		
	}

	void MainMenuState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_title);
		this->_data->window.display();
	}
}