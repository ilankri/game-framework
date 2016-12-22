#ifndef SQUARE_2048_HPP
#define SQUARE_2048_HPP

#include "square.hpp"
#include "square_2048_action.hpp"

class Square_2048 : public Square {
public:
	Square_2048(Square_2048_action a, int val);

	virtual bool operator==(const Square_2048& s) const;

private:
	Square_2048_action action;

	int val;

	virtual void print(ostream& out) const;
};

#endif /* not SQUARE_2048_HPP */
