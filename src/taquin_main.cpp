#include "taquin.hpp"
#include "cap_char.hpp"
#include "low_char.hpp"
#include <cstring>

int main(int argc, char **argv)
{
	const int int_version = 1;
	const int cap_char_version = 2;
	const int low_char_version = 3;
	
	int height, width, version = int_version;
	bool robot = false;

	for (int i = 0; i< argc-1; i++) {
		if (strcmp(argv[i],"-h") == 0)
			height = atoi(argv[i + 1]);
		if (strcmp(argv[i],"-w") == 0)
			width = atoi(argv[i + 1]);
	}
	


	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-capchar") == 0)
			version = cap_char_version;

		if (strcmp(argv[i],"-lowchar") == 0)
			version = low_char_version;
		
		if (strcmp(argv[i],"-r") == 0)
			robot = true;
	}

	Taquin<int> game1(height, width);
	Taquin<Cap_Char> game2(height, width);
	Taquin<Low_Char> game3(height, width);

	switch(version) {
	case cap_char_version:
		if (!robot)
			game2.play();
		else
			game2.demo();
		break;
	case low_char_version:
		if (!robot)
			game3.play();
		else
			game3.demo();
		break;
	default:
		if (!robot)
			game1.play();
		else
			game1.demo();
		break;
	}
	
	return 0;
}
