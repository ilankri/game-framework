#include "taquin.hpp"
#include "cap_char.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	int height, width;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i+1]);
		if (strcmp(argv[i],"-w") == 0)
			width = atoi(argv[i+1]);
	}
	
	Taquin<Cap_Char> game(height, width);

	game.play();
	return 0;
}
