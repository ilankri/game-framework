#ifndef CAP_CHAR_HPP
#define CAP_CHAR_HPP

#include <iostream>
#include "char_exception.hpp"

using namespace std;

class Cap_Char {

private:
	char value;

	void set_value(unsigned int);

public:
	static const char min_value;

	static const char max_value;
	
	Cap_Char(unsigned int c = 1);

	Cap_Char(const Cap_Char &);

	Cap_Char& operator=(const Cap_Char &);
	
	Cap_Char& operator++() throw (CharOutOfBoundsException);

	Cap_Char& operator--() throw (CharOutOfBoundsException);

	Cap_Char operator++(int) throw (CharOutOfBoundsException);

	Cap_Char operator--(int) throw (CharOutOfBoundsException);

	bool operator==(const Cap_Char &) const;

	bool operator!=(const Cap_Char &) const;

	bool operator<(const Cap_Char &) const;

	bool operator<=(const Cap_Char &) const;

	bool operator>(const Cap_Char &) const;

	bool operator>=(const Cap_Char &) const;

	friend ostream& operator<<(ostream&, const Cap_Char&);
	
};

#endif
