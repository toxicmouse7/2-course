#include <iostream>
#include "Model.h"
#include "ModelView.h"

int main()
{
	ModelView game(new Model(3));
	game.StartGame(true);

	return 0;
}