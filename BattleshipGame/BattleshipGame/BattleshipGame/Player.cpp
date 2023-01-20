#include "Player.h"

bool Player::canPlaceShip(int row, int col, int size, bool isHorizontal)
{
	if (isHorizontal)
	{
		if (col + size > COLS)
		{
			return false;
		}
		for (int i = col - 1; i <= col + size; i++)
		{
			for (int j = row - 1; j <= row + 1; j++)
			{
				if (i >= 0 && i < COLS && j >= 0 && j < ROWS && board[j][i] != '.')
				{
					return false;
				}
			}
		}
	} else
	{
		if (row + size > ROWS)
		{
			return false;
		}
		for (int i = row - 1; i <= row + size; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if (i >= 0 && i < ROWS && j >= 0 && j < COLS && board[i][j] != '.')
				{
					return false;
				}
			}
		}
	}
	return true;
}


void Player::placeShip(int row, int col, int size, bool isHorizontal)
{
	if (isHorizontal)
	{
		for (int i = col; i < col + size; i++)
		{
			board[row][i] = 'S';
		}
	} else
	{
		for (int i = row; i < row + size; i++)
		{
			board[i][col] = 'S';
		}
	}
}

Player::Player()
{
	name = "DefaultPlayerName";
	ships.push_back(new Carrier());
	ships.push_back(new Battleship());
	ships.push_back(new Submarine());
	ships.push_back(new PatrolBoat());
	ships.push_back(new Vessel());

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = '.';
		}
	}

}

string Player::getName()
{
	return name;
}

void Player::setName(string name)
{
	this->name = name;
}

void Player::placeShips()
{
	for (int i = 0; i < ships.size(); i++)
	{
		cout << endl;
		cout << name << "'s game board:" << endl;
		printBoard();
		cout << endl;
		cout << "Placing " << ships[i]->getName() << " of size " << ships[i]->getSize() << endl;
		cout << "Enter row coordinate (A-J): ";
		char row;
		cin >> row;
		try
		{
			if (!isalpha(row) || !isupper(row) || row < 'A' || row > 'J')
				throw invalid_argument("Invalid row coordinate. Please enter a valid letter between A and J in uppercase.");
		} catch (const invalid_argument& e)
		{
			system("CLS");
			cout << e.what() << endl;
			i--;
			continue;
		}
		int x = row - 'A';
		cout << "Enter column coordinate (0-9): ";
		int y;
		cin >> y;
		try
		{
			if (/*!isdigit(y) || */y < 0 || y > 9)
				throw invalid_argument("Invalid column coordinate. Please enter a valid number between 0 and 9.");
		} catch (const invalid_argument& e)
		{
			system("CLS");
			cout << e.what() << endl;
			i--;
			continue;
		}
		cout << "Enter orientation (H for horizontal, V for vertical): ";
		char orientation;
		cin >> orientation;
		bool isHorizontal = (orientation == 'H');
		if (canPlaceShip(x, y, ships[i]->getSize(), isHorizontal))
		{
			placeShip(x, y, ships[i]->getSize(), isHorizontal);
		} else
		{
			system("CLS");
			cout << "Invalid coordinates. Please try again." << endl;
			i--;
		}
	}
	system("CLS");
	cout << name << "'s game board:" << endl;
	printBoard();
}

/**
 * Places the 5 ships randomly in the board, respecting a 1 space gap around each ship.
 * Ships can touch the edges of the board, but not with each other..
 *
 * @param None
 * @return None
 */
void Player::placeShipsRandomly()
{
	for (auto ship : ships)
	{
		bool placed = false;
		while (!placed)
		{
			int row = rand() % ROWS;
			int col = rand() % COLS;
			bool isHorizontal = rand() % 2;
			if (canPlaceShip(row, col, ship->getSize(), isHorizontal))
			{
				placeShip(row, col, ship->getSize(), isHorizontal);
				placed = true;
			}
		}
	}
	cout << endl;
	cout << name << "'s game board (randomly generated):" << endl;
	printBoard();
}

bool Player::shoot(int x, int y)
{
	if (board[x][y] == 'S')
	{
		board[x][y] = 'X';
		for (int i = 0; i < ships.size(); i++)
		{
			int size = ships[i]->getSize();
			bool sunk = true;
			for (int j = 0; j < ROWS; j++)
			{
				for (int k = 0; k < COLS; k++)
				{
					if (board[j][k] == 'S')
					{
						sunk = false;
						break;
					}
				}
				if (!sunk)
				{
					break;
				}
			}
			if (sunk)
			{
				ships[i]->setIsSunk(true);
				cout << ships[i]->getName() << " is sunk!" << endl;
			}
		}
		return true;
	} else
	{
		board[x][y] = '*';
		return false;
	}
}



void Player::printBoard()
{
	cout << endl;
	cout << name << "'s board: " << endl;
	for (int i = 0; i < COLS; i++)
	{
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < ROWS; i++)
	{
		cout << (char)('A' + i) << " ";
		for (int j = 0; j < COLS; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

/**
 * Display the history board of shooting for the indicated player
 * This method will display the board of the indicated player, but just with the shots and the hits made
 * by the opponent. This board can be used to show the history of the shots made by the opponent and check
 * where the player's ships have been hit..
 * 
 * \param player The player whose history board will be displayed
 */
void Player::printShootingBoard()
{
	cout << name << "'s history board:" << endl;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j] == 'S')
			{
				cout << board[i][j] << " ";
			} else
			{
				cout << board[i][j];
			}
		}
		cout << endl;
	}
}

bool Player::allSunk()
{
	for (int i = 0; i < ships.size(); i++)
	{
		if (!ships[i]->getIsSunk())
		{
			return false;
		}
	}
	return true;
}

void Player::savePlayer(string filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		file << name << endl;
		for (int i = 0; i < ships.size(); i++)
		{
			file << ships[i]->getName() << " " << ships[i]->getSize() << " " << ships[i]->getIsSunk() << endl;
		}
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				file << board[i][j] << " ";
			}
			file << endl;
		}
		file.close();
	}
}

void Player::loadPlayer(string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		file >> name;
		for (int i = 0; i < ships.size(); i++)
		{
			string shipName;
			int shipSize;
			bool shipSunk;
			file >> shipName >> shipSize >> shipSunk;
			ships[i]->setName(shipName);
			ships[i]->setSize(shipSize);
			ships[i]->setIsSunk(shipSunk);
		}
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				file >> board[i][j];
			}
		}
		file.close();
	}
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		name = other.name;
		for (int i = 0; i < ships.size(); i++)
		{
			ships[i] = new Ship(*(other.ships[i]));
		}
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				board[i][j] = other.board[i][j];
			}
		}
	}
	return *this;
}
