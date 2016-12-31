#ifndef LOW_CHAR_HPP
#define LOW_CHAR_HPP

#include <iostream>
using namespace std;

class LowCharOutOfBoundsException {
	/* Exception levée si on tente de sortir de l'espace a-z */
};

class Low_Char {

private:
	char value;

	void set_value(int);

public:
	static const char min_value;

	static const char max_value;
	
	Low_Char(int c = 1);

	Low_Char(const Low_Char &);

	Low_Char& operator=(Low_Char);
	
	Low_Char& operator++();

	Low_Char& operator--();

	Low_Char operator++(int);

	Low_Char operator--(int);

	bool operator==(const Low_Char &) const;

	bool operator!=(const Low_Char &) const;

	bool operator<(const Low_Char &) const;

	bool operator<=(const Low_Char &) const;

	bool operator>(const Low_Char &) const;

	bool operator>=(const Low_Char &) const;

	friend ostream& operator<<(ostream&, const Low_Char&);
	
};

#endif
