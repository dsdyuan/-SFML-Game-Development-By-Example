#include "game.h"

int main(int argc, void** argv[])
{
	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}