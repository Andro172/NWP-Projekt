#include "Player.h"
#include <iostream>
#include "DEFINITIONS.h"

using namespace std;

namespace NWP {
	Player::Player(int playerPiece, GameDataRef data) {
		this->_data = data;
		this->playerPiece = playerPiece;
		InitSprites(playerPiece);
	}

	void Player::InitSprites(int turn) {
		if (turn == GREEN_PIECE) {
			int xOffset = 0;
			int yOffset = 0;

			this->pieceTexture = this->_data->assets.GetTexture("Green Piece");
			this->playerTexture = this->_data->assets.GetTexture("Green Player");
			this->playerTurnTexture = this->_data->assets.GetTexture("Green Player Turn");
			this->enemyPieceTexture = this->_data->assets.GetTexture("Red Piece");
			this->selectedPieceTexture = this->_data->assets.GetTexture("Green Selected Piece");

			for (int i = 0; i < 9; ++i) {

				if (i == 3 || i == 6) {
					xOffset = 0;
					yOffset += 50;
				}

				this->baseSprites[i].setTexture(this->pieceTexture);
				this->baseSprites[i].setPosition(50 + xOffset,
					SCREEN_HEIGHT / 3 + yOffset);

				xOffset += 50;
			}

			xOffset = 0;
			yOffset = 200;

			for (int i = 0; i < 9; ++i) {

				if (i == 3 || i == 6) {
					xOffset = 0;
					yOffset += 50;
				}

				this->takenSprites[i].setTexture(this->enemyPieceTexture);
				this->takenSprites[i].setPosition(50 + xOffset,
					SCREEN_HEIGHT / 3 + yOffset);
				this->takenSprites[i].setColor(sf::Color(255, 255, 255, 0));

				xOffset += 50;
			}

			this->sprite.setTexture(this->playerTexture);
			this->sprite.setPosition(SCREEN_WIDTH / 6 - this->sprite.getGlobalBounds().width, SCREEN_HEIGHT / 4);
		}
		else {
			int xOffset = 0;
			int yOffset = 0;

			this->pieceTexture = this->_data->assets.GetTexture("Red Piece");
			this->playerTexture = this->_data->assets.GetTexture("Red Player");
			this->playerTurnTexture = this->_data->assets.GetTexture("Red Player Turn");
			this->enemyPieceTexture = this->_data->assets.GetTexture("Green Piece");
			this->selectedPieceTexture = this->_data->assets.GetTexture("Red Selected Piece");

			for (int i = 0; i < 9; ++i) {

				if (i == 3 || i == 6) {
					xOffset = 0;
					yOffset += 50;
				}

				this->baseSprites[i].setTexture(this->pieceTexture);
				this->baseSprites[i].setPosition(SCREEN_WIDTH - 100 - xOffset,
					SCREEN_HEIGHT / 3 + yOffset);

				xOffset += 50;
			}

			xOffset = 0;
			yOffset = 200;

			for (int i = 0; i < 9; ++i) {

				if (i == 3 || i == 6) {
					xOffset = 0;
					yOffset += 50;
				}

				this->takenSprites[i].setTexture(this->enemyPieceTexture);
				this->takenSprites[i].setPosition(SCREEN_WIDTH - 100 - xOffset,
					SCREEN_HEIGHT / 3 + yOffset);
				this->takenSprites[i].setColor(sf::Color(255, 255, 255, 0));

				xOffset += 50;
			}

			this->sprite.setTexture(this->playerTexture);
			this->sprite.setPosition(SCREEN_WIDTH / 6 * 5 + this->sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 4);
		}
	}

	void Player::DrawSprites(){
		this->_data->window.draw(this->sprite);

		for (int i = 0; i < 9; ++i) {
			this->_data->window.draw(this->baseSprites[i]); 
			this->_data->window.draw(this->takenSprites[i]);
		}
	}

	bool Player::PlacePiece(sf::Sprite *placeInGrid){
		if (this->basePieces > 0) {
			(*placeInGrid).setTexture(this->pieceTexture);
			(*placeInGrid).setColor(sf::Color(255, 255, 255, 255));
			this->DecreaseBasePieces();
			return true;
		}
		return false;
	}

	bool Player::TakePiece(sf::Sprite* takeInGrid) {
		if (this->takenPieces < 6) {
			(*takeInGrid).setColor(sf::Color(255, 255, 255, 0));
			this->IncreaseTakenPieces();
			return true;
		}
		return false;
	}

