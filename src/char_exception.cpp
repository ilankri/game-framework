#include "char_exception.hpp"

const string CharOutOfBoundsException::decrement_a = "[CharOutOfBoundsException] Only 26 letters in alphabet. 'A/a' cannot be decremented.";

const string CharOutOfBoundsException::increment_z = "[CharOutOfBoundsException] Only 26 letters in alphabet. 'Z/z' cannot be incremented.";

CharOutOfBoundsException::CharOutOfBoundsException(string message) : message(message)
{
}

string CharOutOfBoundsException::getMessage()
{
	return message;
}
