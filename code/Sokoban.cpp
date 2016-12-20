#include "Sokoban.hpp"

ostream& operator<<(ostream& o, CaseSok const& c) {
	switch (c) {
	case CaseSok::vide:
		o << " ";
		break;
	case CaseSok::mur:
		o << "=";
		break;
	case CaseSok::pers:
		o << "*";
		break;
	case CaseSok::caisse:
		o << "x";
		break;
	case CaseSok::but:
		o << "o";
		break;
	case CaseSok::caisse_but:
		o << "ø";
		break;
	case CaseSok::pers_but:
		o << "@";
		break;
	}
	return o;
}

Sokoban::Sokoban(int longueur, int hauteur, int nb_caisses) :
	Jeu<CaseSok>(longueur, hauteur)
{
	if (nb_caisses == -1)
		this->nb_caisses = sqrt(longueur * hauteur) / 2;
	else
		this->nb_caisses = nb_caisses;
	initialiser();
}

Sokoban::~Sokoban() {}

void Sokoban::afficher(ostream& o) const
{

	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < longueur; j++) {
			o << plateau[i][j] << " ";
		}
		o << endl;

	}

	// enlever les ""
	/*
	  o << mur << " : mur" << endl;
	  o << pers << " : personnage (" << pos_h << "," <<
	  pos_l << ")" << endl;
	  o << caisse << " : caisse" << endl;
	  o << but << " : but" << endl;
	  o << caisse_but << " : caisse placée sur un but" << endl;
	*/
}

void Sokoban::initialiser()
{
	//cout << "initialiser()" << endl;
	placer_murs();
	placer_buts_caisses();
	placer_pers();
}

void Sokoban::placer_murs()
{
	//cout <<"placer_murs()" << endl;
	srand(time(nullptr));

	/* Les coins des murs externes ne seront pas forcément au bord
	   du plateau, afin d'obtenir la disposition la plus aléatoire
	   possible */
	i_haut_gauche = rand() % (hauteur / 3);
	j_haut_gauche = rand() % (longueur / 3);

	i_haut_droite = rand() % (hauteur / 3);
	j_haut_droite = longueur - 1 - rand() % (longueur / 3);

	i_bas_gauche = hauteur - 1 - rand() % (hauteur / 3);
	j_bas_gauche = rand() % (hauteur / 3);

	i_bas_droite = hauteur - 1 - rand() % (hauteur / 3);
	j_bas_droite = longueur - 1 - rand() % (hauteur / 3);

	/* Coin haut-gauche : on prolonge le mur jusqu'au bord du
	   plateau */
	for (int i = i_haut_gauche; i >= 0; i--) {
		plateau[i][j_haut_gauche] = CaseSok::mur;
	}
	for (int j = j_haut_gauche; j >= 0; j--) {
		plateau[i_haut_gauche][j] = CaseSok::mur;
	}

	/* Coin haut-droite */
	for (int i = i_haut_droite; i >= 0; i--) {
		plateau[i][j_haut_droite] = CaseSok::mur;
	}
	for (int j = j_haut_droite; j < longueur; j++) {
		plateau[i_haut_droite][j] = CaseSok::mur;
	}

	/* Coin bas-gauche */
	for (int i = i_bas_gauche; i < hauteur; i++) {
		plateau[i][j_bas_gauche] = CaseSok::mur;
	}
	for (int j = j_bas_gauche; j >= 0; j--) {
		plateau[i_bas_gauche][j] = CaseSok::mur;
	}

	/* Coin bas-droite */
	for (int i = i_bas_droite; i < hauteur; i++) {
		plateau[i][j_bas_droite] = CaseSok::mur;
	}
	for (int j = j_bas_droite; j < longueur; j++) {
		plateau[i_bas_droite][j] = CaseSok::mur;
	}
	placerMursExternes();
	placerMursInternes();
}

void Sokoban::placerMursExternes()
{

	/* On termine de placer les murs externes */
	for (int i = i_haut_gauche; i < i_bas_gauche; i++) {
		plateau[i][0] = CaseSok::mur;
	}

	for (int j = j_haut_gauche; j < j_haut_droite; j++) {
		plateau[0][j] = CaseSok::mur;
	}

	for (int j = j_bas_gauche; j < j_bas_droite; j++) {
		plateau[hauteur - 1][j] = CaseSok::mur;
	}

	for (int i = i_haut_droite; i < i_bas_droite; i++) {
		plateau[i][longueur - 1] = CaseSok::mur;
	}

}

