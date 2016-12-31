#include "taquin.hpp"
#include "cap_char.hpp"

int main()
{
	Taquin<Cap_Char> game(5, 5);

	game.play();
	return 0;
}
