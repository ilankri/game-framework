#include "square_2048.hpp"

Square_2048::Square_2048(Square_2048_action a, int v) : action(a), value(v) {}

Square_2048::Square_2048(const Square_2048& sq)
{
	action = sq.action;
	value = sq.value;
}


Square_2048 Square_2048::empty(Square_2048_action::empty, 0);

Square_2048& Square_2048::operator=(const Square_2048& sq)
{
	action = sq.action;
	value = sq.value;
	return *this;
}

void Square_2048::set_value(int v)
{
	value = v;
}

void Square_2048::swap(Square_2048& sq)
{
	Square_2048 tmp(*this);

	*this = sq;
	sq = tmp;
}

bool Square_2048::is_empty()
{
	return *this == empty;
}

bool Square_2048::is_mergeable(Square_2048& sq)
{
	return !this->is_empty() && !sq.is_empty() && *this == sq;
}

Square_2048 Square_2048::merge(Square_2048& sq)
{
	if (is_mergeable(sq))
		return Square_2048(Square_2048_action::none, sq.value << 1);
	else
		throw Not_mergeable();
}

bool Square_2048::same_action(const Square_2048& sq) const
{
	return action == sq.action;
}

bool Square_2048::same_value(const Square_2048& sq) const
{
	return value == sq.value;
}

bool Square_2048::operator==(const Square_2048& sq) const
{
	return same_action(sq) && same_value(sq);
}

bool Square_2048::operator!=(const Square_2048& sq) const
{
	return !(*this == sq);
}

void Square_2048::print(ostream& out) const
{
	if (*this != empty)
		out << to_string(action) << value;
}
