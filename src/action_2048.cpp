#include "action_2048.hpp"

std::string to_string(Action_2048 action)
{
	switch (action) {
	case Action_2048::neg:
		return "-";
	case Action_2048::mult:
		return "*";
	case Action_2048::div:
		return "/";
	case Action_2048::destroy:
		return "X";
	default:
		return "";
	}
}
