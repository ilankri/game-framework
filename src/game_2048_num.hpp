#ifndef GAME_2048_NUM_HPP
#define GAME_2048_NUM_HPP

#include "game_2048.hpp"

/*
 * Variant with other numbers than powers of 2.  The user can choose
 * a set of possible values.
 */
class Game_2048_num : public virtual Game_2048 {
public:
	Game_2048_num(int height, vector<long long> values);
};

#endif
