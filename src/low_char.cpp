#include "low_char.hpp"

const char Low_Char::min_value = 'a';
const char Low_Char::max_value = 'z';

void Low_Char::set_value(int c)
{
	if (c < 0)
		value = '\0';
	else if (c >= 26)
		value = max_value;
	else value = min_value + (c - 1);
}

Low_Char::Low_Char(int c)
{
	set_value(c);
}

Low_Char::Low_Char(const Low_Char & c_ref) : value(c_ref.value)
{
}

Low_Char& Low_Char::operator=(Low_Char ch)
{
	value = ch.value;
	return *this;
}

Low_Char& Low_Char::operator++()
{
	if (value > max_value) throw LowCharOutOfBoundsException();
	++value;
	return *this;
}

Low_Char& Low_Char::operator--()
{
	if (value < min_value) throw LowCharOutOfBoundsException();
	--value;
	return *this;
}

Low_Char Low_Char::operator++(int)
{
	if (value > max_value) throw LowCharOutOfBoundsException();
	Low_Char res(*this);
	++value;
	return res;
}

Low_Char Low_Char::operator--(int)
{
	if (value < min_value) throw LowCharOutOfBoundsException();
	Low_Char res(*this);
	--value;
	return res;
}

bool Low_Char::operator==(const Low_Char & ch) const
{
	return value == ch.value;
}

bool Low_Char::operator!=(const Low_Char & ch) const
{
	return !(*this == ch);
}

bool Low_Char::operator<(const Low_Char & ch) const
{
	return value < ch.value;
}

bool Low_Char::operator<=(const Low_Char & ch) const
{
	return (*this < ch || *this == ch);
}

bool Low_Char::operator>(const Low_Char & ch) const
{
	return ch < *this;
}

bool Low_Char::operator>=(const Low_Char & ch) const
{
	return ch <= * this;
}

ostream& operator<<(ostream& o, const Low_Char& ch)
{
	o << ch.value;
	return o;
}
