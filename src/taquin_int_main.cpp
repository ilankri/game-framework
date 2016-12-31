#include "taquin.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height, width;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-w") == 0)
			width = atoi(argv[i+1]);
	}
	
	Taquin<int> game(height, width);

	
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-r") == 0)
			robot = true;
	}

	if (!robot)
		game.play();

	else game.demo();

	return 0;
}
