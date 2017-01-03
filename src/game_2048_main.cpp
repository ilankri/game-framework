#include "game_2048.hpp"
#include "game_2048_neg.hpp"
#include "game_2048_num.hpp"
#include "game_2048_fancy.hpp"
#include "game_2048_mix.hpp"

#include <unistd.h>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

/*
 * Return true if and only if at least two of the three conditions are
 * true.
 */
bool at_least_two(bool b1, bool b2, bool b3)
{
	return (b1 && b2) || (b1 && b3) || (b2 && b3);
}

void print_usage(ostream& out, string prgm_name)
{
	out << "Usage: " << prgm_name << " [options]" << endl <<
		"Options:" << endl <<
		"-d Enable destroy squares" << endl <<
		"-D Show a demonstration" << endl <<
		"-h Display this help" << endl <<
		"-m Enable multiply squares" << endl <<
		"-n Enable negative numbers" << endl <<
		"-s <size> Set board's height and width to <size>" << endl <<
		"-v <value> Add <value> to possible values for squares" << endl;
}

int main(int argc, char **argv)
{
	int height = 4;
	bool demo = false;
	bool neg = false;
	bool fancy = false;
	bool num = false;
	vector<long long> values;
	vector<Action_2048> actions;
	const char* shortopts = "dDhmns:v:";
	int opt = getopt(argc, argv, shortopts);
	Game_2048 *game;

	/* Command-line arguments parsing.  */
	while (opt != -1) {
		switch (opt) {
		case 'd':
			actions.push_back(Action_2048::destroy);
			fancy = true;
			break;
		case 'D':
			demo = true;
			break;
		case 'h':
			print_usage(cout, argv[0]);
			return 0;
			break;
		case 'm':
			actions.push_back(Action_2048::mult);
			fancy = true;
			break;
		case 'n':
			neg = true;
			break;
		case 's':
			try {
				height = stoi(optarg);
				break;
			} catch (invalid_argument ia) {}
			break;
		case 'v':
			try {
				values.push_back(stoll(optarg));
				num = true;
				break;
			} catch (invalid_argument ia) {}
		default:
			print_usage(cerr, argv[0]);
			return 1;
		}
		opt = getopt(argc, argv, shortopts);
	}

	/* Ensure that the set of values is nonempty.  */
	if (values.empty())
		values.push_back(2);

	/* Interpret the command-line arguments.  */
	if (at_least_two(neg, num, fancy))
		game = new Game_2048_mix(height, values, actions);
	else if (neg)
		game = new Game_2048_neg(height);
	else if (num)
		game = new Game_2048_num(height, values);
	else if (fancy)
		game = new Game_2048_fancy(height, actions);
	else
		game = new Game_2048(height);
	if (demo)
		game->demo();
	else
		game->play();

	delete game;
	return 0;
}
