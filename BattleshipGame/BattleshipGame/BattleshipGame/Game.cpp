#include "Game.h"


Game::Game()
{
}

void Game::setPlayer(Player player, int number)
{
    if (number == 1)
    {
        player1 = player;
    } else
    {
        player2 = player;
    }
}

Player Game::getPlayer(int number)
{
    if (number == 1)
    {
        return player1;
    } else
    {
        return player2;
    }
}

void Game::saveGame(string filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << player1.getName() << endl;
        file << player2.getName() << endl;
        // save other game state variables
        file.close();
    }
}

void Game::loadGame(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string name1, name2;
        file >> name1 >> name2;
        player1.setName(name1);
        player2.setName(name2);
        // load other game state variables
        file.close();
    }
}

