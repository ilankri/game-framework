#ifndef GAME_2048_MIX_HPP
#define GAME_2048_MIX_HPP

#include "game_2048_num.hpp"
#include "game_2048_neg.hpp"
#include "game_2048_fancy.hpp"

/* Mix of variants.  */
class Game_2048_mix : public Game_2048_num,
		      public Game_2048_neg,
		      public Game_2048_fancy {
public:
	Game_2048_mix(int height, vector<long long> values,
		      vector<Action_2048> actions);

protected:
	virtual bool mergeable(const Square_2048& sq1,
			       const Square_2048& sq2) const;
};

#endif
