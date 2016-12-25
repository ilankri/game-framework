#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include <iostream>

using namespace std;

class Printable {
public:
	friend ostream& operator<<(ostream& out, const Printable& object);

private:
	virtual void print(ostream& out) const = 0;
};

#endif /* not PRINTABLE_HPP */
