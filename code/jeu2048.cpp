#include "jeu2048.hpp"

Jeu2048::Jeu2048(int l, int h) : Jeu<Square2048>(l, h)
{
	initialiser();
}

void Jeu2048::initialiser()
{
	srand(time(nullptr));
	const int& l=this->longueur;
	const int& h=this->hauteur;
	int pos_h1=rand()%h;
	int pos_l1=rand()%l;
	int pos_h2, pos_l2;
	do {
		pos_h2=rand()%h;
		pos_l2=rand()%l;
	}
	while (pos_h2 == pos_h1 && pos_l2 == pos_l1);
	(*this)[pos_h1][pos_l1]=(C) ((1+rand()%2)*2);
	(*this)[pos_h2][pos_l2]=(C) ((1+rand()%2)*2);
}

bool Jeu2048::jeuTermine() const
{
	return false;
}

void Jeu2048::deplacer(Sens sens)
{
	switch (sens) {
	case Sens::Bas:
		break;
	case Sens::Haut:
		break;
	case Sens::Gauche:
		break;
	case Sens::Droite:
		break;
	default:
		break;
	}
}
