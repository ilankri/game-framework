#ifndef SQUARE_2048_HPP
#define SQUARE_2048_HPP

#include "printable.hpp"
#include "action_2048.hpp"

#include <vector>

class Square_2048 : public Printable {
public:
	Square_2048(Action_2048 action, long long value);

	/* Default constructor builds an empty square.  */
	Square_2048();

	Square_2048(const Square_2048& sq);

	Square_2048& operator=(const Square_2048& sq);

	/* The empty square.  */
	static const Square_2048 empty;

	/* Test if two squares are equal.  */
	bool operator==(const Square_2048& sq) const;

	bool operator!=(const Square_2048& sq) const;

	/*
	 * Return true if a square and sq are opposite, i.e. have
	 * opposite values, have no action and are both nonempty.
	 */
	bool is_opposite(const Square_2048& sq) const;

	/* Check if square action is destroy.  */
	bool is_destroy() const;

	/* Check if square action is mult.  */
	bool is_mult() const;

	/* Test if a square has the same action as sq.  */
	bool same_action(const Square_2048& sq) const;

	/* Test if a square has the same value as sq.  */
	bool same_value(const Square_2048& sq) const;

	/* Return the value of a square.  */
	long long get_value() const;

	/* Return the action of a square.  */
	Action_2048 get_action() const;

	/* Swap the content of a square and sq.  */
	void swap(Square_2048& sq);

	/* Test if a square is empty.  */
	bool is_empty() const;

	/*
	 * Return a random new square conform to given possible actions
	 * and values .
	 */
	static Square_2048 random(vector<Action_2048> actions,
				  vector<long long> values);

private:
	Action_2048 action;

	long long value;

	virtual void print(ostream& out) const;

	/* Return a random action for a new square among actions.  */
	static Action_2048 random_action(vector<Action_2048> actions);

	/* Return a random value for a new square among values.  */
	static long long random_value(vector<long long> values);
};

#endif /* not SQUARE_2048_HPP */
