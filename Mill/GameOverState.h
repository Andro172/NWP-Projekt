#pragma once
#include "stdafx.h"
#include "State.h"
#include "Game.h"

namespace NWP {
	class GameOverState : public State {
	public:
		GameOverState(int winner,GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
		sf::Sprite _title;

		sf::Color _color;

		int _winner;
	};
}