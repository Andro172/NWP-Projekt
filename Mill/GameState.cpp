#include "stdafx.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

namespace NWP {
	GameState::GameState(GameDataRef data) : _data(data) {

	}

	void GameState::Init() {

		gameState = STATE_PLAYING;
		previousGameState = STATE_PLAYING;
		turn = GREEN_PIECE;


		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));

		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		this->_data->assets.LoadTexture("Green Piece", GREEN_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("Red Piece", RED_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("Green Selected Piece", GREEN_SELECTED_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("Red Selected Piece", RED_SELECTED_PIECE_FILEPATH);

		this->_data->assets.LoadTexture("Green Player", GREEN_PLAYER_FILEPATH);
		this->_data->assets.LoadTexture("Red Player", RED_PLAYER_FILEPATH);
		this->_data->assets.LoadTexture("Green Player Turn", GREEN_PLAYER_TURN_FILEPATH);
		this->_data->assets.LoadTexture("Red Player Turn", RED_PLAYER_TURN_FILEPATH);


		this->_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
		this->_gridSprite.setScale(0.91,0.91);

		InitGridArray();
		InitGridPieces();

		this->greenPlayer = new Player(GREEN_PIECE,_data);
		this->redPlayer = new Player(RED_PIECE, _data);

	}
	void GameState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}


			for (int i = 0; i < 7; ++i) {
				for (int j = 0; j < 7; ++j) {
					if (this->_data->input.IsSpriteClicked(this->_gridPieces[i][j], sf::Mouse::Left, this->_data->window)) {
						if (gridArray[i][j] != INVALID_SPACE) {
							if (gameState == STATE_PLAYING) {
								this->CheckAndPlacePiece(i, j);
							}
							else if (gameState == STATE_MILL) {
								this->CheckAndTakePiece(i, j);
							}
							else if (gameState == STATE_MOVING) {
								if (gridArray[i][j] == turn) {
									this->CheckAndSelectPiece(i, j);
								}
								else {
									this->CheckAndMovePiece(i, j);
								}
							}
						}
					}
				}
			}
				
			
			

		}
	}

	void GameState::Update(float dt) {
		if (STATE_DRAW == gameState || STATE_RED_WON == gameState || STATE_GREEN_WON == gameState) {
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER) {
				this->_data->machine.AddState(StateRef(new GameOverState(gameState,_data)), true);
			}
		}
	}

	void GameState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);
		this->greenPlayer->DrawSprites();
		this->redPlayer->DrawSprites();

		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {
				if (gridArray[i][j] != INVALID_SPACE) {
					this->_data->window.draw(this->_gridPieces[i][j]);
				}
			}
		}


		this->_data->window.display();
	}


	void GameState::InitGridPieces() {
		int fix = 0;
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {
				_gridPieces[i][j].setTexture(this->_data->assets.GetTexture("Red Piece"));

				_gridPieces[i][j].setPosition(_gridSprite.getPosition().x + fix + (_gridSprite.getLocalBounds().width / 7) * i,
					_gridSprite.getPosition().y + fix + (_gridSprite.getLocalBounds().height / 7) * j);

				_gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));

			}
			fix = 0;
		}
	}

	void GameState::InitGridArray() {

		// first row
		for (int i = 0; i < 7; ++i) {
			if (i == 0 || i == 3 || i == 6) {
				gridArray[0][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[0][i] = INVALID_SPACE;
		}

		// second row
		for (int i = 0; i < 7; ++i) {
			if (i == 1 || i == 3 || i == 5) {
				gridArray[1][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[1][i] = INVALID_SPACE;
		}

		// third row
		for (int i = 0; i < 7; ++i) {
			if (i == 2 || i == 3 || i == 4) {
				gridArray[2][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[2][i] = INVALID_SPACE;
		}

		// fourth row
		for (int i = 0; i < 7; ++i) {
			if (i == 3) {
				gridArray[3][i] = INVALID_SPACE;
				continue;
			}
			gridArray[3][i] = EMPTY_PIECE;
		}


		// fifth row
		for (int i = 0; i < 7; ++i) {
			if (i == 2 || i == 3 || i == 4) {
				gridArray[4][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[4][i] = INVALID_SPACE;
		}


		// sixth row
		for (int i = 0; i < 7; ++i) {
			if (i == 1 || i == 3 || i == 5) {
				gridArray[5][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[5][i] = INVALID_SPACE;
		}

		// seventh row
		for (int i = 0; i < 7; ++i) {
			if (i == 0 || i == 3 || i == 6) {
				gridArray[6][i] = EMPTY_PIECE;
				continue;
			}
			gridArray[6][i] = INVALID_SPACE;
		}
	}

	void GameState::CheckAndPlacePiece(int row,int column) {

		if (gridArray[row][column] == EMPTY_PIECE) {

			if (GREEN_PIECE == turn) {
				bool placed = this->greenPlayer->PlacePiece(&_gridPieces[row][column]);
				if (!placed) {
					previousGameState = gameState;
					gameState = STATE_MOVING;
					this->CheckAndSelectPiece(row, column);
					return;
				}
				gridArray[row][column] = turn;
				try {
					CheckPlayerHasMill(turn);

					this->greenPlayer->ChangeTurnState(false);
					this->redPlayer->ChangeTurnState(true);
					turn = RED_PIECE;

					if (this->redPlayer->GetBasePieces() == 0) {
						gameState = STATE_MOVING;
						previousGameState = gameState;
						this->CheckAndSelectPiece(row, column);
					}
				}
				catch (int error) {
				}
			}
			else if (RED_PIECE == turn) {
				bool placed = this->redPlayer->PlacePiece(&_gridPieces[row][column]);
				if (!placed) {
					previousGameState = gameState;
					gameState = STATE_MOVING;
					return;
				}
				gridArray[row][column] = turn;
				try {
					CheckPlayerHasMill(turn);

					this->greenPlayer->ChangeTurnState(true);
					this->redPlayer->ChangeTurnState(false);
					turn = GREEN_PIECE;

					if (this->greenPlayer->GetBasePieces() == 0) {
						previousGameState = gameState;
						gameState = STATE_MOVING;
					}
				}
				catch (int error) {
				}
			}

		}

	}

	void GameState::CheckAndTakePiece(int row, int column) {

		if (gridArray[row][column] != EMPTY_PIECE && gridArray[row][column] != INVALID_SPACE) {

			if (turn == GREEN_PIECE && gridArray[row][column] == RED_PIECE) {
				if (!this->redPlayer->CheckIfPieceOnMill(row,column)) {
					bool taken = this->greenPlayer->TakePiece(&_gridPieces[row][column]);
					if (!taken) {
						previousGameState = gameState;
						gameState = STATE_GREEN_WON;
						return;
					}
					gridArray[row][column] = EMPTY_PIECE;
					_gridPieces[row][column].setColor(sf::Color(255, 255, 255, 0));

					(*_tempMill[0]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));
					(*_tempMill[1]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));
					(*_tempMill[2]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));

					this->greenPlayer->ChangeTurnState(false);
					this->redPlayer->ChangeTurnState(true);
					turn = RED_PIECE;
					
					gameState = previousGameState;
				}
				else {
					gameState = STATE_RED_WON;
				}
			}
			else if (turn == RED_PIECE && gridArray[row][column] == GREEN_PIECE) {
				if (!this->greenPlayer->CheckIfPieceOnMill(row,column)) {
					bool taken = this->redPlayer->TakePiece(&_gridPieces[row][column]);
					if (!taken) {
						previousGameState = gameState;
						gameState = STATE_RED_WON;
						return;
					}
					gridArray[row][column] = EMPTY_PIECE;
					_gridPieces[row][column].setColor(sf::Color(255, 255, 255, 0));

					(*_tempMill[0]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));
					(*_tempMill[1]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));
					(*_tempMill[2]).setTexture(this->_data->assets.GetTexture(_tempPieceStr));

					this->greenPlayer->ChangeTurnState(true);
					this->redPlayer->ChangeTurnState(false);
					turn = GREEN_PIECE;
					
					gameState = previousGameState;
				}
				else {
					gameState = STATE_GREEN_WON;
				}
			}
		}

	}

	void GameState::CheckAndSelectPiece(int row, int column) {

		if (gridArray[row][column] != EMPTY_PIECE && gridArray[row][column] != INVALID_SPACE) {

			if (GREEN_PIECE == turn && GREEN_PIECE == gridArray[row][column]) {
				this->greenPlayer->SelectPiece(&_gridPieces[row][column]);
				previousGameState = gameState;
				gameState = STATE_MOVING;
			}
			else if (RED_PIECE == turn && RED_PIECE == gridArray[row][column]) {
				this->redPlayer->SelectPiece(&_gridPieces[row][column]);
				previousGameState = gameState;
				gameState = STATE_MOVING;
			}

			rowSelected = row;
			columnSelected = column;
		}
	}

	void GameState::CheckAndMovePiece(int row, int column) {

		if (gridArray[row][column] == EMPTY_PIECE) {

			if (GREEN_PIECE == turn) {
				if (CheckIfCanMove(row,column) || this->redPlayer->GetTakenPieces() == 6) {
					this->greenPlayer->MovePiece(&_gridPieces[row][column]);
					gridArray[row][column] = turn;
					gridArray[rowSelected][columnSelected] = EMPTY_PIECE;

					try {
						CheckPlayerHasMill(turn);
						this->greenPlayer->UnsetMillIfMoved(rowSelected, columnSelected);

						this->greenPlayer->ChangeTurnState(false);
						this->redPlayer->ChangeTurnState(true);
						turn = RED_PIECE;
					}
					catch (int error) {
					}
				}
			}
			else if (RED_PIECE == turn) {
				if (CheckIfCanMove(row, column) || this->greenPlayer->GetTakenPieces() == 6) {
					this->redPlayer->MovePiece(&_gridPieces[row][column]);
					gridArray[row][column] = turn;
					gridArray[rowSelected][columnSelected] = EMPTY_PIECE;

					try {
						CheckPlayerHasMill(turn);
						this->redPlayer->UnsetMillIfMoved(rowSelected, columnSelected);

						this->greenPlayer->ChangeTurnState(true);
						this->redPlayer->ChangeTurnState(false);
						turn = GREEN_PIECE;
					}
					catch (int error) {
					}
				}
			}

		}
	}


	void GameState::CheckPlayerHasMill(int piece) {
		try {
			Check3PiecesForMatch(0, 0, 0, 3, 0, 6, piece);
			Check3PiecesForMatch(0, 0, 3, 0, 6, 0, piece);
			Check3PiecesForMatch(6, 0, 6, 3, 6, 6, piece);
			Check3PiecesForMatch(6, 6, 3, 6, 0, 6, piece);
			Check3PiecesForMatch(1, 1, 1, 3, 1, 5, piece);
			Check3PiecesForMatch(1, 1, 3, 1, 5, 1, piece);
			Check3PiecesForMatch(5, 1, 5, 3, 5, 5, piece);
			Check3PiecesForMatch(5, 5, 3, 5, 1, 5, piece);
			Check3PiecesForMatch(2, 2, 2, 3, 2, 4, piece);
			Check3PiecesForMatch(2, 2, 3, 2, 4, 2, piece);
			Check3PiecesForMatch(4, 2, 4, 3, 4, 4, piece);
			Check3PiecesForMatch(4, 4, 3, 4, 2, 4, piece);
			Check3PiecesForMatch(0, 3, 1, 3, 2, 3, piece);
			Check3PiecesForMatch(4, 3, 5, 3, 6, 3, piece);
			Check3PiecesForMatch(3, 0, 3, 1, 3, 2, piece);
			Check3PiecesForMatch(3, 4, 3, 5, 3, 6, piece);
		}
		catch (int error) {
			throw -1;
		}

	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if (STATE_RED_WON != gameState && STATE_DRAW != gameState && STATE_GREEN_WON != gameState) {

			if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) {

				if (CheckIfAlreadyMill(x1, y1, x2, y2, x3, y3, pieceToCheck)) {
					return;
				}

				std::string selectingPieceStr;

				if (GREEN_PIECE == pieceToCheck) {
					selectingPieceStr = "Green Selected Piece";
					_tempPieceStr = "Green Piece";
					greenPlayer->SetMill(x1, y1, x2, y2, x3, y3);
				}
				else {
					selectingPieceStr = "Red Selected Piece";
					_tempPieceStr = "Red Piece";
					redPlayer->SetMill(x1, y1, x2, y2, x3, y3);
				}

				_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(selectingPieceStr));
				_tempMill[0] = &_gridPieces[x1][y1];
				_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(selectingPieceStr));
				_tempMill[1] = &_gridPieces[x2][y2];
				_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(selectingPieceStr));
				_tempMill[2] = &_gridPieces[x3][y3];

				previousGameState = gameState;
				gameState = STATE_MILL;

				throw -1;
			}
		}
	}

	bool GameState::CheckIfAlreadyMill(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if (pieceToCheck == GREEN_PIECE) {
			return this->greenPlayer->CheckIfHasMill(x1, y1, x2, y2, x3, y3);
		}
		else {
			return this->redPlayer->CheckIfHasMill(x1, y1, x2, y2, x3, y3);
		}
	}
	bool GameState::CheckIfCanMove(int row, int column)
	{
		return rowSelected == row || columnSelected == column;
	}
}