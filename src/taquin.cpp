#include "taquin.hpp"

Taquin::Taquin(int l, int h) : Game<int>(l, h)
{
	initialiser();
}

Taquin::~Taquin() {}

void Taquin::initialiser()
{
	remplir();
	melanger();
}

void Taquin::remplir()
{
	int tmp = 1;

	srand(time(nullptr));
	// On remplit les cases.
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < longueur; j++) {
			plateau[i][j] = tmp++;
		}
	}
	plateau[hauteur - 1][longueur - 1] = 0;
	pos_vide_h = hauteur - 1;
	pos_vide_l = longueur - 1;

}

void Taquin::melanger()
{
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

	int board_size = longueur * hauteur;

	for (int k = 0; k < board_size; k++) {
		i1 = rand() % hauteur;
		j1 = rand() % longueur;

		do {
			i2 = rand() % hauteur;
			j2 = rand() % longueur;
		} while (i1 == i2 && j1 == j2);

		int tmp = plateau[i1][j1];
		plateau[i1][j1] = plateau[i2][j2];
		plateau[i2][j2] = tmp;
		perm_paire = !perm_paire;

		// On met à jour les coordonnées de la case vide.
		if (plateau[i1][j1] == caseVide) {
			pos_vide_h = i1;
			pos_vide_l = j1;
		} else if (plateau[i2][j2] == caseVide) {
			pos_vide_h = i2;
			pos_vide_l = j2;
		}
		case_vide_paire = ((longueur - 1 - pos_vide_l) +
				   (hauteur - 1 - pos_vide_h)) % 2 == 0;
	}

	/*
	 * Pour que la grille soit résolvable, il faut que la
	 * permutation soit de même parité que la case vide.
	 */
	if (case_vide_paire ^ perm_paire) {
		do {
			i1 = rand() % hauteur;
			j1 = rand() % longueur;
		} while (i1 == pos_vide_h && j1 == pos_vide_l);
		do {
			i2 = rand() % hauteur;
			j2 = rand() % longueur;
		} while ((i2 == pos_vide_h && j2 == pos_vide_l) ||
			 (i2 == i1 && j2 == j1));
		int tmp = plateau[i1][j1];
		plateau[i1][j1] = plateau[i2][j2];
		plateau[i2][j2] = tmp;
	}
}

bool Taquin::jeuTermine() const
{
	if (plateau[hauteur - 1][longueur - 1] != caseVide) {
		return false;
	}

	for (int j = 1; j < longueur; j++) {
		// On teste si la première ligne est triée.
		if (plateau[0][j] < plateau[0][j-1])
			return false;
	}
	for (int i = 1; i < hauteur - 1; i++) {
		/*
		 * À partir de la 2e ligne, on regarde d'abord si la 1re
		 * case est supérieure à la dernière de la ligne
		 * précédente.
		 */
		if (plateau[i][0] < plateau[i - 1][longueur - 1])
			return false;
		for (int j = 1; j < longueur; j++) {
			// On teste ensuite si la ligne i est triée.
			if (plateau[i][j] < plateau[i][j - 1])
				return false;
		}
	}

	if (plateau[hauteur - 1][0] < plateau[hauteur - 2][longueur - 1])
		return false;
	for (int j = 1; j < longueur - 1; j++) {
		/*
		 * On teste si la dernière ligne est triée (sans tenir
		 * compte de la dernière case, qui doit être vide.
		 */
		if (plateau[hauteur - 1][j] < plateau[hauteur - 1][j - 1])
			return false;
	}

	return true;
}

void Taquin::deplacer(Sens s)
{
	int sens_l = 0;
	int sens_h = 0;

	switch (s) {
	case Sens::Haut:
		sens_h = (pos_vide_h > 0) ? -1 : 0;
		break;
	case Sens::Bas:
		sens_h = (pos_vide_h < hauteur - 1) ? 1 : 0;
		break;
	case Sens::Gauche:
		sens_l = (pos_vide_l > 0) ? -1 : 0;
		break;
	case Sens::Droite:
		sens_l = (pos_vide_l < longueur - 1) ? 1 : 0;
		break;
	default:
		break;
	}

	int& source = plateau[pos_vide_h][pos_vide_l];
	int& dest = plateau[pos_vide_h + sens_h][pos_vide_l + sens_l];

	if (sens_h != 0 || sens_l != 0) {
		int tmp = source;
		source = dest;
		dest = tmp;
		pos_vide_h += sens_h;
		pos_vide_l += sens_l;
		score++;
	}
}
