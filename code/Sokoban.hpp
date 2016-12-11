#ifndef SOKOBAN
#define SOKOBAN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>

enum class CaseSok{vide,mur,pers,caisse,but,caisse_but};

ostream& operator<<(ostream&, CaseSok const&);

template<int l, int h>
class Sokoban : public Jeu<CaseSok,l,h> {
protected:
  int pos_h;
  int pos_l;
  virtual void afficher(ostream& o=cout) const {
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	o << (*this)[i][j] << " ";
      }
      o << endl;
    }
  }
  virtual void initialiser() {
    srand(time(nullptr));

    (*this)[pos_h][pos_l]=CaseSok::pers;
    int i_haut_gauche=rand()%(h/3);
    int j_haut_gauche=rand()%(l/3);
    
    int i_haut_droite=rand()%(h/3);
    int j_haut_droite=l-1-rand()%(l/3);

    int i_bas_gauche=h-1-rand()%(h/3);
    int j_bas_gauche=rand()%(h/3);

    int i_bas_droite=h-1-rand()%(h/3);
    int j_bas_droite=l-1-rand()%(h/3);

    for (int i(i_haut_gauche); i>=0; i--) {
      (*this)[i][j_haut_gauche]=CaseSok::mur;
    }
    for (int j(j_haut_gauche); j>=0; j--) {
      (*this)[i_haut_gauche][j]=CaseSok::mur;
    }
    for (int i(i_haut_droite); i>=0; i--) {
      (*this)[i][j_haut_droite]=CaseSok::mur;
    }
    for (int j(j_haut_droite); j<l; j++) {
      (*this)[i_haut_droite][j]=CaseSok::mur;
    }
    for (int i(i_bas_gauche); i<h; i++) {
      (*this)[i][j_bas_gauche]=CaseSok::mur;
    }
    for (int j(j_bas_gauche); j>=0; j--) {
      (*this)[i_bas_gauche][j]=CaseSok::mur;
    }
    for (int i(i_bas_droite); i<h; i++) {
      (*this)[i][j_bas_droite]=CaseSok::mur;
    }
    for (int j(j_bas_droite); j<l; j++) {
      (*this)[i_bas_droite][j]=CaseSok::mur;
    }

    for (int i(i_haut_gauche); i<i_bas_gauche; i++) {
      (*this)[i][0]=CaseSok::mur;
    }

    for (int j(j_haut_gauche); j<j_haut_droite; j++) {
      (*this)[0][j]=CaseSok::mur;
    }
    
    for (int j(j_bas_gauche); j<j_bas_droite; j++) {
      (*this)[h-1][j]=CaseSok::mur;
    }

    for (int i(i_haut_droite); i<(i_bas_droite); i++) {
      (*this)[i][l-1]=CaseSok::mur;
    }

    if (i_haut_gauche >1) {
      int r=1+rand()%(l/4);
      for (int j(j_haut_gauche); j<j_haut_gauche+r; j++) {
	(*this)[i_haut_gauche][j]=CaseSok::mur;
      }
    }
    if (j_haut_gauche > 1) {
      int r=rand()%(h/3);
      for (int i(i_haut_gauche); i<i_haut_gauche+r; i++) {
	(*this)[i][j_haut_gauche]=CaseSok::mur;
      }
    }

    if (i_haut_droite >1) {
      int r=rand()%(l/3);
      for (int j(j_haut_droite); j<j_haut_droite-r; j--) {
	(*this)[i_haut_droite][j]=CaseSok::mur;
      }
    }
    if (j_haut_droite < l-2) {
      int r=rand()%(h/3);
      for (int i(i_haut_droite); i<i_haut_droite+r; i++) {
	(*this)[i][j_haut_droite]=CaseSok::mur;
      }
    }

    if (i_bas_gauche <h-2) {
      int r=rand()%(l/3);
      for (int j(j_bas_gauche); j<j_bas_gauche+r; j++) {
	(*this)[i_bas_gauche][j]=CaseSok::mur;
      }
    }
    if (j_bas_gauche >1) {
      int r=rand()%(h/3);
      for (int i(i_bas_gauche); i>i_bas_gauche-r; i--) {
	(*this)[i][j_bas_gauche]=CaseSok::mur;
      }
    }

    if (i_bas_droite <h-2) {
      int r=rand()%(l/3);
      for (int j(j_bas_droite); j>j_bas_droite-r; j--) {
	(*this)[i_bas_droite][j]=CaseSok::mur;
      }
    }
    if (j_bas_droite <l-2) {
      int r=rand()%(h/3);
      for (int i(i_bas_droite); i>i_bas_droite-r; i--) {
	(*this)[i][j_bas_droite]=CaseSok::mur;
      }
    }
    

  }
  virtual void deplacerHaut() {}
  virtual void deplacerBas() {}
  virtual void deplacerGauche() {}
  virtual void deplacerDroite(){}
  virtual bool jeuTermine() const {return false;}
public:
  Sokoban() :
    Jeu<CaseSok,l,h>()
  { pos_l=l/2;
    pos_h=h/2;
    initialiser();}
};

#endif
