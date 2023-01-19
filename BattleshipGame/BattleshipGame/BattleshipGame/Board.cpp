//#include "Board.h"
//
//void Board::fillBoard()
//{
//	// Board frames
//	char coordX[] = { '0', '1', '2', '3',  '4',  '5',  '6',  '7',  '8',  '9' };
//	char coordY[] = { 'A', 'B', 'C', 'D',  'E',  'F',  'G',  'H',  'I',  'J' };
//	for (int i = 0; i < 11; i++)
//	{
//		for (int j = 0; j < 11; j++)
//		{
//			if (i == 0 && j > 0)
//			{
//				// Frame x-coordinates of the board
//				board[i][j] = coordX[j - 1];;
//			} else if (j == 0 && i > 0)
//			{
//				// Frame y-coordinates of the board
//				board[i][j] = coordY[i - 1];
//			} else
//			{
//				// Water
//				board[i][j] = '~';
//			}
//		}
//	}
//	board[0][0] = ' ';
//}
//
//
//Board::Board()
//{
//	fillBoard();
//}
//
//char** Board::getBoard()
//{
//	char** copy = new char* [11];
//	for (int i = 0; i < 11; i++)
//	{
//		copy[i] = new char[11];
//		for (int j = 0; j < 11; j++)
//		{
//			copy[i][j] = board[i][j];
//		}
//	}
//	return copy;
//}
//
//void Board::displayBoard()
//{
//	for (int i = 0; i < 11; i++)
//	{
//		for (int j = 0; j < 11; j++)
//		{
//			cout << board[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//bool Board::isValidPlacement(Ship ship, int x, int y)
//{
//	if (ship.getOrientation() == 'h')
//	{
//		// Check if ship goes off the board
//		if (x + ship.getLength() > 11)
//		{
//			return false;
//		}
//		// Check if ship overlaps with other ships
//		for (int i = x - 1; i < x + ship.getLength() + 1; i++)
//		{
//			for (int j = y - 1; j < y + 2; j++)
//			{
//				if (board[i][j] != '~')
//				{
//					return false;
//				}
//			}
//		}
//	} else if (ship.getOrientation() == 'v' || ship.getOrientation() == 'V')
//	{
//		// Check if ship goes off the board
//		if (y + ship.getLength() > 11)
//		{
//			return false;
//		}
//		// Check if ship overlaps with other ships
//		for (int i = x - 1; i < x + 2; i++)
//		{
//			for (int j = y - 1; j < y + ship.getLength() + 1; j++)
//			{
//				if (board[i][j] != '~')
//				{
//					return false;
//				}
//			}
//		}
//	} else
//	{
//		return false;
//	}
//	return true;
//}
