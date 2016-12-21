#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>

using namespace std;

class Square {
public:
	virtual bool operator==(const Square& s) const = 0;

	bool operator!=(const Square& s) const;

	friend ostream& operator<<(ostream& out, const Square& sq);

private:
	virtual void print(ostream& out) const = 0;
};

#endif /* not SQUARE_HPP */
