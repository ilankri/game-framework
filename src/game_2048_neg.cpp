#include "game_2048_neg.hpp"

Game_2048_neg::Game_2048_neg(int height) :
	Game_2048(height)
{
	auto end = values.end();

	for (auto it = values.begin(); it != end; ++it)
		values.push_back(-(*it));
}

bool Game_2048_neg::mergeable(const Square_2048& sq1,
			      const Square_2048& sq2) const
{
	return sq1.is_opposite(sq2);
}
