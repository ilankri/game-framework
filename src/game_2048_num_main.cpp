#include "game_2048_num.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height = 4;
	int base = 2;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-b") == 0)
			base = atoi(argv[i+1]);
	}

	Game_2048_Num game(height,base);


	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-r") == 0)
			robot = true;
	}

	if (!robot)
		game.play();

	else game.demo();

	return 0;
}
