#include "Ship.h"

Ship::Ship()
{
	name = "Ship";
	size = 0;
	symbol = 'S';
	orientation = 'V';
	x = 0;
	y = 0;
	hits = 0;
	isSunk = false;
}

string Ship::getName()
{
	return name;
}

void Ship::setName(string name)
{
	this->name = name;
}

int Ship::getSize()
{
	return size;
}

void Ship::setSize(int size)
{
	this->size = size;
}

char Ship::getSymbol()
{
	return symbol;
}

void Ship::setSymbol(char symbol)
{
	this->symbol = symbol;
}

char Ship::getOrientation()
{
	return orientation;
}

void Ship::setOrientation(char orientation)
{
	this->orientation = orientation;
}

char Ship::getX()
{
	return x;
}

void Ship::setX(int x)
{
	this->x = x;
}

char Ship::getY()
{
	return y;
}

void Ship::setY(int y)
{
	this->y = y;
}

int Ship::getHits()
{
	return hits;
}

void Ship::setHits(int hits)
{
	this->hits = hits;
}

void Ship::hit()
{
	++hits;
}

bool Ship::getIsSunk()
{
	if (hits == size)
	{
		isSunk = true;
	} else
	{
		isSunk = false;
	}
	return isSunk;
}

void Ship::setIsSunk(bool sunk)
{
	this->isSunk = sunk;
}

istream& operator>>(istream& cin, Ship& ship)
{
	cout << "Enter the " << ship.name << " coordinates (x y) and orientation (h/v): ";
	cin >> ship.x >> ship.y >> ship.orientation;
	return cin;
}
