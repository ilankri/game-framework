#include "square_2048.hpp"

Square_2048::Square_2048(Square_2048_action a, int v) : action(a), val(v) {}

bool Square_2048::operator==(const Square_2048& s) const
{
	return action == s.action && val == s.val;
}

void Square_2048::print(ostream& out) const
{
	out << to_string(action);
}
