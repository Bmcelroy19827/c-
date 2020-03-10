#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

using namespace std;

const int ROWS = 10;
const int ELEMENTS = 10;
int max_ships = 5;

int ship_1 = 2;
int ship_2 = 3;
int ship_3 = 3;
int ship_4 = 4;
int ship_5 = 5;

int matrix[ROWS][ELEMENTS];
string players_board[ROWS][ELEMENTS];

void Clear()
{
	for (int i = 0; i < ROWS;i++)
	{
		for (int j = 0; j < ELEMENTS; j++)
		{
			matrix[i][j] = 0;
			players_board[i][j] = "O";
		}
	}
}

void Show()
{
	for (int i = 0; i < ROWS;i++)
	{
		for (int j = 0; j < ELEMENTS; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void ShowPB()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ELEMENTS; j++)
		{
			cout << players_board[i][j] << " ";
		}
		cout << endl;
	}
}

int NumberOfShips()
{
	int ships = 0;
	for (int i = 0; i < ROWS;i++)
	{
		for (int j = 0; j < ELEMENTS; j++)
		{
			if (matrix[i][j] == 1)
			{
				ships++;
			}
		}		
	}
	return ships;
}

void SetShip(int size)
{
	bool isValid = false;
	int x, y;
	int direction;// either 0 for horizontal or 1 for vertical
	bool isMoreGood = false;
	bool isLessGood = false;
	while (!isValid)
	{
		direction = rand() % 2;
		x = rand() % ROWS;
		y = rand() % ELEMENTS;
		if (direction == 0)
		{
			if (y + size < ELEMENTS)
			{
				int start = y;
				isMoreGood = true;
				for (int i = 0; i < size; i++)
				{
					if (matrix[x][y + i] == 1)
					{
						isMoreGood = false;
					}
				}
				isValid = isMoreGood;
			}
			if ((y - size >= 0) && !isValid)
			{
				isLessGood = true;
				for (int i = 0; i < size; i++)
				{
					if (matrix[x][y - i] == 1)
					{
						isLessGood = false;
					}
				}
				isValid = isLessGood;
			}
		}
		else 
		{
			if (x + size < ROWS)
			{
				isMoreGood = true;
				for (int i = 0; i < size; i++)
				{
					if (matrix[x + i][y] == 1)
					{
						isMoreGood = false;
					}
				}
				isValid = isMoreGood;
			}
			if ((x - size >= 0) && !isValid)
			{
				isLessGood = true;
				for (int i = 0; i < size; i++)
				{
					if (matrix[x - i][y] == 1)
					{
						isLessGood = false;
					}
				}
				isValid = isLessGood;
			}
		}
	}

	if (direction == 0)//ship will be horizontal
	{
		if (isMoreGood)
		{
			for (int i = 0;i < size;i++)
			{
				matrix[x][y + i] = 1;
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				matrix[x][y - i] = 1;
			}
		}
	}
	else
	{
		if (isMoreGood)
		{
			for (int i = 0; i < size; i++)
			{
				matrix[x + i][y] = 1;
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				matrix[x - i][y] = 1;
			}
		}
	}
}

void SetShips()
{
	SetShip(ship_1);
	SetShip(ship_2);
	SetShip(ship_3);
	SetShip(ship_4);
	SetShip(ship_5);
}

bool Attack(int x, int y)
{
	if (matrix[x][y] == 1)
	{
		matrix[x][y] = 2;
		players_board[x][y] = "X";
		return true;
	}
	if (matrix[x][y] != 2)
	{
		players_board[x][y] = "-";
	}
	return false;
}

int main()
{
	srand(time(NULL));
	Clear();
	SetShips();
	int x_coord, y_coord;
	char quit;
	int shots_fired = 0;
	while (1)
	{
		ShowPB(); 
		cout << "Please input x and y coordinates (0-9 values): "; cin >> x_coord >> y_coord;
		shots_fired++;
		if (Attack(x_coord, y_coord))
		{
			cout << "Ship Hit!" << endl;
		}
		else
		{
			cout << "Miss!" << endl;
			cout << "Do you want to give up (y/n)? ";cin >> quit;
			if (quit == 'y')
			{
				break;
			}
		}
		if (NumberOfShips() == 0)break;
		cout << "Number of ships left: " << NumberOfShips() << endl;
	}
	if (NumberOfShips() == 0)
	{
		cout << "You Win!" << endl;
		cout << "Shots fired: " << shots_fired << endl;
		ShowPB();
	}
	else
	{
		cout << "Game Over, You Lost!" << endl;
		cout << "Ships Left: " << NumberOfShips() << endl;
		cout << "Shots fired: " << shots_fired << endl;
		Show();
	}

	system("pause");
	return 0;
}