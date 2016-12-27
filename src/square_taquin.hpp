#ifndef SQUARE_TAQUIN_HPP
#define SQUARE_TAQUIN_HPP

#include <iostream>

#include "printable.hpp"

class Square_Taquin : public Printable {
public:
	Square_Taquin(unsigned long l = 0);

	Square_Taquin(const Square_Taquin&);

	bool operator==(const Square_Taquin &) const;

	bool operator!=(const Square_Taquin &) const;

	bool operator<(const Square_Taquin &) const;

	bool operator<=(const Square_Taquin &) const;

	bool operator>(const Square_Taquin &) const;

	bool operator>=(const Square_Taquin &) const;

	Square_Taquin& operator=(Square_Taquin);

	Square_Taquin& operator++();

	Square_Taquin operator++(int);

	Square_Taquin& operator--();

	Square_Taquin operator--(int);
	
private:
	static Square_Taquin empty;
	
	virtual void print(ostream& o) const;


	unsigned long value;

	
};

#endif
