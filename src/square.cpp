#include "square.hpp"

ostream& operator<<(ostream& out, Square& sq)
{
	sq.print(out);
	return out;
}
