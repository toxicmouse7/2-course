#pragma once
#include "Model.h"

#include <iostream>

class ModelView
{
private:
	Model* model;
	char playerToChar(player _player);

	void changePlayer(player& _player)
	{
		_player = static_cast<player>((static_cast<int>(_player) + 1) % 2);
	}

	void ShowBoard();
	void UpdateBoard(std::pair<short, short> coords);

public:
	ModelView(Model* _model);
	~ModelView();
	void StartGame(bool UseBot);
};

inline char ModelView::playerToChar(player _player)
{
	switch (_player)
	{
		case X:
			{
				return 'X';
			}
		case O:
			{
				return 'O';
			}
		case NONE:
			{
				return ' ';
			}
	}
}

