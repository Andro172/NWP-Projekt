#include "AI.h"
#include <iostream>
#include "DEFINITIONS.h"

using namespace std;

namespace NWP {
	AI::AI(int playerPiece, GameDataRef data) {
		this->_data = data;
		this->playerPiece = playerPiece;

		if (GREEN_PIECE == playerPiece) {
			aiPiece = RED_PIECE;
		}
		else {
			aiPiece = GREEN_PIECE;
		}

		checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
		checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
		checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
		checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
		checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
		checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
		checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
		checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
		checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
		checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
		checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
		checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });

	}

	void AI::PlacePiece(int(*gridArray)[3][3], sf::Sprite gridPieces[3][3], int* gameState) {
		try {
			for (int i = 0; i < checkMatchVector.size(); ++i) {
				CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2],
					checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], GREEN_PIECE, gridArray, gridPieces);
			}

			for (int i = 0; i < checkMatchVector.size(); ++i) {
				CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2],
					checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], RED_PIECE, gridArray, gridPieces);
			}

			// if center is empty
			CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);

			//check if corner is empty
			CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);

			// check for any other empty piece
			CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);
		}
		catch (int error) {

		}

		*gameState = STATE_PLAYING;
	}
	void AI::CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3]) {
		
		if ((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck) {
			if (EMPTY_PIECE == (*gridArray)[X][Y]) {
				(*gridArray)[X][Y] == GREEN_PIECE;
				gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("Green Piece"));
				gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));
				throw -1;
			}
		}
	}
	void AI::CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3]) {
		std::cout << X + Y << std::endl;
		if (EMPTY_PIECE == (*gridArray)[X][Y]) {
			(*gridArray)[X][Y] = GREEN_PIECE;
			gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("Green Piece"));
			gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));
			std::cout << "here" << std::endl;
			throw -2;
		}
	}
}