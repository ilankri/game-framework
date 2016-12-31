#ifndef SQUARE_TAQUIN_HPP
#define SQUARE_TAQUIN_HPP

#include <iostream>

#include "printable.hpp"

template<class C>
class Square_Taquin : public Printable {
	
public:
	Square_Taquin(int val = 1);

	Square_Taquin(const Square_Taquin<C>&);

	static const Square_Taquin<C> empty;

	bool operator==(const Square_Taquin<C> &) const;

	bool operator!=(const Square_Taquin<C> &) const;

	bool operator<(const Square_Taquin<C> &) const;

	bool operator<=(const Square_Taquin<C> &) const;

	bool operator>(const Square_Taquin<C> &) const;

	bool operator>=(const Square_Taquin<C> &) const;

	Square_Taquin<C>& operator=(Square_Taquin<C>);

	Square_Taquin<C>& operator++();

	Square_Taquin<C> operator++(int);

	Square_Taquin<C>& operator--();

	Square_Taquin<C> operator--(int);
	
private:
	virtual void print(ostream& o) const;

	C value;

	
};

template<class C>
const Square_Taquin<C> Square_Taquin<C>::empty(0);

template<class C>
Square_Taquin<C>::Square_Taquin(int val) : value(val) {}

template<class C>
Square_Taquin<C>::Square_Taquin(const Square_Taquin<C>& sq) : value(sq.value) {}

template<class C>
bool Square_Taquin<C>::operator==(const Square_Taquin<C> & sq) const
{
	return value == sq.value;
}

template<class C>
bool Square_Taquin<C>::operator!=(const Square_Taquin<C> & sq) const
{
	return ! (*this == sq);
}

template<class C>
bool Square_Taquin<C>::operator<(const Square_Taquin<C> & sq) const
{
	return value < sq.value;
}

template<class C>
bool Square_Taquin<C>::operator<=(const Square_Taquin<C> & sq) const
{
	return (*this == sq || *this < sq);
}

template<class C>
bool Square_Taquin<C>::operator>(const Square_Taquin<C> & sq) const
{
	return sq < *this;
}

template<class C>
bool Square_Taquin<C>::operator>=(const Square_Taquin<C> & sq) const
{
	return (sq <= *this);
}

template<class C>
Square_Taquin<C>& Square_Taquin<C>::operator=(Square_Taquin<C> sq)
{
	value = sq.value;
	return *this;
}

template<class C>
Square_Taquin<C>& Square_Taquin<C>::operator++()
{
	++value;
	return *this;
}

template<class C>
Square_Taquin<C> Square_Taquin<C>::operator++(int)
{
	Square_Taquin<C> tmp(*this);
	++value;
	return tmp;
}

template<class C>
Square_Taquin<C>& Square_Taquin<C>::operator--()
{
	--value;
	return *this;
}

template<class C>
Square_Taquin<C> Square_Taquin<C>::operator--(int)
{
	Square_Taquin<C> tmp(*this);
	--value;
	return tmp;
}

template<class C>
void Square_Taquin<C>::print(ostream& o) const
{
	if (*this != empty) o << value;
}


#endif
