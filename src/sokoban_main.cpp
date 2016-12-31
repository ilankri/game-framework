#include "sokoban.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height, width, nb_crates = -1;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-w") == 0)
			width = atoi(argv[i+1]);
		if (strcmp(argv[i],"-c") == 0)
			nb_crates = atoi(argv[i+1]);
	}
	
	Sokoban game(height, width, nb_crates);

	game.play();
	return 0;
}

