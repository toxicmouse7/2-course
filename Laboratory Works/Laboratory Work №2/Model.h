#pragma once
#include <vector>
#include <conio.h>
#include <ctime>
#include <Windows.h>

class ModelView;

enum player
{
	X,
	O,
	NONE,
	DRAW
};


class Model
{
private:
	int field_size;
	std::vector<std::vector<player>> board;
	std::pair<short, short> curPosition = std::make_pair(0,0);

	const int& GetSize();
	std::vector<std::vector<player>>& GetBoard();
	std::pair<short, short> MakeMove(player _player);
	std::pair<short, short> MakeBotMove(player _player);
	player CheckWinner();
	player CheckHorizontal();
	player CheckVertical();
	player CheckDiagonal();

	friend ModelView;
	
public:
	Model(int size);
	static void gotoxy(short x, short y);
	
};

