#include "game_2048_fancy.hpp"

Game_2048_fancy::Game_2048_fancy(int height, vector<Action_2048> acts) :
	Game_2048(height)
{
	for (auto it = acts.begin(); it != acts.end(); ++it)
		actions.push_back(*it);
}

bool Game_2048_fancy::mergeable(const Square_2048& sq1,
				const Square_2048& sq2) const
{
	return sq1.is_destroy() || sq2.is_destroy() ||
		(sq1.get_action() == Action_2048::mult) ^
		(sq2.get_action() == Action_2048::mult);
}
