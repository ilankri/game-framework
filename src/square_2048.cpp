#include "square_2048.hpp"

Square_2048::Square_2048(Action_2048 a,
			 unsigned long long v) : action(a), value(v) {}

Square_2048::Square_2048(const Square_2048& sq)
{
	action = sq.action;
	value = sq.value;
}


Square_2048 Square_2048::empty(Action_2048::empty, 0);

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

unsigned long long Square_2048::get_value() const
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

bool Square_2048::is_mergeable(Square_2048& sq) const
{

	if (*this == sq) {
		if (sq.action == Action_2048::none)
			return true;

		if (sq.action == Action_2048::neg)
			return true;
	}

	if (this -> mult_possible(sq)) return true;

	if (this -> is_opposite(sq)) return true;

	if (this -> dest_possible(sq)) return true;

	return false;
}

Square_2048 Square_2048::merge(Square_2048& sq)
{
	if (this -> is_opposite(sq)
	    || this -> dest_possible(sq))
	{
		return empty;
	}

	if (this -> mult_possible(sq)) {

		int res_val = this -> value * sq.value;
		Action_2048 res_action;

		if (this -> action == Action_2048::mult) {
			res_action = sq.action;
		}

		else res_action = this -> action;

		return Square_2048(res_action,res_val);
	}

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

bool Square_2048::dest_possible(const Square_2048& sq) const
{
	if (this -> is_empty() || sq.is_empty()) return false;

	return (this -> action == Action_2048::destroy
		|| sq.action == Action_2048::destroy);
}

bool Square_2048::mult_possible(const Square_2048& sq) const
{
	if (this -> is_empty() || sq.is_empty()) return false;

	if (this -> action == Action_2048::destroy)
		return false;

	if (sq.action == Action_2048::destroy)
		return false;


	return (this -> action == Action_2048::mult
		|| sq.action == Action_2048::mult);
}

bool Square_2048::is_opposite(const Square_2048& sq) const
{
	/* Deux cases ayant des valeurs différentes ne peuvent être opposés */
	if (!same_value(sq)) return false;

	/* Il reste maintenant à vérifier si les deux signes sont opposés */
	if (this -> action == Action_2048::none)
		return sq.action == Action_2048::neg;

	if (this -> action == Action_2048::neg)
		return sq.action == Action_2048::none;

	return false;
}

void Square_2048::print(ostream& out) const
{
	if (!is_empty()) {
		out << to_string(action);
		if (this -> action != Action_2048::destroy) {
			out << value;
		}
	}
}
