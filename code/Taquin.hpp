#ifndef TAQUIN
#define TAQUIN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>


class Taquin : public Jeu<int> {
public:
	Taquin(int l, int h);

	virtual ~Taquin();

private:
	static const int caseVide = 0;

	//coordonnées de la case vide
	int pos_vide_l;

	int pos_vide_h;

	//virtual bool bienTriePartiel() const;

	virtual void initialiser();

	virtual bool jeuTermine() const;

	virtual void deplacer(Sens s);

	void remplir();

	void melanger();
};

#endif
