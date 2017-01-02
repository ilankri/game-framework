#ifndef GAME_2048_NEG_HPP
#define GAME_2048_NEG_HPP

#include "game_2048.hpp"

/* Variant with negative numbers.  */
class Game_2048_neg : public virtual Game_2048 {
public:
	Game_2048_neg(int height);

protected:
	virtual bool mergeable(const Square_2048& sq1,
			       const Square_2048& sq2) const;
};

#endif
