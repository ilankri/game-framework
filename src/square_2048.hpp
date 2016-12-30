#ifndef SQUARE_2048_HPP
#define SQUARE_2048_HPP

#include "printable.hpp"
#include "action_2048.hpp"

class Square_2048 : public Printable {
public:
	static Square_2048 empty;

	Square_2048(Action_2048 action = Action_2048::empty,
		    unsigned long long value = 0);

	Square_2048(const Square_2048& sq);

	bool operator==(const Square_2048& sq) const;

	bool operator!=(const Square_2048& sq) const;

	bool dest_possible(const Square_2048& sq) const;

	bool mult_possible(const Square_2048& sq) const;

	bool is_opposite(const Square_2048& sq) const;

	bool same_action(const Square_2048& sq) const;

	bool same_value(const Square_2048& sq) const;

	Square_2048& operator=(const Square_2048& sq);

	void set_value(unsigned long long value);

	unsigned long long get_value() const;

	void swap(Square_2048& sq);

	bool is_empty() const;

	virtual bool is_mergeable(Square_2048& sq) const;

	virtual Square_2048 merge(Square_2048& sq);

private:
	Action_2048 action;

	unsigned long long value;

	virtual void print(ostream& out) const;

};

#endif /* not SQUARE_2048_HPP */