void Sokoban::placerMursInternes()
{

	/* On décide aléatoirement si on place des murs internes
	   ou pas*/
	int j_h_mil = (j_haut_gauche + j_haut_droite) / 2;
	int j_b_mil = (j_bas_gauche + j_bas_droite) / 2;
	int i_mil_g = (i_haut_gauche + i_haut_droite) / 2;
	int i_mil_d = (i_haut_droite + i_bas_droite) / 2;

	int lim_h_mil = 1 + rand() % (hauteur / 4);
	int lim_b_mil = 1 + rand() % (hauteur / 4);
	int lim_mil_g = 1 + rand() % (longueur / 4);
	int lim_mil_d = 1 + rand() % (longueur / 4);

	for (int i = 0; i < lim_h_mil; i++)
		plateau[i][j_h_mil] = CaseSok::mur;

	for (int i = hauteur - 1; i > hauteur - 1 - lim_b_mil; i--)
		plateau[i][j_b_mil] = CaseSok::mur;

	for (int j = 0; j < lim_mil_g; j++)
		plateau[i_mil_g][j] = CaseSok::mur;

	for(int j = longueur - 1; j > longueur - 1 -lim_mil_d; j--)
		plateau[i_mil_d][j] = CaseSok::mur;
}

void Sokoban::placer_buts_caisses()
{
	//cout << "placer_buts_caisses()" << endl;
	for (int k = 0; k < nb_caisses; k++) {
		int l_c;
		int h_c;
		/* on place les buts aléatoirement sur le
		   plateau, en vérifiant qu'ils ne soient jamais
		   en dehors des murs */
		do {
			l_c = rand() % longueur;
			h_c = rand() % hauteur;
		} while (plateau[h_c][l_c] != CaseSok::vide ||
			 horsZoneMurs(h_c, l_c));
		plateau[h_c][l_c] = CaseSok::but;

		/* on place autant de caisses que de buts, en
		   vérifiant toujours qu'elles ne soient jamais
		   en dehors des murs.  De plus, pour que la
		   grille soit résolvable, les caisses ne
		   doivent jamais être placées dans une zone
		   entourée de murs. S'il y a un mur
		   devant/derrière et à gauche/à droite, la
		   caisse ne pourra pas être déplacée, et donc
		   le jeu sera bloqué. */
		do {
			l_c = rand() % longueur;
			h_c = rand() % hauteur;
		} while (!zoneLibre(h_c, l_c));
		plateau[h_c][l_c] = CaseSok::caisse;
	}
}

bool Sokoban::zoneLibre(int h_c, int l_c)
{

	if (horsZoneMurs(h_c,l_c))
		return false;
	if (plateau[h_c][l_c] != CaseSok::vide)
		return false;
	if (plateau[h_c + 1][l_c] != CaseSok::vide)
		return false;
	if (plateau[h_c - 1][l_c] != CaseSok::vide)
		return false;
	if (plateau[h_c][l_c - 1] != CaseSok::vide)
		return false;
	if (plateau[h_c][l_c + 1] != CaseSok::vide)
		return false;

	return true;
}

bool Sokoban::horsZoneMurs(int h_c, int l_c)
{
	if (h_c >= hauteur - 2 || h_c <= 1)
		return true;
	if (l_c >= longueur - 2 || l_c <= 1)
		return true;

	if (h_c <= i_haut_gauche && l_c <= j_haut_gauche)
		return true;
	if (h_c >= i_bas_gauche && l_c <= j_bas_gauche)
		return true;
	if (h_c <= i_haut_droite && l_c >= j_haut_droite)
		return true;
	if (h_c >= i_bas_droite && l_c >= j_bas_droite)
		return true;

	return false;
}

void Sokoban::placer_pers()
{
	//cout << "placer_pers()" << endl;
	do {
		pos_l = 1 + rand() % (longueur - 2);
		pos_h = 1 + rand() % (hauteur - 2);
	}

	/* pour que le personnage puisse effectuer au moins un
	   mouvement, on le place dans une case entourée
	   uniquement de cases vides, toujours à l'intérieur de
	   la zone délimitée par les murs externes */
	while (!zoneLibre(pos_h, pos_l));
	plateau[pos_h][pos_l] = CaseSok::pers;
}

