#include "taquin.hpp"
#include "low_char.hpp"

int main()
{
	Taquin<Low_Char> game(4, 4);

	game.play();
	return 0;
}
