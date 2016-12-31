#include "game_2048.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i + 1]);
	}
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-r") == 0)
			robot = true;
	}
	
	Game_2048 game(height);

	if (!robot)
		game.play();

	else
		game.demo();
	
	return 0;
}
