#include "square_2048.hpp"

Square_2048::Square_2048(Action_2048 a, long long v) :
	action(a),
	value(v) {}

Square_2048::Square_2048() :
	action(empty.action),
	value(empty.value) {}


Square_2048::Square_2048(const Square_2048& sq)
{
	action = sq.action;
	value = sq.value;
}

Action_2048 Square_2048::random_action(vector<Action_2048> actions)
{
	Action_2048 a = actions[rand() % actions.size()];

	/* Make fancy actions less probable than basic action.  */
	if ((rand() & 3) == 0)
		return a;
	return Action_2048::none;
}

long long Square_2048::random_value(vector<long long> values)
{
	long long v = values[rand() % values.size()] << (rand() & 1);

	/* Make negative values less probable than positive ones.  */
	if ((rand() & 3) == 0)
		return v;
	return abs(v);
}

Square_2048 Square_2048::random(vector<Action_2048> actions,
				vector<long long> values)
{
	return Square_2048(random_action(actions), random_value(values));
}

Square_2048& Square_2048::operator=(const Square_2048& sq)
{
	action = sq.action;
	value = sq.value;
	return *this;
}

const Square_2048 Square_2048::empty(Action_2048::none, 0);

long long Square_2048::get_value() const
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
	if (action == Action_2048::none)
		return same_action(sq) && same_value(sq);
	return same_action(sq);
}

bool Square_2048::operator!=(const Square_2048& sq) const
{
	return !(*this == sq);
}

bool Square_2048::is_opposite(const Square_2048& sq) const
{
	return !is_empty() && value + sq.value == 0 &&
		action == Action_2048::none && same_action(sq);
}

void Square_2048::print(ostream& out) const
{
	if (!is_empty()) {
		out << to_string(action);
		if (get_action() == Action_2048::none)
			out << value;
	}
}

Action_2048 Square_2048::get_action() const
{
	return action;
}

bool Square_2048::is_destroy() const
{
	return action == Action_2048::destroy;
}

bool Square_2048::is_mult() const
{
	return action == Action_2048::mult;
}
