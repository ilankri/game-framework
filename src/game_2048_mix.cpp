#include "game_2048_mix.hpp"

Game_2048_mix::Game_2048_mix(int height, vector<long long> values,
			     vector<Action_2048> actions) :
	Game_2048(height),
	Game_2048_num(height, values),
	Game_2048_neg(height),
	Game_2048_fancy(height, actions) {}

bool Game_2048_mix::mergeable(const Square_2048& sq1,
			      const Square_2048& sq2) const
{
	return Game_2048_num::mergeable(sq1, sq2) ||
		Game_2048_neg::mergeable(sq1, sq2) ||
		Game_2048_fancy::mergeable(sq1, sq2);
}