	void Player::SelectPiece(sf::Sprite* selectInGrid) {
		if (previousSelectedPiece) {
			(*previousSelectedPiece).setTexture(pieceTexture);
		}
		(*selectInGrid).setTexture(selectedPieceTexture);
		previousSelectedPiece = selectInGrid;
	}

	void Player::MovePiece(sf::Sprite* moveInGrid) {
		if (previousSelectedPiece) {
			(*previousSelectedPiece).setColor(sf::Color(255, 255, 255, 0));
			(*moveInGrid).setTexture(pieceTexture);
			(*moveInGrid).setColor(sf::Color(255, 255, 255, 255));
			previousSelectedPiece = nullptr;
		}
	}

	void Player::ChangeTurnState(bool hasTurn){
		if (hasTurn) {
			this->sprite.setTexture(this->playerTurnTexture);
		}
		else {
			this->sprite.setTexture(this->playerTexture);
		}
	}

	void Player::DecreaseBasePieces(){

		if (this->basePieces > 0) {
			--this->basePieces;
			this->baseSprites[this->basePieces].setColor(sf::Color(255, 255, 255, 0));
		}
	}

	void Player::IncreaseTakenPieces() {

		if (this->takenPieces < 9) {
			this->takenSprites[this->takenPieces].setColor(sf::Color(255, 255, 255, 255)); 
			++this->takenPieces;
		}
	}

	bool Player::CheckIfMill(int x1, int y1, int x2, int y2, int x3, int y3, MillPieces pieces)
	{
		bool one = pieces.x1 == x1 && pieces.y1 == y1;
		bool two = pieces.x2 == x2 && pieces.y2 == y2;
		bool three = pieces.x3 == x3 && pieces.y3 == y3;

		return one && two && three;
	}

	bool Player::CheckIfOnMill(int row, int column, MillPieces pieces)
	{
		bool one = pieces.x1 == row && pieces.y1 == column;
		bool two = pieces.x2 == row  && pieces.y2 == column;
		bool three = pieces.x3 == row && pieces.y3 == column;

		return one || two || three;
	}

	void Player::SetMill(int x1, int y1, int x2, int y2, int x3, int y3){
		MillPieces pieces;
		pieces.x1 = x1;
		pieces.x2 = x2;
		pieces.x3 = x3;

		pieces.y1 = y1;
		pieces.y2 = y2;
		pieces.y3 = y3;

		
		for (int i = 0; i < 16; ++i) {
			if (CheckIfMill(x1, y1, x2, y2, x3, y3, currentMills[i])) {
				break;
			}

			if (currentMills[i].x1 == -1) {
				currentMills[i] = pieces;
				++currentMillsNum;
				break;
			}
		}
		
	}

	void Player::UnsetMill(int x1, int y1, int x2, int y2, int x3, int y3){
		MillPieces pieces;

		for (int i = 0; i < 16; ++i) {
			if (currentMills[i].x1 == x1 &&
				currentMills[i].x2 == x2 &&
				currentMills[i].x3 == x3 &&
				currentMills[i].y1 == y1 &&
				currentMills[i].y2 == y2 &&
				currentMills[i].y3 == y3) {

				currentMills[i] = pieces;
				--currentMillsNum;
				break;
			}
		}
		
	}

	bool Player::CheckIfHasMill(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		for (int i = 0; i < 16; ++i) {
			if (CheckIfMill(x1, y1, x2, y2, x3, y3, currentMills[i])) {
				return true;
			}
		}
		return false;
	}

	bool Player::CheckIfPieceOnMill(int row, int column)
	{
		for (int i = 0; i < 16; ++i) {
			if (CheckIfOnMill(row, column, currentMills[i])) {
				return true;
			}
		}
		return false;
	}

	void Player::UnsetMillIfMoved(int rowSelected, int columnSelected){
		
		for (int i = 0; i < 16; ++i) {
			if (CheckIfOnMill(rowSelected, columnSelected, currentMills[i])) {
				MillPieces pieces;
				currentMills[i] = pieces;
				--currentMillsNum;
			}
		}
	}

	int Player::GetBasePieces()
	{
		return this->basePieces;
	}
	int Player::GetTakenPieces()
	{
		return this->takenPieces;
	}
}