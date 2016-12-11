#ifndef SOKOBAN
#define SOKOBAN

#include "Jeu.hpp"


enum class CaseSok{vide,mur,caisse,but};

template<int l, int h>
class Sokoban : public Jeu<CaseSok,l,h> {
protected:
  int pos_x;
  int pos_y;
  virtual void afficher(ostream& o=cout) const {
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	o <<"";
      }
    }
  }
  virtual void initialiser() {
    for (int i(0); i<h; i++) {
      (*this)[0][i]=CaseSok::mur;
      (*this)[i][0]=CaseSok::mur;
      (*this)[h-1][i]=CaseSok::mur;
      (*this)[i][l-1]=CaseSok::mur;
    }
  }
  virtual void deplacerHaut() {}
  virtual void deplacerBas() {}
  virtual void deplacerGauche() {}
  virtual void deplacerDroite(){}
  virtual bool jeuTermine() const {return false;}
public:
  Sokoban() : Jeu<CaseSok,l,h>() {}
};

#endif
