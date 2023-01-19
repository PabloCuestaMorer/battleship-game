/*****************************************************************//**
 * \file   Main.cpp
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/

#include <iostream>
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



void startNewGame()
{
	//Game game;

	Player player1;

	//INI Player1
	cout << "Enter the name of player 1: ";
	string name1;
	cin >> name1;
	player1.setName(name1);
	//game.setPlayer1(player1);


	system("CLS");
	cout << player1.getName() << ", it's your turn to place your boats. Be careful!" << endl;
	
	player1.placeShips();

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
