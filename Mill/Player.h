#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

struct MillPieces {
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1, x3 = -1, y3 = -1;
};

namespace NWP {
	class Player {
	public:
		Player(int playerPiece, GameDataRef data);
		void ChangeTurnState(bool hasTurn);
		void DrawSprites();
		bool PlacePiece(sf::Sprite *placeInGrid);
		bool TakePiece(sf::Sprite* takeInGrid);
		void SelectPiece(sf::Sprite* selectInGrid);
		void MovePiece(sf::Sprite* moveInGrid);
		void SetMill(int x1, int y1, int x2, int y2, int x3, int y3);
		void UnsetMill(int x1, int y1, int x2, int y2, int x3, int y3);
		bool CheckIfHasMill(int x1, int y1, int x2, int y2, int x3, int y3);
		bool CheckIfPieceOnMill(int row, int column);
		void UnsetMillIfMoved(int row,int column);
		int GetBasePieces();
		int GetTakenPieces();
	private:
		void InitSprites(int playerPiece);
		void DecreaseBasePieces();
		void IncreaseTakenPieces();
		bool CheckIfMill(int x1, int y1, int x2, int y2, int x3, int y3, MillPieces pieces);
		bool CheckIfOnMill(int row, int column, MillPieces pieces);
		

		int playerPiece;
		int basePieces = 9;
		int takenPieces = 0;
		sf::Sprite baseSprites[9];
		sf::Sprite takenSprites[9];
		sf::Sprite sprite;
		sf::Texture pieceTexture;
		sf::Texture playerTexture;
		sf::Texture playerTurnTexture;
		sf::Texture enemyPieceTexture;
		sf::Texture selectedPieceTexture;
		sf::Sprite* previousSelectedPiece;

		MillPieces currentMills[16];
		int currentMillsNum = 0;

		GameDataRef _data;
	};
}