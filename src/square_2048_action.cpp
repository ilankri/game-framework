#include "square_2048_action.hpp"

std::string to_string(Square_2048_action action)
{
	switch (action) {
	case Square_2048_action::neg:
		return "-";
	case Square_2048_action::mult:
		return "*";
	case Square_2048_action::div:
		return "/";
	case Square_2048_action::destroy:
		return "X";
	default:
		return "";
	}
}
