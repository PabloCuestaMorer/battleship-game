/*****************************************************************//**
 * \file   Ship.h
 * \brief
 *
 * \author pablo
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <iostream>
#include <string>

using namespace std;
class Ship
{
protected:
	string name;
	int size;
	char symbol;
	char orientation;
	int x, y;
	int hits;
	bool isSunk;
public:
	Ship();
	string getName();
	void setName(string name);
	int getSize();
	void setSize(int size);
	char getSymbol();
	void setSymbol(char symbol);
	char getOrientation();
	void setOrientation(char orientation);
	char getX();
	void setX(int x);
	char getY();
	void setY(int x);
	int getHits();
	void setHits(int hits);
	void hit();
	bool getIsSunk();
	void setIsSunk(bool sunk);

	friend istream& operator>>(istream& input, Ship& ship);
};

