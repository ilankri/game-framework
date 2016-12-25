#include "printable.hpp"

ostream& operator<<(ostream& out, const Printable& object)
{
	object.print(out);
	return out;
}
