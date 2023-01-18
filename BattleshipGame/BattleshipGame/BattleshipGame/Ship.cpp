#include "Ship.h"

string Ship::getName()
{
	return name;
}

void Ship::setName(string name)
{
	this->name = name;
}

int Ship::getLength()
{
	return length;
}

void Ship::setLength(int length)
{
	this->length = length;
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

void Ship::setX()
{
	this->x = x;
}

char Ship::getY()
{
	return y;
}

void Ship::setY()
{
	this->y = y;
}
