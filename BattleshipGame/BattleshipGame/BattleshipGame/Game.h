/*****************************************************************//**
 * \file   Game.h
 * \brief  
 * 
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include "Player.h"
#include <fstream>

using namespace std;
class Game
{
private:
    Player player1;
    Player player2;

public:
    Game();
    void setPlayer(Player player, int number);
    Player getPlayer(int number);
    void saveGame(std::string filename);
    void loadGame(std::string filename);
};

