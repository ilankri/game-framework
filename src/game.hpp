#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

using namespace std;

enum class Sens {Haut, Bas, Gauche, Droite};

template<class T>
class Game {
public:
	Game(int l, int h);

	void jouerHumain();

	void jouerRobot();

	template<class C>
	friend ostream& operator<<(ostream& o, const Game<C>& game);

	/* const T* operator[](int i) const; */

	/* T* operator[](int i); */

	virtual ~Game();

protected:
	const int longueur;

	const int hauteur;

	T** plateau;

	/* static const T caseVide = (T) 0; */

	long score;

private:
	bool quitter;

	virtual void initialiser() = 0;

	virtual bool jeuTermine() const = 0;

	virtual void deplacer(Sens) = 0;

	virtual void afficher(ostream& o = cout) const;

	void deplacerHaut();

	void deplacerBas();

	void deplacerGauche();

	void deplacerDroite();

	virtual bool jeuBloque() const;
};

template<class T>
Game<T>::Game(int l, int h) : longueur(l), hauteur(h), plateau(new T*[h]),
			    score(0), quitter(false)
{
	for (int i = 0; i < h; i++)
		plateau[i] = new T[l];
}

template<class T>
void Game<T>::jouerHumain() {
	int rep;

	while (!jeuTermine() && !quitter) {
		cout << *this;
		cout << "Entrer (2, 4, 8 ou 6) pour effectuer ";
		cout << "un déplacement (resp. bas, gauche, haut, droite) ";
		cout << "ou 0 pour quitter le jeu : ";
		cin >> rep;
		cin.ignore();
		switch (rep) {
		case 6:
			deplacerDroite();
			break;
		case 2:
			deplacerBas();
			break;
		case 4:
			deplacerGauche();
			break;
		case 8:
			deplacerHaut();
			break;
		case 0:
			quitter = true;
			return;
		default:
			break;
		}
	}
	cout << *this;
}

template<class T>
void Game<T>::jouerRobot() {
	/*
	 * Ceci est une version naïve : essayer si possible de rendre le
	 * robot plus intelligent.
	 */
	srand(time(nullptr));
	while (!jeuTermine()) {
		cout << *this;
		int sens = rand() % 4;
		switch(sens) {
		case 0:
			deplacerDroite();
			break;
		case 1:
			deplacerBas();
			break;
		case 2:
			deplacerGauche();
			break;
		case 3:
			deplacerHaut();
			break;
		default:
			break;
		}
	}
	cout << *this;
}

template<class T>
ostream& operator<<(ostream& o, const Game<T>& j)
{
	j.afficher();
	o << "score : " << j.score << endl;
	if (j.jeuBloque())
		o << "Game blocked !" << endl;
	if (j.jeuTermine())
		o << "Game Over" << endl;
	return o;
}

/* template<class T> */
/* const T* Jeu<T>::operator[](int i) const */
/* { */
/*	return plateau[i]; */
/* } */

/* template<class T> */
/* T* Jeu<T>::operator[](int i) */
/* { */
/*	return plateau[i]; */
/* } */

template<class T>
Game<T>::~Game()
{
	for (int i = 0; i < hauteur; i++)
		delete[] plateau[i];
	delete[] plateau;
}

template<class T>
void Game<T>::afficher(ostream& o) const
{
	// longueur d'une ligne, en tenant compte des tabulations
	int line_len_with_tabs = 8 * longueur + 2;

	for (int j = 0; j < line_len_with_tabs; j++)
		o << "-";
	o << endl;
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < longueur; j++) {
			const T& case_cur = plateau[i][j];

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

template<class T>
void Game<T>::deplacerHaut()
{
	deplacer(Sens::Haut);
}

template<class T>
void Game<T>::deplacerBas()
{
	deplacer(Sens::Bas);
}

template<class T>
void Game<T>::deplacerGauche()
{
	deplacer(Sens::Gauche);
}

template<class T>
void Game<T>::deplacerDroite()
{
	deplacer(Sens::Droite);
}


template<class T>
bool Game<T>::jeuBloque() const
{
	return false;
}

#endif	/* not GAME_HPP */
