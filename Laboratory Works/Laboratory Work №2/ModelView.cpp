#include "ModelView.h"

void ModelView::ShowBoard()
{
	const auto _board = model->GetBoard();
	const auto size = model->GetSize();
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			switch (_board[i][j])
			{
				case NONE:
					{
						if (j+1 == size)
						{
							std::cout << " " << std::endl;
						}
						else
						{
							std::cout << "  |";
						}
						
						break;
					}
				case X:
					{
						if (j+1 == size)
						{
							std::cout << "X" << std::endl;
						}
						else
						{
							std::cout << "X |";
						}
						
						break;
					}
				case O:
					{
						if (j+1 == size)
						{
							std::cout << "O" << std::endl;
						}
						else
						{
							std::cout << "O |";
						}
						
						break;
					}
			}
		}

		if (i + 1 != size)
		{
			for (int j = 0; j < size; ++j)
			{
				if (j + 1 != size)
				{
					std::cout << "--|";
				}
				else
				{
					std::cout << "--" << std::endl;
				}
			}
		}
	}

	Model::gotoxy(0,0);
}

void ModelView::UpdateBoard(std::pair<short, short> coords)
{
	Model::gotoxy(coords.first, coords.second);
	std::cout << playerToChar(model->board[coords.first / 3][coords.second / 2]);
	Model::gotoxy(coords.first, coords.second);
}

void ModelView::StartGame(bool UseBot)
{
	player _player = X, winner;

	while ((winner = model->CheckWinner()) == NONE)
	{
		UpdateBoard(model->MakeMove(_player));
		changePlayer(_player);
		if (UseBot && (winner = model->CheckWinner()) == NONE)
		{
			UpdateBoard(model->MakeBotMove(_player));
			Model::gotoxy(model->curPosition.first, model->curPosition.second);
			changePlayer(_player);
		}
	}

	if (winner != DRAW)
	{
		Model::gotoxy(0, model->field_size * 2 + 2);
		std::cout << playerToChar(winner) << " wins" << std::endl;
	}
	else
	{
		Model::gotoxy(0, model->field_size * 2 + 2);
		std::cout << "Draw" << std::endl;
	}
}


ModelView::ModelView(Model* _model) : model(_model)
{
	if (model->field_size > 2)
	{
		ShowBoard();
	}
	else
	{
		std::cout << "Can't start game with such low field size" << std::endl;
		system("pause");
		exit(-1);
	}
}

ModelView::~ModelView()
{
	delete model;
}
