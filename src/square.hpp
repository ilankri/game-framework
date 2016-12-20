#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>

using namespace std;

class Square {
	friend ostream& operator<<(ostream& out, Square& sq);

private:
	virtual void print(ostream& out) = 0;
};

#endif /* not SQUARE_HPP */
