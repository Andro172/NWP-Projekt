#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "DEFINITIONS.h"


namespace NWP {
	class GameState : public State {
	public:
		GameState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		void InitGridPieces();
		void InitGridArray();
		void CheckAndPlacePiece(int row,int column);
		void CheckAndTakePiece(int row, int column);
		void CheckAndSelectPiece(int row, int column);
		void CheckAndMovePiece(int row, int column);
		void CheckPlayerHasMill(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		bool CheckIfAlreadyMill(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		bool CheckIfCanMove(int row, int column);


		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;
		sf::Sprite _gridPieces[7][7];
		sf::Sprite* _tempMill[3];
		std::string _tempPieceStr;

		int gridArray[7][7];
		int turn;
		int gameState;
		int previousGameState;
		int rowSelected = -1;
		int columnSelected = -1;


		Player *greenPlayer;
		Player *redPlayer;

		sf::Clock _clock;
	};
}