void Sokoban::deplacer(Sens s)
{

	int new_pos_h = pos_h;
	int new_pos_l = pos_l;
	int sens_h = 0;
	int sens_l = 0;

	CaseSok& source = plateau[pos_h][pos_l];
	switch(s) {
	case Sens::Haut:
		new_pos_h -= 1;
		sens_h = -1;
		break;
	case Sens::Bas:
		new_pos_h += 1;
		sens_h = 1;
		break;
	case Sens::Gauche:
		new_pos_l -= 1;
		sens_l = -1;
		break;
	case Sens::Droite:
		new_pos_l += 1;
		sens_l = 1;
		break;
	default:
		break;
	}

	CaseSok& dest = plateau[new_pos_h][new_pos_l];
	CaseSok& derriere =
		plateau[new_pos_h + sens_h][new_pos_l + sens_l];

	/* si la case juste au-dessus est vide, le personnage
	   peut s'y déplacer sans condition */

	if (dest == CaseSok::vide || dest == CaseSok::but) {
		dest = (dest == CaseSok::vide) ?
			CaseSok::pers : CaseSok::pers_but;
		if (source == CaseSok::pers)
			source = CaseSok::vide;
		else if (source == CaseSok::pers_but)
			source = CaseSok::but;
		pos_h = new_pos_h;
		pos_l = new_pos_l;
		score++;
	}

	/* si la case juste au-dessus contient une caisse,
	   elle ne peut être poussée que si la case située derrière
	   est vide ou contient un but */

	else if (dest == CaseSok::caisse) {

		/* déplacement d'une caisse sur une case caseVide */

		if (derriere == CaseSok::vide) {
			derriere = CaseSok::caisse;
			dest = CaseSok::pers;
			if (source == CaseSok::pers)
				source = CaseSok::vide;
			else if (source == CaseSok::pers_but)
				source = CaseSok::but;
			pos_h = new_pos_h;
			pos_l = new_pos_l;
			score++;
		} else if (derriere == CaseSok::but) {

			/* déplacement d'une caisse sur un but */

			derriere = CaseSok::caisse_but;
			dest = CaseSok::pers;
			if (source == CaseSok::pers)
				source = CaseSok::vide;
			else if (source == CaseSok::pers_but)
				source = CaseSok::but;
			pos_h = new_pos_h;
			pos_l = new_pos_l;
			score++;
		}
	}

	/* si la case du dessus contient un but occupé
	   par une caisse, cette dernière peut être poussée
	   s'il y a un autre but ou une case vide derrière
	*/

	else if (dest == CaseSok::caisse_but) {

		/* d'un but vers un autre */

		if (derriere == CaseSok::but) {
			derriere = CaseSok::caisse_but;
			dest = CaseSok::pers_but;
			if (source == CaseSok::pers)
				source = CaseSok::vide;
			else if (source == CaseSok::pers_but)
				source = CaseSok::but;
			pos_h = new_pos_h;
			pos_l = new_pos_l;
			score++;
		}

		/* d'un but vers une case vide */

		else if (derriere == CaseSok::vide) {
			derriere = CaseSok::caisse;
			dest = CaseSok::pers_but;
			if (source == CaseSok::pers)
				source = CaseSok::vide;
			else if (source == CaseSok::pers_but)
				source = CaseSok::but;
			pos_h = new_pos_h;
			pos_l = new_pos_l;
			score++;
		}
	}

}

bool Sokoban::jeuTermine() const
{
	if (jeuBloque())
		return true;
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < longueur; j++) {
			if (plateau[i][j] == CaseSok::but ||
			    plateau[i][j] == CaseSok::caisse)
				return false;
		}
	}
	return true;
}

bool Sokoban::jeuBloque() const
{
	/* un bloquage peut survenir lorsqu'une caisse ne peut
	   plus être déplacée, c'est à dire lorsqu'il y a un mur
	   derrière et sur l'un des côtés (gauche/droite)
	*/
	for (int i = 1; i < hauteur - 1; i++) {
		for (int j = 1; j < longueur - 1; j++) {
			if (plateau[i][j] == CaseSok::caisse &&
			    (plateau[i - 1][j] == CaseSok::mur ||
			     plateau[i + 1][j] == CaseSok::mur) &&
			    (plateau[i][j - 1] == CaseSok::mur ||
			     plateau[i][j + 1] == CaseSok::mur)) {
				return true;
			}
		}
	}
	return false;
}
