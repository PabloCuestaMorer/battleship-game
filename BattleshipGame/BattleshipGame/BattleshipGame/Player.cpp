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


