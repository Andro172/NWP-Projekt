#pragma once
#include "stdafx.h"
#include "State.h"
#include "Game.h"

namespace NWP {
	class SplashState : public State {
	public:
		SplashState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
	};
}
