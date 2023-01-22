#include "Player.h"

bool Player::canPlaceShip(Ship* ship)
{
	if (ship->getOrientation() == 'H')
	{
		if (ship->getY() + ship->getSize() > COLS)
		{
			return false;
		}
		for (int i = ship->getY() - 1; i <= ship->getY() + ship->getSize(); i++)
		{
			for (int j = ship->getX() - 1; j <= ship->getX() + 1; j++)
			{
				if (i >= 0 && i < COLS && j >= 0 && j < ROWS && board[j][i] != '.')
				{
					return false;
				}
			}
		}
	} else
	{
		if (ship->getX() + ship->getSize() > ROWS)
		{
			return false;
		}
		for (int i = ship->getX() - 1; i <= ship->getX() + ship->getSize(); i++)
		{
			for (int j = ship->getY() - 1; j <= ship->getY() + 1; j++)
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

void Player::placeShip(Ship* ship)
{
	if (ship->getOrientation() == 'H')
	{
		for (int i = ship->getY(); i < ship->getY() + ship->getSize(); i++)
		{
			board[ship->getX()][i] = ship->getSymbol();
		}
	} else
	{
		for (int i = ship->getX(); i < ship->getX() + ship->getSize(); i++)
		{
			board[i][ship->getY()] = ship->getSymbol();
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
		Ship* currentShip = ships[i];
		cout << name << ", it's your turn to place your boats. Be smart!" << endl;
		printShipsBoard();
		cout << endl;
		cout << "Placing " << ships[i]->getName() << " of size " << ships[i]->getSize() << endl;
		cout << "Enter row coordinate (A-J), colum coordinate (0-9) and orientation (H/V)." << endl;
		cout << "Example A0V : ";
		char row;
		char column;
		char orientation;
		cin >> row >> column >> orientation;
		// Pass row to int (x)
		int x = row - 'A';
		int y = column - '0';
		bool isHorizontal = (orientation == 'H');
		try
		{
			if (!isalpha(row) || !isupper(row) || row < 'A' || row > 'J')
				throw invalid_argument("Invalid row coordinate. Please enter a valid letter between A and J in uppercase.");
			if (!isdigit(column) || y < 0 || y > 9)
				throw invalid_argument("Invalid column coordinate. Please enter a valid number between 0 and 9.");
			if (!isalpha(orientation) || !isupper(orientation) || (orientation != 'V' && orientation != 'H'))
				throw invalid_argument("Invalid orientation. Please enter a valid letter H/V in uppercase.");
		} catch (const invalid_argument& e)
		{
			system("cls");
			cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
			i--;
			continue;
		}

		//Set coordinates and orientation to ship
		currentShip->setOrientation(orientation);
		currentShip->setX(x);
		currentShip->setY(y);
		if (canPlaceShip(currentShip))
		{
			placeShip(currentShip);
			system("cls");

		} else
		{
			system("cls");
			cerr << "\033[1;31m" << "Must leave a space of water between boats." << "\033[0m" << endl;
			cerr << "\033[1;31m" << "Invalid coordinates. Please try again." << "\033[0m" << endl;
			i--;
		}
	}
	printShipsBoard();
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
			int randomX = rand() % 10;  //generate a random number 0-9
			int randomY = rand() % 10;  //generate a random number 0-9
			ship->setX(randomX);
			ship->setY(randomY);
			char randomOrientation = (rand() % 2 == 0) ? 'H' : 'V'; //generate a randomly 'V'/'H'
			ship->setOrientation(randomOrientation);
			if (canPlaceShip(ship))
			{
				placeShip(ship);
				placed = true;
			}
		}
	}
	cout << name << "'s game board (randomly generated):" << endl;
	printShipsBoard();
}

bool Player::shoot(int x, int y)
{
	if (board[x][y] == 'S' || board[x][y] == 'B' || board[x][y] == 'C' || board[x][y] == 'P' || board[x][y] == 'S' || board[x][y] == 'V')
	{
		char symbolHit = board[x][y];
		// Find the ship in ships vector that mathes the hit symbol
		auto it = find_if(ships.begin(), ships.end(), [symbolHit](Ship* ship) {
			return ship->getSymbol() == symbolHit;
			});

		if (it != ships.end())
		{
			Ship* foundShip = *it;
			foundShip->hit();
			if (foundShip->getIsSunk())
			{

				cout << foundShip->getName() << " Hit and sunk! " << endl;
				cout << "You destroy the " << name << "'s " << foundShip->getName() << "!!! ^_^" << endl;
			} else
			{
				cout << "Hit!" << endl;
			}
		} else
		{
			// object not found
		}
		board[x][y] = 'X';
		return true;
	} else
	{
		board[x][y] = '*';
		cout << "Water!" << endl;
		return false;
	}
}



void Player::printShipsBoard()
{
	//cout << endl;
	cout << name << "'s board: " << endl;
	//Space for the board frame
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
			// If its a hit do not print on ships board
			if (board[i][j] == '*')
			{
				cout << ". ";
			} else
			{
				cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
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
	cout << "Shooting history board:" << endl;
	//Space for the board frame
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
			if (board[i][j] == 'S' || board[i][j] == 'B' || board[i][j] == 'C' || board[i][j] == 'P' || board[i][j] == 'S' || board[i][j] == 'V')
			{
				cout << "." << " ";
			} else
			{
				cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
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
