#include "game_2048_neg.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
	}
	
	Game_2048_Neg game(height);

	
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-r") == 0)
			robot = true;
	}

	if (!robot)
		game.play();

	else game.demo();

	return 0;
}
