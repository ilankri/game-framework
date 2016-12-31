#ifndef TAQUIN_HPP
#define TAQUIN_HPP

#include "game.hpp"
#include "square_taquin.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

template<class C = int>
class Taquin : public Game<Square_Taquin<C>> {
public:
	Taquin(int h, int w);

	virtual ~Taquin();

	/* this value represents the empty square */
	static const Square_Taquin<C> empty;

private:
	static const int min_height;

	static const int min_width;
	
	/* coordinates of empty square */
	int pos_empty_w;

	int pos_empty_h;

	virtual void init();

	virtual bool is_over() const;

	virtual void move(Direction s);

	void fill();

	void mix();
};

template<class C>
const Square_Taquin<C> Taquin<C>::empty(Square_Taquin<C>::empty);

template<class C>
const int Taquin<C>::min_width = 3;

template<class C>
const int Taquin<C>::min_height = 3;

template<class C>
Taquin<C>::Taquin(int h, int w) :
	Game<Square_Taquin<C>>(max(min_height,h), max(min_width,w))
{
}

template<class C>
Taquin<C>::~Taquin() {}

template<class C>
void Taquin<C>::init()
{
	fill();
	mix();
}

template<class C>
void Taquin<C>::fill()
{
	const int& height = this -> height;
	const int& width = this -> width;
	
	Square_Taquin<C> tmp = 1;

	srand(time(nullptr));
	// On remplit les cases.
	for (int i = 0; i < height -1; i++) {
		for (int j = 0; j < width; j++) {
			this -> board[i][j] = tmp++;
		}
	}
	for (int j = 0; j < width -1; j++) {
		this -> board[height - 1][j] = tmp++;
	}
	this -> board[height - 1][width - 1] = 0;
	pos_empty_h = height - 1;
	pos_empty_w = width - 1;

}

template<class C>
void Taquin<C>::mix()
{

	const int& height = this -> height;
	const int& width = this -> width;
	
	/*
	 * La parité d'une permutation est celle du nombre d'échanges
	 * successifs qu'il faut faire pour obtenir la grille finale.
	 */
	bool perm_paire = true;

	/*
	 * La parité de la case vide est celle du nombre de déplacements
	 * à effectuer pour la mettre en bas à droite.
	 */
	bool case_vide_paire = true;

	// On mélange les cases.
	int i1 = 0;
	int j1 = 0;
	int i2 = 0;
	int j2 = 0;

	int board_size = width * height;

	for (int k = 0; k < board_size; k++) {
		i1 = rand() % height;
		j1 = rand() % width;

		do {
			i2 = rand() % height;
			j2 = rand() % width;
		} while (i1 == i2 && j1 == j2);

		Square_Taquin<C> tmp = this -> board[i1][j1];
		this -> board[i1][j1] = this -> board[i2][j2];
		this -> board[i2][j2] = tmp;
		perm_paire = !perm_paire;

		// On met à jour les coordonnées de la case vide.
		if (this -> board[i1][j1] == empty) {
			pos_empty_h = i1;
			pos_empty_w = j1;
		} else if (this -> board[i2][j2] == empty) {
			pos_empty_h = i2;
			pos_empty_w = j2;
		}
		case_vide_paire = ((width - 1 - pos_empty_w) +
				   (height - 1 - pos_empty_h)) % 2 == 0;
	}

	/*
	 * Pour que la grille soit résolvable, il faut que la
	 * permutation soit de même parité que la case vide.
	 */
	if (case_vide_paire ^ perm_paire) {
		do {
			i1 = rand() % height;
			j1 = rand() % width;
		} while (i1 == pos_empty_h && j1 == pos_empty_w);
		do {
			i2 = rand() % height;
			j2 = rand() % width;
		} while ((i2 == pos_empty_h && j2 == pos_empty_w) ||
			 (i2 == i1 && j2 == j1));
		Square_Taquin<C> tmp = this -> board[i1][j1];
		this -> board[i1][j1] = this -> board[i2][j2];
		this -> board[i2][j2] = tmp;
	}
}

template<class C>
bool Taquin<C>::is_over() const
{
	const int& height = this -> height;
	const int& width = this -> width;
	
	if (this -> board[height - 1][width - 1] != empty) {
		return false;
	}

	for (int j = 1; j < width; j++) {
		// On teste si la première ligne est triée.
		if (this -> board[0][j] < this -> board[0][j-1])
			return false;
	}
	for (int i = 1; i < height - 1; i++) {
		/*
		 * À partir de la 2e ligne, on regarde d'abord si la 1re
		 * case est supérieure à la dernière de la ligne
		 * précédente.
		 */
		if (this -> board[i][0] < this -> board[i - 1][width - 1])
			return false;
		for (int j = 1; j < width; j++) {
			// On teste ensuite si la ligne i est triée.
			if (this -> board[i][j] < this -> board[i][j - 1])
				return false;
		}
	}

	if (this -> board[height - 1][0] < this -> board[height - 2][width - 1])
		return false;
	for (int j = 1; j < width - 1; j++) {
		/*
		 * On teste si la dernière ligne est triée (sans tenir
		 * compte de la dernière case, qui doit être vide.
		 */
		if (this -> board[height - 1][j] < this -> board[height - 1][j - 1])
			return false;
	}

	return true;
}

template<class C>
void Taquin<C>::move(Direction s)
{
	int dir_w = 0;
	int dir_h = 0;

	switch (s) {
	case Direction::up:
		dir_h = (pos_empty_h > 0) ? -1 : 0;
		break;
	case Direction::down:
		dir_h = (pos_empty_h < this -> height - 1) ? 1 : 0;
		break;
	case Direction::left:
		dir_w = (pos_empty_w > 0) ? -1 : 0;
		break;
	case Direction::right:
		dir_w = (pos_empty_w < this -> width - 1) ? 1 : 0;
		break;
	default:
		break;
	}

	Square_Taquin<C>& source = this -> board[pos_empty_h][pos_empty_w];
	Square_Taquin<C>& dest = this -> board[pos_empty_h + dir_h][pos_empty_w + dir_w];

	if (dir_h != 0 || dir_w != 0) {
		Square_Taquin<C> tmp = source;
		source = dest;
		dest = tmp;
		pos_empty_h += dir_h;
		pos_empty_w += dir_w;
		this -> score++;
	}
}


#endif	/* not TAQUIN_HPP */
