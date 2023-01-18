/*****************************************************************//**
 * \file   Player.h
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <string>
#include "Ship.h"

using namespace std;
class Player
{
private:
	string name;
	Ship ships[5];
	char gameBoard[10][10];
	char shotHistory[10][10];
};

