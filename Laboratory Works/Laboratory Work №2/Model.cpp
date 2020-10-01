#include "Model.h"

Model::Model(int size) : field_size(size)
{
	if (field_size > 2)
	{
		std::vector<player> temp(size, NONE);
	
		for (int i = 0; i < field_size; ++i)
		{
			board.push_back(temp);
		}
	}
}

const int& Model::GetSize()
{
	return field_size;
}

void Model::gotoxy(short x, short y)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);	  
	crd.X = x;
	crd.Y = y;
	SetConsoleCursorPosition(hCons, crd);
}

std::vector<std::vector<player>>& Model::GetBoard()
{
	return board;
}

std::pair<short, short> Model::MakeMove(player _player)
{
	while (true)
	{
		if (_kbhit())
		{
			unsigned char c = _getch();
			switch (c)
			{
				case ' ':
					{
						if (board[curPosition.first/3][curPosition.second/2] == NONE)
						{
							board[curPosition.first/3][curPosition.second/2] = _player;
							return curPosition;
						}
						
						continue;
					}
				case 'w':
					{
						if (curPosition.second > 0)
						{
							curPosition.second -= 2;
							gotoxy(curPosition.first, curPosition.second);
						}
						break;
					}
				case 'a':
					{
						if (curPosition.first > 0)
						{
							curPosition.first -= 3;
							gotoxy(curPosition.first, curPosition.second);
						}
						break;
					}
				case 's':
					{
						if (curPosition.second + 2 < field_size * 2)
						{
							curPosition.second += 2;
							gotoxy(curPosition.first, curPosition.second);
						}
						break;
					}
				case 'd':
					{
						if (curPosition.first + 3 < field_size * 3)
						{
							curPosition.first += 3;
							gotoxy(curPosition.first, curPosition.second);
						}
						break;
					}
			}
		}
	}
}

std::pair<short, short> Model::MakeBotMove(player _player)
{
	srand(time(NULL));
	
	short x = rand() % field_size;
	short y = rand() % field_size;

	while (board[x][y] != NONE)
	{
		x = rand() % field_size;
		y = rand() % field_size; 
	}

	board[x][y] = _player;

	return std::make_pair(x * 3, y * 2);
}

player Model::CheckWinner()
{
	for (auto& it_1 : board)
	{
		for (auto& it_2 : it_1)
		{
			if (it_2 == NONE)
			{
				goto exit;
			}
		}
	}

	return DRAW;

	exit:

	player winner;

	if ((winner = CheckDiagonal()) != NONE)
	{
		return winner;
	}
	else if ((winner = CheckHorizontal()) != NONE)
	{
		return winner;
	}
	else if ((winner = CheckVertical()) != NONE)
	{
		return winner;
	}

	return NONE;
}

player Model::CheckHorizontal()
{
	for (int i = 0; i < field_size; ++i)
	{
		int count = 0;
		
		for (int j = 0; j < field_size-1; ++j)
		{
			if (board[i][j] == NONE)
			{
				break;
			}
			
			if (board[i][j] == board[i][j + 1])
			{
				++count;
			}
			else
			{
				break;
			}
		}

		if (count == field_size -1)
		{
			return board[i][0];
		}
	}

	return NONE;
}

player Model::CheckVertical()
{
	for (int i = 0; i < field_size; ++i)
	{
		int count = 0;
		
		for (int j = 0; j < field_size-1; ++j)
		{
			if (board[j][i] == NONE)
			{
				break;
			}
			
			if (board[j][i] == board[j + 1][i])
			{
				++count;
			}
			else
			{
				break;
			}
		}

		if (count == field_size -1)
		{
			return board[i][0];
		}
	}

	return NONE;
}

player Model::CheckDiagonal()
{
	int count = 0;
	player winner = NONE;
	for (int i = 0; i < field_size; i += field_size - 1)
	{
		for (int j = 0, k = i; j < field_size - 1; ++j, i == 0 ? ++k : --k)
		{
			if (board[j][k] == NONE)
			{
				break;
			}
			
			if (board[j][k] == board[j + 1][i == 0 ? k + 1 : k - 1])
			{
				++count;
				winner = board[j][k];
			}
			else
			{
				break;
			}
		}
	}

	if (count == field_size -1)
	{
		return winner;
	}
	else
	{
		return NONE;
	}
}


