#ifndef SQUARE_2048_ACTION_HPP
#define SQUARE_2048_ACTION_HPP

#include <string>

enum class Square_2048_action { none, neg, mult, div, destroy };

std::string to_string(Square_2048_action action);

#endif /* not SQUARE_2048_ACTION_HPP */
