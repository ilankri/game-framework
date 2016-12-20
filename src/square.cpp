#include "square.hpp"

ostream& operator<<(ostream& out, const Square& sq)
{
	sq.print(out);
	return out;
}
