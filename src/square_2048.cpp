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

void Square_2048::set_value(long v)
{
	value = v;
}

long Square_2048::get_value()
{
	return value;
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
	if (!this->is_empty() && !sq.is_empty() && *this == sq) return true;
	if (this -> is_opposite(sq)) return true;
	return false;
}

Square_2048 Square_2048::merge(Square_2048& sq)
{
	if (is_mergeable(sq))
		if (is_opposite(sq))
			return Square_2048(empty); /* (1) */
		else
			return Square_2048(action, sq.value << 1);
	else
		throw Not_mergeable();

	/* (1) : les nombres négatifs détruisent les opposés, le résultat
	   de la fusion est donc une case vide */
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
	if (*this != empty)
		out << to_string(action) << value;
}
