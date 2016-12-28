#include "game_2048.hpp"

Game_2048::Game_2048(int height) :
	Game<Square_2048>(height, height), board_change(false) {}

void Game_2048::transpose_board()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < i; j++)
			board[i][j].swap(board[j][i]);
}

int Game_2048::random_value()
{
	return (1 + rand() % 2) *2;
}

Square_2048 Game_2048::random_square()
{
	Square_2048 res(Square_2048_action::none, random_value());
	return res;
}

void Game_2048::init()
{
	int pos_h1;
	int pos_l1;
	int pos_h2;
	int pos_l2;

	srand(time(nullptr));
	pos_h1 = rand() % height;
	pos_l1 = rand() % height;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < height; j++)
			board[i][j] = Square_2048::empty;
	do {
		pos_h2 = rand() % height;
		pos_l2 = rand() % height;
	} while (pos_h2 == pos_h1 && pos_l2 == pos_l1);
	board[pos_h1][pos_l1] = Square_2048(Square_2048_action::none,
					    (1 + rand() % 2) * 2);
	board[pos_h2][pos_l2] = Square_2048(Square_2048_action::none,
					    (1 + rand() % 2) * 2);
}

bool Game_2048::is_over() const
{
	return false;
}

template<class It>
int Game_2048::slide_line_template(It begin, It end)
{
	It new_begin(begin);
	int first_empty_index = 0;

	for (It it = begin; it != end; ++it)
		if (!it->is_empty()) {
			*new_begin = *it;
			++new_begin;
			first_empty_index++;
		}
	for (It it = new_begin; it != end; ++it)
		*it = Square_2048::empty;
	return first_empty_index;
}

void Game_2048::add_empty_square(int i, int j)
{
	empty_squares.push_back(Ordered_pair<int, int>(i, j));
}

void Game_2048::slide_line(int i, Direction dir)
{
	int bound;

	merge_line(i, dir);

	switch (dir) {
	case Direction::left:
		bound = slide_line_template(board[i].begin(), board[i].end());
		for (int j = bound; j < height; j++)
			add_empty_square(i, j);
		break;
	case Direction::right:
		bound = height -
			slide_line_template(board[i].rbegin(), board[i].rend());
		for (int j = 0; j < bound; j++)
			add_empty_square(i, j);
		break;
	default:
		break;
	}
}

template<class It>
void Game_2048::merge_line_template(It begin, It end)
{
	bool already_merged = false;

	for (It it = begin; it != end; ++it) {
		if (!already_merged && it[0].is_mergeable(it[1])) {
			it[1] = it[0].merge(it[1]);
			it[0] = Square_2048::empty;
			already_merged = true;
			score += j[1].get_value();
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
	Ordered_pair<int, int> pos(empty_squares[k]);
	int i = pos.get_first();
	int j = pos.get_second();

	board[i][j] = Square_2048(Square_2048_action::none, 2);
}

void Game_2048::slide_board(Direction dir, bool transpose)
{
	if (transpose)
		transpose_board();

	for (int i = 0; i < height; i++) {
		vector<Square_2048> old_line(board[i]);

		slide_line(i, dir);
		for (int j = 0; j < height; j++)
			if (old_line[j] != board[i][j]) {
				board_change = true;
				break;
			}
	}

	if (board_change && !empty_squares.empty())
		pop_up_new_square();

	board_change = false;
	empty_squares.clear();

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
}
