#include "taquin.hpp"
#include "cap_char.hpp"

int main()
{
	Taquin<Cap_Char> game(4, 4);

	game.play();
	return 0;
}
