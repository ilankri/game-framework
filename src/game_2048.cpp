#include "game_2048.hpp"

Game_2048::Game_2048(int height, int width) :
	Game<Square_2048>(height, width), first_empty_old_index(0),
	first_empty_new_index(0), board_change(false)
{

}

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
	srand(time(nullptr));
	int pos_h1 = rand() % height;
	int pos_l1 = rand() % width;
	int pos_h2;
	int pos_l2;

	do {
		pos_h2 = rand() % height;
		pos_l2 = rand() % width;
	} while (pos_h2 == pos_h1 && pos_l2 == pos_l1);
	board[pos_h1][pos_l1]=random_square();
	board[pos_h2][pos_l2]=random_square();
	/* board[0][0].set_value(2); */
	/* board[0][1].set_value(2); */
	/* board[0][2].set_value(4); */
	/* board[0][3].set_value(4); */
	/* board[0][4].set_value(4); */
}

bool Game_2048::is_over() const
{
	return false;
}

/* pas de changement de board si la pos de la 1ere case vide n'a pas change */
template<class It>
void Game_2048::slide_line_aux(It begin, It end)
{
	It it_bis(begin);

	for (It it = begin; it != end; ++it)
		if (!it->is_empty()) {
			*it_bis = *it;
			++it_bis;
			first_empty_new_index++;
		}
	for (It it = it_bis; it != end; ++it)
		*it = Square_2048::empty;
	//cout << "old " << first_empty_old_index << endl;
	//cout << "new " << first_empty_new_index << endl;
}

void Game_2048::slide_line(int i, Direction dir)
{
	switch (dir) {
	case Direction::left:
		slide_line_aux(board[i].begin(), board[i].end());
		break;
	case Direction::right:
		slide_line_aux(board[i].rbegin(), board[i].rend());
		break;
	default:
		break;
	}
}

template<class It>
void Game_2048::merge_line_aux(It begin, It end)
{
	bool already_merged = false;

	for (It j = begin; j != end; ++j)
		if (!already_merged && j[0].is_mergeable(j[1])) {
			Square_2048 tmp(j[1]);

			j[1] = j[0].merge(tmp);
			j[0] = Square_2048::empty;
			already_merged = true;
			score += j[1].get_value();
			/* board_change = true; */
		} else {
			if (j[1].is_empty())
				j[0].swap(j[1]);
			already_merged = false;
		}
}

void Game_2048::merge_line(int i, Direction dir)
{
	switch (dir) {
	case Direction::left:
		merge_line_aux(board[i].begin(), board[i].end() - 1);
		break;
	case Direction::right:
		merge_line_aux(board[i].rbegin(), board[i].rend() - 1);
		break;
	default:
		break;
	}
}

void Game_2048::slide_board(Direction dir, bool need_transpose)
{
	if (need_transpose)
		transpose_board();
	/* calculer ici le first_empty_old_index */
	for (int i = 0; i < width; i++) {
		for (vector<Square_2048>::iterator it = board[i].begin();
		     it != board[i].end() && !it->is_empty(); ++it)
			first_empty_old_index++;
		merge_line(i, dir);
		slide_line(i, dir);
		if (first_empty_new_index != first_empty_old_index)
			board_change = true;
		first_empty_old_index = 0;
		first_empty_new_index = 0;
	}
	if (need_transpose)
		transpose_board();

}
void Game_2048::move(Direction dir)
{
	switch (dir) {
	case Direction::down:
		slide_board(Direction::right, true);
		/* transpose_board(); */
		/* merge_line(4, Direction::right); */
		/* slide_line(4, Direction::right); */
		/* transpose_board(); */
		break;
	case Direction::up:
		/* transpose_board(); */
		/* merge_line(4, Direction::left); */
		/* slide_line(4, Direction::left); */
		/* transpose_board(); */
		slide_board(Direction::left, true);
		break;
	case Direction::left:
	case Direction::right:
		slide_board(dir, false);
		/* merge_line(0, dir); */
		/* slide_line(0, dir); */
		break;
	default:
		break;
	}
	/* a appeler seulement si la grille a change! */
	if (board_change)
		fill_first_empty_square();
	board_change = false;
}

bool Game_2048::fill_first_empty_square()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (board[i][j].is_empty()) {
				board[i][j] = random_square();
				return true;
			}
	return false;
}
