#include "stdafx.h"
#include "GameState.h"
#include "GameOverState.h"
#include "MainMenuState.h"

namespace NWP {
	GameOverState::GameOverState(int winner,GameDataRef data) : _data(data) {
		_winner = winner;
	}

	void GameOverState::Init() {

		if (_winner == STATE_GREEN_WON) {
			_color = sf::Color::Green;
			this->_data->assets.LoadTexture("Green Player Won", GREEN_PLAYER_WON_FILEPATH);
			_title.setTexture(this->_data->assets.GetTexture("Green Player Won"));
		}
		else {
			_color = sf::Color::Red;
			this->_data->assets.LoadTexture("Red Player Won", RED_PLAYER_WON_FILEPATH);
			_title.setTexture(this->_data->assets.GetTexture("Red Player Won"));
		}

		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));

		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		
		this->_title.setPosition((this->_data->window.getSize().x / 2) - (this->_title.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_title.getLocalBounds().height / 2));

		this->_retryButton.setPosition((this->_data->window.getSize().x / 3) * 2 - (this->_retryButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) * 2 - (this->_retryButton.getLocalBounds().height / 2));

		this->_homeButton.setPosition((this->_data->window.getSize().x / 3) - (this->_homeButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) * 2 - (this->_homeButton.getLocalBounds().height / 2));

		
	}

	void GameOverState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt) {

	}

	void GameOverState::Draw(float dt) {
		this->_data->window.clear(_color);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_title);
		this->_data->window.display();
	}
}