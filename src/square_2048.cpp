#include "square_2048.hpp"

Square_2048::Square_2048(Square_2048_action a,
			 unsigned long long v) : action(a), value(v) {}

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

void Square_2048::set_value(unsigned long long v)
{
	value = v;
}

unsigned long long Square_2048::get_value()
{
	return value;
}

void Square_2048::swap(Square_2048& sq)
{
	Square_2048 tmp(*this);

	*this = sq;
	sq = tmp;
}

bool Square_2048::is_empty() const
{
	return *this == empty;
}

bool Square_2048::is_mergeable(Square_2048& sq)
{
	if (sq.action == Square_2048_action::none && *this == sq) return true;
	if (sq.action == Square_2048_action::neg && *this == sq) return true;
	if (this -> is_opposite(sq)) return true;
	return false;
}

Square_2048 Square_2048::merge(Square_2048& sq)
{
	if (this -> is_opposite(sq)) return empty;
	return Square_2048(sq.action, sq.value << 1);
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

bool Square_2048::is_opposite(const Square_2048& sq) const
{
	/* Deux cases ayant des valeurs différentes ne peuvent être opposés */
	if (!same_value(sq)) return false;

	/* Il reste maintenant à vérifier si les deux signes sont opposés */
	if (this -> action == Square_2048_action::none)
		return sq.action == Square_2048_action::neg;

	if (this -> action == Square_2048_action::neg)
		return sq.action == Square_2048_action::none;

	return false;
}

void Square_2048::print(ostream& out) const
{
	if (!is_empty())
		out << to_string(action) << value;
}
