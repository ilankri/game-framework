#include "taquin.hpp"
#include "low_char.hpp"

int main()
{
	Taquin<Low_Char> game(5, 5);

	game.play();
	return 0;
}
