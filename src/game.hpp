#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

using namespace std;

/* Possible movements.  */
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

	/* Start a human playable game.  */
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
	srand(time(nullptr));
}

template<class Sq>
Game<Sq>::~Game()
{
	delete[] board;
}


template<class Sq>
void Game<Sq>::play()
{
	init();
	while (!is_over() && !quit) {
		char key;

		cout << *this <<
			"Input e, d, s or f to make a move "
			"(resp. up, down, left, right), "
			"or q to exit: ";
		key = cin.get();
		cin.ignore(256, '\n');
		switch (key) {
		case 'e':
			move_up();
			break;
		case 'd':
			move_down();
			break;
		case 's':
			move_left();
			break;
		case 'f':
			move_right();
			break;
		case 'q':
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
	while (!is_over()) {
		int dir = rand() % 4;

		cout << *this;
		switch(dir) {
		case 0:
			cout << "Move up." << endl;
			move_up();
			break;
		case 1:
			cout << "Move down." << endl;
			move_down();
			break;
		case 2:
			cout << "Move left." << endl;
			move_left();
			break;
		case 3:
			cout << "Move right." << endl;
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
	out << endl;
	game.print_board();
	out << "Score: " << game.score << endl;
	if (game.is_stuck())
		out << "Game blocked!" << endl;
	if (game.is_over())
		out << "Game over!" << endl;
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
