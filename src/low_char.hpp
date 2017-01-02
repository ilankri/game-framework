#ifndef LOW_CHAR_HPP
#define LOW_CHAR_HPP

#include <iostream>
#include "char_exception.hpp"

using namespace std;

class Low_Char {

private:
	char value;

	void set_value(unsigned int);

public:
	static const char min_value;

	static const char max_value;
	
	Low_Char(unsigned int c = 1);

	Low_Char(const Low_Char &);

	Low_Char& operator=(const Low_Char &);
	
	Low_Char& operator++() throw (CharOutOfBoundsException);

	Low_Char& operator--() throw (CharOutOfBoundsException);

	Low_Char operator++(int) throw (CharOutOfBoundsException);

	Low_Char operator--(int) throw (CharOutOfBoundsException);

	bool operator==(const Low_Char &) const;

	bool operator!=(const Low_Char &) const;

	bool operator<(const Low_Char &) const;

	bool operator<=(const Low_Char &) const;

	bool operator>(const Low_Char &) const;

	bool operator>=(const Low_Char &) const;

	friend ostream& operator<<(ostream&, const Low_Char&);
	
};

#endif
