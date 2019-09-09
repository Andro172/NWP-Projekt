#pragma once
#include "stdafx.h"
#include "State.h"
#include "Game.h"

namespace NWP {
	class MainMenuState : public State{
	public:
		MainMenuState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update( float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _playButton;
		sf::Sprite _title;
	};
}