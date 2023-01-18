#include "Player.h"

Player::Player()
{
	name = "DefaultPlayerName";
	Board shipsBoard;
	Board shotsBoard;
}

string Player::getName()
{
	return name;
}

void Player::setName(string name)
{
	this->name = name;
}

Board Player::getShipsBoard()
{
	return shipsBoard;
}

void Player::setShipsBoard(Board b)
{
	shipsBoard = b;
}

Board Player::getShotsBoard()
{
	return shotsBoard;
}

void Player::setShotsBoard(Board b)
{
	shotsBoard = b;
}


