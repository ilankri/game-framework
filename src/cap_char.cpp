#include "cap_char.hpp"

const char Cap_Char::min_value = 'A';
const char Cap_Char::max_value = 'Z';

void Cap_Char::set_value(unsigned int c)
{
	if (c == 0)
		value = '\0';
	else if (c >= 26)
		value = max_value;
	else value = (min_value) + (c - 1);
}

Cap_Char::Cap_Char(unsigned int c)
{
	set_value(c);
}

Cap_Char::Cap_Char(const Cap_Char & c_ref) : value(c_ref.value)
{
}

Cap_Char& Cap_Char::operator=(const Cap_Char& ch)
{
	value = ch.value;
	return *this;
}

Cap_Char& Cap_Char::operator++()
{
	if (value > max_value)
		throw CharOutOfBoundsException(CharOutOfBoundsException::increment_z);
	++value;
	return *this;
}

Cap_Char& Cap_Char::operator--()
{
	if (value < min_value)
		throw CharOutOfBoundsException(CharOutOfBoundsException::decrement_a);
	--value;
	return *this;
}

Cap_Char Cap_Char::operator++(int)
{
	if (value > max_value)
		throw CharOutOfBoundsException(CharOutOfBoundsException::increment_z);
	Cap_Char res(*this);
	++value;
	return res;
}

Cap_Char Cap_Char::operator--(int)
{
	if (value < min_value)
		throw CharOutOfBoundsException(CharOutOfBoundsException::decrement_a);
	Cap_Char res(*this);
	--value;
	return res;
}

bool Cap_Char::operator==(const Cap_Char & ch) const
{
	return value == ch.value;
}

bool Cap_Char::operator!=(const Cap_Char & ch) const
{
	return !(*this == ch);
}

bool Cap_Char::operator<(const Cap_Char & ch) const
{
	return value < ch.value;
}

bool Cap_Char::operator<=(const Cap_Char & ch) const
{
	return (*this < ch || *this == ch);
}

bool Cap_Char::operator>(const Cap_Char & ch) const
{
	return ch < *this;
}

bool Cap_Char::operator>=(const Cap_Char & ch) const
{
	return ch <= * this;
}

ostream& operator<<(ostream& o, const Cap_Char& ch)
{
	o << ch.value;
	return o;
}
