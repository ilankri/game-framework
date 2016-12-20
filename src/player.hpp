#ifndef PLAYER_HPP
#define PLAYER_HPP

template<class T>
class Player {
private:
	Jeu<T>& j;

public:
	static enum class Movement {L, R, U, D};

	virtual void play(Movement) = 0;
};

#endif	/* not PLAYER_HPP */
