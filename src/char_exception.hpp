#ifndef CHAR_EXCEPTION_HPP
#define CHAR_EXCEPTION_HPP

#include <string>
using namespace std;

class CharOutOfBoundsException {
	/* Exception levée si on tente de sortir des espaces [a-z] et [A-Z] */
private:
	string message;
public:

	static const string decrement_a;

	static const string increment_z;
	
	CharOutOfBoundsException(string message);
	string getMessage();
};


#endif
