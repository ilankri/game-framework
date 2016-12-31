#include "game_2048_mult.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
	}
	
	Game_2048_Mult game(height);

	game.play();
	return 0;
}
