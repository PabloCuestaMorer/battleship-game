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

#include "Game.h"
#include "Player.h"

using namespace std;

void displayMenu()
{
	cout << "Welcome to the game! Please select an option:" << endl;
	cout << "1. New game" << endl;
	cout << "2. Load game" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your selection: ";
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

void startNewGame()
{
	//Game game;

//INI Player1 ships
	Player player1;
	cout << "Enter the name of player 1: ";
	string name1;
	cin >> name1;
	player1.setName(name1);
	//game.setPlayer1(player1);


	system("CLS");
	cout << player1.getName() << ", it's your turn to place your boats. Be smart!" << endl;
	//player1.placeShips();
//END Player1 ships

	cout << "Player 2 turn..." << endl;
	waitForSeconds(5);
	system("cls");

//INI Player2 ships
	Player player2;
	cout << "Enter the name of player 2: ";
	string name2;
	cin >> name2;
	player2.setName(name2);
	//game.setPlayer1(player2);


	system("CLS");
	cout << player2.getName() << ", it's your turn to place your boats. Be smarter!" << endl;
	player2.placeShips();
//END Player2 ships

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
