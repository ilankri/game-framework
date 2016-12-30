#ifndef ACTION_2048_HPP
#define ACTION_2048_HPP

#include <string>

enum class Action_2048 { empty, none, neg, mult, div, destroy };

std::string to_string(Action_2048 action);

#endif /* not ACTION_2048_HPP */
