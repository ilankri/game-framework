#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

using namespace std;

enum class Direction { up, down, left, right };

template<class Sq>
class Game {
public:
	Game(int h, int w);

	void play();

	void demo();

	virtual ~Game();

protected:
	const int height;

	const int width;

	Sq** board;

	long score;

private:
	bool quit;

	virtual void init() = 0;

	virtual bool is_over() const = 0;

	virtual void move(Direction) = 0;

	void print(ostream& o = cout) const;

	template<class S>
	friend ostream& operator<<(ostream& o, const Game<S>& game);

	void move_up();

	void move_down();

	void move_left();

	void move_right();

	virtual bool is_stuck() const;
};

template<class Sq>
Game<Sq>::Game(int h, int w) : height(h), width(w), board(new Sq*[h]),
			       score(0), quit(false)
{
	for (int i = 0; i < h; i++)
		board[i] = new Sq[w];
}

template<class Sq>
void Game<Sq>::play() {
	int rep;

	while (!is_over() && !quit) {
		cout << *this;
		cout << "Entrer (2, 4, 8 ou 6) pour effectuer ";
		cout << "un déplacement (resp. bas, gauche, haut, droite) ";
		cout << "ou 0 pour quitter le jeu : ";
		cin >> rep;
		cin.ignore();
		switch (rep) {
		case 6:
			move_right();
			break;
		case 2:
			move_down();
			break;
		case 4:
			move_left();
			break;
		case 8:
			move_up();
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
	/*
	 * Ceci est une version naïve : essayer si possible de rendre le
	 * robot plus intelligent.
	 */
	srand(time(nullptr));
	while (!is_over()) {
		cout << *this;
		int sens = rand() % 4;
		switch(sens) {
		case 0:
			move_right();
			break;
		case 1:
			move_down();
			break;
		case 2:
			move_left();
			break;
		case 3:
			move_up();
			break;
		default:
			break;
		}
	}
	cout << *this;
}

template<class S>
ostream& operator<<(ostream& o, const Game<S>& j)
{
	j.print();
	o << "score : " << j.score << endl;
	if (j.is_stuck())
		o << "Game blocked !" << endl;
	if (j.is_over())
		o << "Game Over" << endl;
	return o;
}

template<class Sq>
Game<Sq>::~Game()
{
	for (int i = 0; i < height; i++)
		delete[] board[i];
	delete[] board;
}

template<class Sq>
void Game<Sq>::print(ostream& o) const
{
	// longueur d'une ligne, en tenant compte des tabulations
	int line_len_with_tabs = 8 * width + 2;

	for (int j = 0; j < line_len_with_tabs; j++)
		o << "-";
	o << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			const Sq& case_cur = board[i][j];

			o << "| ";
			/* if (case_cur == caseVide) */
			/*	o << " "; */
			/* else */
			o << case_cur;
			o << "\t";
		}
		o << " |" << endl;
		for (int j = 0; j < line_len_with_tabs; j++)
			o << "-";
		o << endl;
	}
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


template<class Sq>
bool Game<Sq>::is_stuck() const
{
	return false;
}

#endif	/* not GAME_HPP */
