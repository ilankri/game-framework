#ifndef GAME_2048_FANCY_HPP
#define GAME_2048_FANCY_HPP

#include "game_2048.hpp"

/* Variant with "special" actions.  */
class Game_2048_fancy : public virtual Game_2048 {
public:
	Game_2048_fancy(int height, vector<Action_2048> actions);

protected:
	virtual bool mergeable(const Square_2048& sq1,
			       const Square_2048& sq2) const;
};

#endif
