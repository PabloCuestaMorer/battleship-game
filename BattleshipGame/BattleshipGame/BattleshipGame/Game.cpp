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
        // Save player1
        file << player1.getName() << endl;
        vector<Ship*> ships = player1.getShips();
        for (auto& ship : ships)
        {
            file << ship->getName() << " " << ship->getSize() << " " << ship->getIsSunk() << endl;
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                file << player1.getBoard()[i][j] << " ";
            }
            file << endl;
        }
        // Save player2
        file << player2.getName() << endl;
        ships = player2.getShips();
        for (auto& ship : ships)
        {
            file << ship->getName() << " " << ship->getSize() << " " << ship->getIsSunk() << endl;
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                file << player2.getBoard()[i][j] << " ";
            }
            file << endl;
        }

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

