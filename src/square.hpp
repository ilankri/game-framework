#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>

using namespace std;

class Square {
	friend ostream& operator<<(ostream& out, const Square& sq);

private:
	virtual void print(ostream& out) const = 0;
};

#endif /* not SQUARE_HPP */
