#include "sokoban.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height = 0, width = 0, nb_crates = -1;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-w") == 0)
			width = atoi(argv[i+1]);
		if (strcmp(argv[i],"-c") == 0)
			nb_crates = atoi(argv[i+1]);
	}

	Sokoban game(height, width, nb_crates);


	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-D") == 0)
			robot = true;
	}

	if (!robot)
		game.play();

	else game.demo();

	return 0;
}
