#ifndef CHAR_EXCEPTION_HPP
#define CHAR_EXCEPTION_HPP

#include <string>
using namespace std;

class CharOutOfBoundsException {
	/* This exception is thrown when you try to get outside of intervals [a-z] and [A-Z] */
private:
	string message;
public:

	static const string decrement_a;

	static const string increment_z;
	
	CharOutOfBoundsException(string message);
	
	string getMessage();
};


#endif
