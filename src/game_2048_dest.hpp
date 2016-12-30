#ifndef GAME_2048_DEST_HPP
#define GAME_2048_DEST_HPP

#include "game_2048.hpp"

class Game_2048_Dest : public virtual Game_2048 {
	/* Variant with destroy squares */
public:
	Game_2048_Dest(int height);

protected:
	virtual Square_2048 random_square() const;
};

#endif
