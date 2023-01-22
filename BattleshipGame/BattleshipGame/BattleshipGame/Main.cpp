/*****************************************************************//**
 * \file   Main.cpp
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "Player.h"
#include "Game.h"

using namespace std;

void waitForSeconds(int seconds)
{
	//cout << "Waiting for " << seconds << " seconds:" << endl;
	for (int i = seconds; i > 0; i--)
	{
		cout << i << "..." << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	//cout << "Done!" << endl;
}

void displayTurnsMenu()
{
	cout << endl;
	cout << "1. Next move" << endl;
	cout << "2. Save Game" << endl;
	cout << "Enter your selection: ";
}

void battle(Game game)
{
	Player player1 = game.getPlayer(1);
	Player player2 = game.getPlayer(2);
	bool gameOver = false;
	bool player1Turn = true;
	int turnsCounter = 0;
	int minTurns = 15; // minimum number of turns to win. At least the sum af all ships sizes
	int menuOp = 0;
	while (!gameOver)
	{
		// The first time do not display the menu
		if (turnsCounter == 0)
		{
			cout << "THE BATTLE BEGINS!" << endl;
			cout << endl;
			menuOp = 1;
		} else
		{
			bool validOp = false;
			while (!validOp)
			{
				try
				{
					displayTurnsMenu();
					cin >> menuOp;
					if (cin.fail())
					{
						throw std::invalid_argument("The input is not a number");
					} else if (menuOp < 1 || menuOp > 2)
					{
						throw std::invalid_argument("Choose an option between 1 and 2");
					} else
					{
						validOp = true;
					}
				} catch (const std::invalid_argument& e)
				{
					system("cls");
					cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
					cin.clear();
					cin.ignore(numeric_limits<::streamsize>::max(), '\n');
					continue;
				}
			}
			system("cls");
		}
		// Next move (pass turn)
		if (menuOp == 1)
		{
			if (player1Turn)
			{
				bool validInput = false;
				while (!validInput)
				{
					// Display boards
					player1.printShipsBoard();
					player2.printShootingBoard();
					// Ask for shooting coordinates
					cout << player1.getName() << ", it's your turn to shoot. Enter coordinates (example: B3): ";
					char row;
					char column;
					cin >> row >> column;
					int x = row - 'A';
					int y = column - '0';
					try
					{
						if (cin.fail() || !isupper(row) || row < 'A' || row > 'J')
						{
							throw invalid_argument("Invalid row coordinate. Please enter a valid letter between A and J in uppercase.");
						} else if (!isdigit(column) || y < 0 || y > 9)
						{
							throw invalid_argument("Invalid column coordinate. Please enter a valid number between 0 and 9.");
						} else
						{
							validInput = true;
						}
					} catch (const invalid_argument& e)
					{
						system("cls");
						cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
						cin.clear();
						cin.ignore(numeric_limits<::streamsize>::max(), '\n');
						continue;
					}
					// If player1 shoot player2. Hit = true: water = false
					player1Turn = player2.shoot(x, y) ? true : false;
				}
			} else
			{
				bool validInput = false;
				while (!validInput)
				{
					// Player 2 turn
					// Display boards
					player2.printShipsBoard();
					player1.printShootingBoard();
					// Ask for shooting coordinates
					cout << player2.getName() << ", it's your turn to shoot. Enter coordinates (example: B3): ";
					char row;
					char column;
					cin >> row >> column;
					int x = row - 'A';
					int y = column - '0';
					try
					{
						if (cin.fail() || !isupper(row) || row < 'A' || row > 'J')
						{
							throw invalid_argument("Invalid row coordinate. Please enter a valid letter between A and J in uppercase.");
						} else if (!isdigit(column) || y < 0 || y > 9)
						{
							throw invalid_argument("Invalid column coordinate. Please enter a valid number between 0 and 9.");
						} else
						{
							validInput = true;
						}
					} catch (const invalid_argument& e)
					{
						system("cls");
						cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
						cin.clear();
						cin.ignore(numeric_limits<::streamsize>::max(), '\n');
						continue;
					}
					// If player1 shoot player2. Hit = true: water = false
					player1Turn = player1.shoot(x, y) ? false : true;
				}

			}
		} else if (menuOp == 2)
		{
			//Save game option
			string path = "C:\\Games\\Battleship\\";
			string ext = ".txt";
			string fileName;
			cout << "Enter filename: ";
			cin >> fileName;
			string finalPath = path + fileName + ext;
			game.saveGame(finalPath);
			cout << "Game saved at: " << finalPath << endl;
		} else
		{
			system("cls");
			cerr << "\033[1;31m" << "ERROR contact support." << "\033[0m" << endl;
		}
		// Check gameOver
		if (turnsCounter > minTurns && player2.allSunk())
		{
			cout << endl;
			cout << "Hit, sunk and fleet destroyed! " << player1.getName() << " wins!" << endl;
			cout << player1.getName() << " has won in a total of " << turnsCounter << " moves." << endl;
			player1.printShipsBoard();
			player2.printShootingBoard();
			cout << "Congratulations " << player1.getName() << " you are the champion." << endl;
			gameOver = true;
		} else if (turnsCounter > minTurns && player1.allSunk())
		{
			cout << endl;
			cout << "Hit, sunk and fleet destroyed! " << player2.getName() << " wins!" << endl;
			cout << player2.getName() << " has won in a total of " << turnsCounter << " moves." << endl;
			player2.printShipsBoard();
			player1.printShootingBoard();
			cout << "Congratulations " << player2.getName() << " you are the champion." << endl;
			gameOver = true;
		}

		++turnsCounter;
	}
	cout << endl;
	cout << "GAME ENDS." << endl;
}

void startNewGame()
{
	Game game;

	//INI Player1 ships
	Player player1;
	cout << "Enter the name of player 1: ";
	string name1;
	cin >> name1;
	player1.setName(name1);
	//Place ships
	system("CLS");
	player1.placeShips();
	//player1.placeShipsRandomly();
	//END Player1 ships

	cout << endl;
	cout << "Player 2's be ready to place the ships in... " << endl;
	waitForSeconds(5);
	system("cls");

	//INI Player2 ships
	Player player2;
	cout << "Enter the name of player 2: ";
	string name2;
	cin >> name2;
	player2.setName(name2);
	//Place ships
	system("CLS");
	player2.placeShips();
	//player2.placeShipsRandomly();
	//END Player2 ships

	game.setPlayer(player1, 1);
	game.setPlayer(player2, 2);

	//INI BATTLE
	cout << endl;
	cout << "The battle begins!" << endl;
	waitForSeconds(10);
	system("cls");

	battle(game);
	//END BATTLE
}

void displayMenu()
{
	cout << "Welcome to the game! Please select an option:" << endl;
	cout << "1. New game" << endl;
	cout << "2. Load game" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your selection: ";
}

int main()
{
	bool validOp = false;
	int menuOption;
	while (!validOp)
	{
		try
		{
			displayMenu();
			cin >> menuOption;
			if (cin.fail())
			{
				throw std::invalid_argument("The input is not a number");
			}
			if (menuOption < 1 || menuOption > 3)
			{
				throw std::invalid_argument("Choose an option between 1 and 3");
			}
			validOp = true;
			switch (menuOption)
			{
				case 1:
					cout << "Starting a new game..." << endl;
					system("CLS");
					startNewGame();
					break;
				case 2:
					//cout << "Loading a saved game..." << endl;
					cerr << "\033[1;32m" << "We are still implementing this functionality, please be patient :)" << "\033[0m" << endl;
					break;
				case 3:
					cout << "Exiting the program..." << endl;
					return 0;
				default:
					system("cls");
					cerr << "\033[1;31m" << "ERROR contact support." << "\033[0m" << endl;
					break;
			}

		} catch (const std::invalid_argument& e)
		{
			system("cls");
			cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
			cin.clear();
			cin.ignore(numeric_limits<::streamsize>::max(), '\n');
			continue;
		}
	}

	return 0;
}