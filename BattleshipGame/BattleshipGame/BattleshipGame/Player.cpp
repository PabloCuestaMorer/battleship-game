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
	cout << name << "'s game board:" << endl;
	for (int i = 0; i < ships.size(); i++)
	{
		printBoard();
		cout << "Placing " << ships[i]->getName() << " of size " << ships[i]->getSize() << endl;
		cout << "Enter row coordinate (A-J): ";
		char row;
		cin >> row;
		int x = row - 'A';
		cout << "Enter column coordinate (0-9): ";
		int y;
		cin >> y;
		cout << "Enter orientation (H for horizontal, V for vertical): ";
		char orientation;
		cin >> orientation;
		bool isHorizontal = (orientation == 'H');
		if (canPlaceShip(x, y, ships[i]->getSize(), isHorizontal))
		{
			placeShip(x, y, ships[i]->getSize(), isHorizontal);
		} else
		{
			cout << "Invalid coordinates. Please try again." << endl;
			i--;
		}
	}
	system("CLS");
	cout << name << "'s game board:" << endl;
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
	cout << "  ";
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


