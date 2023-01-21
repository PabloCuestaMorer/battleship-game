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


void shoot(Player& player, bool& player1Turn, bool& gameOver)
{
	cout << player.getName() << ", it's your turn to shoot. Enter coordinates (example: B3): ";
	char row;
	int col;
	cin >> row >> col;
	int x = row - 'A';
	if (player.shoot(x, col))
	{
		cout << "Hit!" << endl;
		if (player.allSunk())
		{
			if (player1Turn)
			{
				cout << "Hit, sunk and fleet destroyed! " << player.getName() << " wins!" << endl;
			} else
			{
				cout << "Hit, sunk and fleet destroyed! " << player.getName() << " wins!" << endl;
			}
			gameOver = true;
		} else
		{
			cout << "Enter coordinates again: ";
			cin >> row >> col;
			x = row - 'A';
			if (player.shoot(x, col))
			{
				cout << "Hit!" << endl;
				if (player.allSunk())
				{
					if (player1Turn)
					{
						cout << "Hit, sunk and fleet destroyed!" << player.getName() << " wins!" << endl;
					} else
					{
						cout << "Hit, sunk and fleet destroyed! " << player.getName() << " wins!" << endl;
					}
					gameOver = true;
				}
			}
		}
	} else
	{
		cout << "Water!" << endl;
		player1Turn = !player1Turn;
	}
}

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

	cout << "1. Pass Turn" << endl;
	cout << "2. Save Game" << endl;
	cout << "Enter your selection: ";

}

void battle(Game game)
{
	Player player1 = game.getPlayer(1);
	Player player2 = game.getPlayer(2);

	cout << "The battle begins!" << endl;
	waitForSeconds(10);
	system("cls");

	bool gameOver = false;
	bool player1Turn = true;
	bool turnsCounter = 0;
	int menuOp = 0;
	while (!gameOver)
	{
		if (player1Turn)
		{
			// The first time do not display the menu
			if (turnsCounter == 0)
			{
				cout << "THE BATTLE BEGINS!" << endl;
			} else
			{
				displayTurnsMenu();
				cin >> menuOp;
			}

			if (menuOp == 1)
			{
				player1.printShipsBoard();
				player1.printShootingBoard();
				cout << "It's " << player1.getName() << "turn!" << endl;
				shoot(player1, player1Turn, gameOver);
			} else if (menuOp == 2)
			{
				string filename;
				cout << "Enter filename: ";
				cin >> filename;
				game.saveGame(filename);
				cout << "Game saved!" << endl;
			} else
			{
				cout << "Invalid choice. Please try again." << endl;
			}

		} else
		{
			displayTurnsMenu();
			cin >> menuOp;
			if (menuOp == 1)
			{
				player2.printShipsBoard();
				player2.printShootingBoard();
				cout << "It's " << player2.getName() << "turn!" << endl;
				shoot(player2, player1Turn, gameOver);
			} else if (menuOp == 2)
			{
				string filename;
				cout << "Enter filename: ";
				cin >> filename;
				game.saveGame(filename);
				cout << "Game saved!" << endl;
			} else
			{
				cout << "Invalid choice. Please try again." << endl;
			}
		}
		turnsCounter++;
	}
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
	cout << "Player 2's turn to place the ships in... " << endl;
	waitForSeconds(10);
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
	displayMenu();

	int menuOption;
	cin >> menuOption;

	switch (menuOption)
	{
		case 1:
			cout << "Starting a new game..." << endl;
			system("CLS");
			startNewGame();
			break;
		case 2:
			cout << "Loading a saved game..." << endl;
			break;
		case 3:
			cout << "Exiting the program..." << endl;
			return 0;
		default:
			cout << "Invalid selection. Please try again." << endl;
			break;
	}

	return 0;
}