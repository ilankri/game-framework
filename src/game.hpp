#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

using namespace std;

/* Allowed movements.  */
enum class Direction { up, down, left, right };

/*
 * Template abstract class representing a board game composed of
 * printable squares with four possible movements (up, down, left and
 * right).
 */
template<class Sq>
class Game {
public:
	/*
	 * A game is defined by the height and the width of its board.
	 */
	Game(int height, int width);

	virtual ~Game();

	/* Start a Human playable game.  */
	virtual void play();

	/* Game demonstration.  */
	virtual void demo();

protected:
	/* Height of the board.  */
	const int height;

	/* Width of the board.  */
	const int width;

	/* Board of the game, basically a matrix.  */
	vector<Sq>* board;

	/* Player's score.  */
	long long score;

private:
	/* Whether the player ask to quit game.  */
	bool quit;

	/* Initialize game board. */
	virtual void init() = 0;

	/*
	 * Change the game configuration according to the given
	 * movement.
	 */
	virtual void move(Direction) = 0;

	/* Check if the game is over.  */
	virtual bool is_over() const = 0;

	/*
	 * Check if the current game configuration is in a stuck state.
	 */
	virtual bool is_stuck() const;

	/* Print current game configuration.  */
	virtual void print_board(ostream& out = cout) const;

	template<class S>
	friend ostream& operator<<(ostream& out, const Game<S>& game);

	void move_up();

	void move_down();

	void move_left();

	void move_right();
};

template<class Sq>
Game<Sq>::Game(int h, int w) :
	height(h),
	width(w),
	board(new vector<Sq>[h]),
	score(0),
	quit(false)
{
	for (int i = 0; i < h; i++)
		board[i] = vector<Sq>(w);
}

template<class Sq>
Game<Sq>::~Game()
{
	delete[] board;
}


template<class Sq>
void Game<Sq>::play()
{
	int rep;

	init();
	while (!is_over() && !quit) {
		cout << *this;
		cout << "Entrer (2, 4, 8 ou 6) pour effectuer ";
		cout << "un déplacement (resp. bas, gauche, haut, droite) ";
		cout << "ou 0 pour quitter le jeu : ";
		cin >> rep;
		cin.ignore();
		switch (rep) {
		case 8:
			move_up();
			break;
		case 2:
			move_down();
			break;
		case 4:
			move_left();
			break;
		case 6:
			move_right();
			break;
		case 0:
			quit = true;
			return;
		default:
			break;
		}
	}
	cout << *this;
}

template<class Sq>
void Game<Sq>::demo() {
	init();
	srand(time(nullptr));
	while (!is_over()) {
		int dir = rand() % 4;

		cout << *this;
		switch(dir) {
		case 0:
			move_up();
			break;
		case 1:
			move_down();
			break;
		case 2:
			move_left();
			break;
		case 3:
			move_right();
			break;
		default:
			break;
		}
	}
	cout << *this;
}

/* By default a game cannot get stuck.  */
template<class Sq>
bool Game<Sq>::is_stuck() const
{
	return false;
}

template<class Sq>
void Game<Sq>::print_board(ostream& out) const
{
	/* Length of a line including tabulations.  */
	int line_len_with_tabs = 8 * width + 2;

	for (int j = 0; j < line_len_with_tabs; j++)
		out << "-";
	out << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out << "| ";
			out << board[i][j];
			out << "\t";
		}
		out << " |" << endl;
		for (int j = 0; j < line_len_with_tabs; j++)
			out << "-";
		out << endl;
	}
}

template<class Sq>
ostream& operator<<(ostream& out, const Game<Sq>& game)
{
	game.print_board();
	out << "score : " << game.score << endl;
	if (game.is_stuck())
		out << "Game blocked !" << endl;
	if (game.is_over())
		out << "Game Over" << endl;
	return out;
}

template<class Sq>
void Game<Sq>::move_up()
{
	move(Direction::up);
}

template<class Sq>
void Game<Sq>::move_down()
{
	move(Direction::down);
}

template<class Sq>
void Game<Sq>::move_left()
{
	move(Direction::left);
}

template<class Sq>
void Game<Sq>::move_right()
{
	move(Direction::right);
}

#endif	/* not GAME_HPP */
