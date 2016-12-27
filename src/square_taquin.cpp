#include "square_taquin.hpp"

Square_Taquin Square_Taquin::empty(0);

Square_Taquin::Square_Taquin(unsigned long l) : value(l) {}

Square_Taquin::Square_Taquin(const Square_Taquin& sq) : value(sq.value) {}

bool Square_Taquin::operator==(const Square_Taquin & sq) const
{
	return value == sq.value;
}

bool Square_Taquin::operator!=(const Square_Taquin & sq) const
{
	return ! (*this == sq);
}

bool Square_Taquin::operator<(const Square_Taquin & sq) const
{
	return value < sq.value;
}

bool Square_Taquin::operator<=(const Square_Taquin & sq) const
{
	return (*this == sq || *this < sq);
}

bool Square_Taquin::operator>(const Square_Taquin & sq) const
{
	return sq < *this;
}

bool Square_Taquin::operator>=(const Square_Taquin & sq) const
{
	return (sq <= *this);
}

Square_Taquin& Square_Taquin::operator=(Square_Taquin sq)
{
	value = sq.value;
	return *this;
}

Square_Taquin& Square_Taquin::operator++()
{
	++value;
	return *this;
}

Square_Taquin Square_Taquin::operator++(int)
{
	Square_Taquin tmp(*this);
	++value;
	return tmp;
}

Square_Taquin& Square_Taquin::operator--()
{
	--value;
	return *this;
}

Square_Taquin Square_Taquin::operator--(int)
{
	Square_Taquin tmp(*this);
	--value;
	return tmp;
}

void Square_Taquin::print(ostream& o) const
{
	if (*this != empty) o << value;
}
