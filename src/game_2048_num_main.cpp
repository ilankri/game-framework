#include "game_2048_num.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height, base;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-b") == 0)
			base = atoi(argv[i+1]);
	}
	
	Game_2048_Num game(height,base);

	game.play();
	return 0;
}
