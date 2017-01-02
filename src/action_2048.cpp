#include "action_2048.hpp"

std::string to_string(Action_2048 action)
{
	switch (action) {
	case Action_2048::mult:
		return "x";
	case Action_2048::destroy:
		return "X";
	default:
		return "";
	}
}
