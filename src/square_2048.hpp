#ifndef SQUARE_2048_HPP
#define SQUARE_2048_HPP

#include "printable.hpp"
#include "square_2048_action.hpp"

class Not_mergeable {};

class Square_2048 : public Printable {
public:
	static Square_2048 empty;

	Square_2048(Square_2048_action action = Square_2048_action::empty,
		    int value = 0);

	Square_2048(const Square_2048& sq);

	bool operator==(const Square_2048& sq) const;

	bool operator!=(const Square_2048& sq) const;

	bool same_action(const Square_2048& sq) const;

	bool same_value(const Square_2048& sq) const;

	Square_2048& operator=(const Square_2048& sq);

	void set_value(int value);

	void swap(Square_2048& sq);

	bool is_empty();

	virtual bool is_mergeable(Square_2048& sq);

	virtual Square_2048 merge(Square_2048& sq);

private:
	Square_2048_action action;

	int value;

	virtual void print(ostream& out) const;
};

#endif /* not SQUARE_2048_HPP */
