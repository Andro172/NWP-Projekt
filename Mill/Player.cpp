#include "stdafx.h"
#include "Player.h"

namespace NWP {
	Player::Player(int playerPiece, GameDataRef data) {
		this->_data = data;
		this->playerPiece = playerPiece;
		InitSprites(playerPiece);
	}

	void Player::InitSprites(int turn) {
		if (turn == GREEN_PIECE) {
			float xOffset = 0;
			float yOffset = 0;

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
			float xOffset = 0;
			float yOffset = 0;

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

	void Player::SetMill(int x1, int y1, int x2, int y2, int x3, int y3){

		MillPieces pieces;
		pieces.x1 = x1;
		pieces.x2 = x2;
		pieces.x3 = x3;

		pieces.y1 = y1;
		pieces.y2 = y2;
		pieces.y3 = y3;

		currentMills.push_front(pieces);
	}


	void Player::UnsetMill(int x1, int y1, int x2, int y2, int x3, int y3){

		auto it = currentMills.begin();
		while (it != currentMills.end())
		{
			if (it->x1 == x1 && it->y1 == y1 &&
				it->x2 == x2 && it->y2 == y2 &&
				it->x3 == x3 && it->y3 == y3){
				currentMills.erase(it++);
			}
			else{
				++it;
			}
		}
	}

	bool Player::CheckIfHasMill(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		auto it = std::find_if(currentMills.begin(), currentMills.end(), [x1, y1, x2, y2, x3, y3](MillPieces pieces) {
				bool one = pieces.x1 == x1 && pieces.y1 == y1;
				bool two = pieces.x2 == x2 && pieces.y2 == y2;
				bool three = pieces.x3 == x3 && pieces.y3 == y3;

				return one && two && three;
			});

		if (it != currentMills.end()) {
			return true;
		}
		return false;
	}

	bool Player::CheckIfPieceOnMill(int row, int column)
	{
		auto it = std::find_if(currentMills.begin(), currentMills.end(), [row, column](MillPieces pieces) {
				bool one = pieces.x1 == row && pieces.y1 == column;
				bool two = pieces.x2 == row && pieces.y2 == column;
				bool three = pieces.x3 == row && pieces.y3 == column;

				return one || two || three;
			});

		if (it != currentMills.end()) {
			return true;
		}
		return false;
	}

	void Player::UnsetMillIfMoved(int rowSelected, int columnSelected){

		auto it = currentMills.begin();
		while (it != currentMills.end())
		{
			bool one = (*it).x1 == rowSelected && (*it).y1 == columnSelected;
			bool two = (*it).x2 == rowSelected && (*it).y2 == columnSelected;
			bool three = (*it).x3 == rowSelected && (*it).y3 == columnSelected;
			bool onMill = one || two || three;

			if (onMill) {
				currentMills.erase(it);
				break;
			}
			else {
				++it;
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