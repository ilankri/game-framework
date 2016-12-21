#include "square.hpp"

bool Square::operator!=(const Square& s) const
{
	return !(*this == s);
}

ostream& operator<<(ostream& out, const Square& sq)
{
	sq.print(out);
	return out;
}
