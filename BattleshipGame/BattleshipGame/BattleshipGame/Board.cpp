#include "Board.h"

void Board::fillBoard()
{
	// Board frames
	char coordX[] = { '0', '1', '2', '3',  '4',  '5',  '6',  '7',  '8',  '9' };
	char coordY[] = {'A', 'B', 'C', 'D',  'E',  'F',  'G',  'H',  'I',  'J'};
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 && j > 0)
			{
				// Frame x-coordinates of the board
				board[i][j] = coordX[j - 1];;
			} else if (j == 0 && i > 0)
			{
				// Frame y-coordinates of the board
				board[i][j] = coordY[i-1];
			} else
			{
				// Water
				board[i][j] = '~';
			}
		}
	}
	board[0][0] = ' ';
}


Board::Board()
{
	fillBoard();
}

void Board::displayBoard()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
