#ifndef CAP_CHAR_HPP
#define CAP_CHAR_HPP

#include <iostream>
using namespace std;

class CapCharOutOfBoundsException {
	/* il n'y a que 26 lettres dans l'alphabet, donc
	   cette exception sera levée si on essaye d'incrémenter Z
	   ou de décrémenter A */
};

class Cap_Char {

private:
	char value;

	void set_value(int);

public:
	static const char min_value;

	static const char max_value;
	
	Cap_Char(int c = 1);

	Cap_Char(const Cap_Char &);

	Cap_Char& operator=(Cap_Char);
	
	Cap_Char& operator++();

	Cap_Char& operator--();

	Cap_Char operator++(int);

	Cap_Char operator--(int);

	bool operator==(const Cap_Char &) const;

	bool operator!=(const Cap_Char &) const;

	bool operator<(const Cap_Char &) const;

	bool operator<=(const Cap_Char &) const;

	bool operator>(const Cap_Char &) const;

	bool operator>=(const Cap_Char &) const;

	friend ostream& operator<<(ostream&, const Cap_Char&);
	
};

#endif
