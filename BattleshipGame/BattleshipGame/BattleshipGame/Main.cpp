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
			displayTurnsMenu();
			cin >> menuOp;
			system("cls");
		}
		if (menuOp == 1)
		{
			if (player1Turn)
			{
				// Display boards
				player1.printShipsBoard();
				player2.printShootingBoard();
				// Ask for shooting coordinates
				cout << player1.getName() << ", it's your turn to shoot. Enter coordinates (example: B3): ";
				char row;
				int col;
				cin >> row >> col;
				int x = row - 'A';
				// If player1 shoot player2. Hit = true: water = false
				player1Turn = player2.shoot(x, col) ? true : false;
				// Check gameOver
				if (turnsCounter > minTurns && player2.allSunk())
				{
					cout << "Hit, sunk and fleet destroyed! " << player1.getName() << " wins!" << endl;
					cout << player1.getName() << " has won in a total of " << turnsCounter << " moves." << endl;
					cout << "Congratulations " << player1.getName() << " you are the champion." << endl;
					gameOver = true;
				}
			} else
			{
				// Display boards
				player2.printShipsBoard();
				player1.printShootingBoard();
				// Ask for shooting coordinates
				cout << player2.getName() << ", it's your turn to shoot. Enter coordinates (example: B3): ";
				char row;
				int col;
				cin >> row >> col;
				int x = row - 'A';
				// If player1 shoot player2. Hit = true: water = false
				player1Turn = player1.shoot(x, col) ? false : true;
				// Check gameOver
				if (turnsCounter > minTurns && player1.allSunk())
				{
					cout << "Hit, sunk and fleet destroyed! " << player2.getName() << " wins!" << endl;
					cout << player2.getName() << " has won in a total of " << turnsCounter << " moves." << endl;
					cout << "Congratulations " << player2.getName() << " you are the champion." << endl;
					gameOver = true;
				}
			}
		} else if (menuOp == 2)
		{
			//Save game option
			string filename;
			cout << "Enter filename: ";
			cin >> filename;
			game.saveGame(filename);
			cout << "Game saved!" << endl;
		} else
		{
			cout << "Invalid choice. Please try again." << endl;
		}
		turnsCounter++;
	}
	cout << endl;
	cout << " GAME ENDS." << endl;
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
	//player1.placeShips();
	player1.placeShipsRandomly();
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
	//player2.placeShips();
	player2.placeShipsRandomly();
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