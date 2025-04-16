#include <iostream>
using namespace std;

class Cell
{
public:
	int x, y;
	int ship;

};

class Board
{
private:
	static int const size = 10;
	Cell board[size][size];

public:
	Board()
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				board[i][j].ship = 0;
	}

	void show()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (board[i][j].ship == 0)cout << " |";
				else if (board[i][j].ship == 1) cout << "H|";
				else if (board[i][j].ship == 2) cout << ".|";
				else if (board[i][j].ship == 3)cout << "X|";
			}
			cout << "\n";
		}
	}
};

int main()
{
	Board board;
	board.show();
}