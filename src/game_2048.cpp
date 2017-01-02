#include "game_2048.hpp"

Game_2048::Game_2048(int height) :
	Game<Square_2048>(height, height),
	board_change(false),
	full(false) {}

void Game_2048::transpose_board()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < i; j++)
			board[i][j].swap(board[j][i]);
}

unsigned long long Game_2048::random_value() const
{
	return (1 + (rand() & 1)) << 1;
}

Square_2048 Game_2048::random_square() const
{
	return Square_2048(Action_2048::none, random_value());
}

void Game_2048::init()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < height; j++) {
			board[i][j] = Square_2048::empty;
			add_empty_square(i, j);
		}
	pop_up_new_square();
	pop_up_new_square();
}

/*
 * The game is over when the board is full and there is no possible
 * merging.
 */
bool Game_2048::is_over() const
{
	if (full) {
		int height_minus_one = height - 1;

		/* Search for a mergeable pair of squares.  */
		for (int i = 0; i < height; i++)
			for (int j = 0; j < height_minus_one; j++)
				if (mergeable(board[i][j], board[i][j + 1]) ||
				    mergeable(board[j][i], board[j + 1][i]))
					return false;

		return true;
	}
	return false;
}

template<class It>
int Game_2048::slide_merged_line(It begin, It end)
{
	/* Pointer to the first empty square on the current line.  */
	It first_empty(begin);

	/*
	 * The index of the first empty square on the current line
	 * beginning from the edge of the board.
	 */
	int first_empty_index = 0;

	/* Move nonempty squares to the edge.  */
	for (It it = begin; it != end; ++it)
		if (!it->is_empty()) {
			*first_empty = *it;
			++first_empty;
			first_empty_index++;
		}

	/* Fill the rest of the line with empty squares.  */
	for (It it = first_empty; it != end; ++it)
		*it = Square_2048::empty;

	return first_empty_index;
}

void Game_2048::add_empty_square(int i, int j)
{
	empty_squares.push_front(pair<int, int>(i, j));
}

void Game_2048::slide_line(int i, Direction dir)
{
	/* Compute the mergings.  */
	merge_line(i, dir);

	/* Slide the nonempty squares to the edge.  */
	switch (dir) {
		/*
		 * Index of the first empty square after sliding line i in
		 * direction dir.
		 */
		int bound;

	case Direction::left:
		bound = slide_merged_line(board[i].begin(), board[i].end());

		/* Update empty squares set.  */
		for (int j = bound; j < height; j++)
			add_empty_square(i, j);
		break;
	case Direction::right:
		bound = height -
			slide_merged_line(board[i].rbegin(), board[i].rend());

		/* Update empty squares set.  */
		for (int j = 0; j < bound; j++)
			add_empty_square(i, j);
		break;
	default:
		break;
	}
}

/*
 * Idea of the merging algorithm:
 *
 * To apply all the merging on a single line, cross the line and test if
 * two adjacent squares are mergeable.  If so, empty the square that is
 * the closest to the board edge and store the result in the other one.
 * Otherwise, if the square that is the furthest to the board edge is
 * empty, swap the two current squares, else do nothing.
 */
template<class It>
void Game_2048::merge_line_template(It begin, It end)
{
	/*
	 * Whether the current square (i.e. it[0] in the following loop)
	 * has already been merged.
	 */
	bool already_merged = false;

	for (It it = begin; it != end; ++it) {
		if (!already_merged && mergeable(it[0], it[1])) {
			it[1] = merge(it[0], it[1]);
			it[0] = Square_2048::empty;
			already_merged = true;
			score += it[1].get_value();
		} else {
			if (it[1].is_empty())
				it[0].swap(it[1]);
			else
				already_merged = false;
		}
	}
}

void Game_2048::merge_line(int i, Direction dir)
{
	switch (dir) {
	case Direction::left:
		merge_line_template(board[i].begin(), board[i].end() - 1);
		break;
	case Direction::right:
		merge_line_template(board[i].rbegin(), board[i].rend() - 1);
		break;
	default:
		break;
	}
}

void Game_2048::pop_up_new_square()
{
	int k = rand() % empty_squares.size();
	auto pos = empty_squares.begin();

	for (; k > 0; ++pos)
		k--;
	board[pos->first][pos->second] = random_square();
	empty_squares.erase(pos);
	full = empty_squares.size() == 0;
}

void Game_2048::slide_board(Direction dir, bool transpose)
{
	if (transpose)
		transpose_board();
	for (int i = 0; i < height; i++) {
		/* Line configuration before sliding.  */
		vector<Square_2048> old_line(board[i]);

		slide_line(i, dir);

		/*
		 * Check if the sliding really changed the game
		 * configuration, i.e. a line changed.
		 */
		for (int j = 0; j < height; j++)
			if (old_line[j] != board[i][j]) {
				board_change = true;
				break;
			}
	}

	/*
	 * A new square appears if and only if the board configuration
	 * changed and there is an empty square.
	 */
	if (board_change && !empty_squares.empty())
		pop_up_new_square();

	if (transpose)
		transpose_board();
}

void Game_2048::move(Direction dir)
{
	switch (dir) {
	case Direction::left:
	case Direction::right:
		slide_board(dir, false);
		break;
	case Direction::up:
		slide_board(Direction::left, true);
		break;
	case Direction::down:
		slide_board(Direction::right, true);
		break;
	default:
		break;
	}

	/* Reset turn local variables.  */
	board_change = false;
	empty_squares.clear();
}

bool Game_2048::mergeable(const Square_2048& sq1,
			  const Square_2048& sq2) const
{
	if (sq1 == sq2) {
		if (sq2.get_action() == Action_2048::none)
			return true;

		if (sq2.get_action() == Action_2048::neg)
			return true;
	}

	if (sq1.mult_possible(sq2))
		return true;

	if (sq1.is_opposite(sq2))
		return true;

	if (sq1.dest_possible(sq2))
		return true;

	return false;
}

Square_2048 Game_2048::merge(const Square_2048& sq1,
			     const Square_2048& sq2) const
{
	if (sq1.is_opposite(sq2) || sq1.dest_possible(sq2))
		return Square_2048::empty;

	if (sq1.mult_possible(sq2)) {

		unsigned long long res_val = sq1.get_value() * sq2.get_value();
		Action_2048 res_action;

		if (sq1.get_action() == Action_2048::mult)
			res_action = sq2.get_action();
		else
			res_action = sq1.get_action();

		return Square_2048(res_action,res_val);
	}

	return Square_2048(sq2.get_action(), sq2.get_value() << 1);
}
