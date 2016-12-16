#ifndef TAQUIN
#define TAQUIN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>


template<class C>
class Taquin : public Jeu<C> {

protected:
  //coordonnées de la case vide
  int pos_vide_l;
  int pos_vide_h;

  //virtual bool bienTriePartiel() const;
public:
  Taquin(int l, int h) : Jeu<C>(l,h) {initialiser();}
  virtual ~Taquin() {}
  virtual void initialiser() {
    const int &h = this->hauteur;
    const int &l = this->longueur;
    //reste à gérer les grilles impossibles à réordonner :
    // (case vide paire + permutation impaire)
    // ou (case vide impaire + permutation paire)
    srand(time(nullptr));
    C tmp=(C) 1;
    //on remplit les cases
    for (int i(0); i<h-1; i++) {
      for (int j(0); j<l; j++) {
	(*this)[i][j]=tmp++;
      }
    }
    for (int j(0); j<l-1; j++) {
      (*this)[h-1][j]=tmp++;
    }
    (*this)[h-1][l-1]=0;
    this->pos_vide_h=h-1;
    this->pos_vide_l=l-1;
    
    bool perm_paire=true; // la parité d'une permutation est celle du nombre d'échanges successifs qu'il faut faire pour obtenir la grille finale
    bool case_vide_paire=false; // la parité de la case vide est celle du nombre de déplacements à effectuer pour la mettre en bas à droite
    
    // on mélange les cases
    int i1(0), j1(0), i2(0), j2(0);
    
    
    for (int k(0); k<l*h; k++) {
      i1=rand()%h;
      j1=rand()%l;
    do {
      i2=rand()%h;
      j2=rand()%l;
    }
    while (i1==i2 && j1==j2);
    int tmp=(*this)[i1][j1];
    (*this)[i1][j1]=(*this)[i2][j2];
    (*this)[i2][j2]=tmp;
    perm_paire=!perm_paire;
    
    //on met à jour les coordonnées de la case vide
    if ((*this)[i1][j1]==Jeu<C>::caseVide) {
      pos_vide_h=i1;
      pos_vide_l=j1;
    }
    else if ((*this)[i2][j2]==Jeu<C>::caseVide) {
      pos_vide_h=i2;
      pos_vide_l=j2;
    }
    case_vide_paire=((l-1-pos_vide_l)+(h-1-pos_vide_h))%2==0;
    }
    
    /*pour que la grille soit résolvable, il faut que 
      la permutation soit de même parité que la case vide */
      if (case_vide_paire ^ perm_paire) {
      do {
	i1=rand()%h;
	j1=rand()%l;
      }
      while (i1==this->pos_vide_h && j1==this->pos_vide_l);
      do {
	i2=rand()%h;
	j2=rand()%l;
      }
      while ((i2==this->pos_vide_h && j2==this->pos_vide_l)
	     ||(i2==i1 && j2==j1));
      tmp=(*this)[i1][j1];
      (*this)[i1][j1]=(*this)[i2][j2];
      (*this)[i2][j2]=tmp;
      
    }
  }

  virtual bool jeuTermine() const {

    const int &l=this->longueur, &h=this->hauteur;

    if ((*this)[h-1][l-1] != Jeu<C>::caseVide) {
      return false;
    }
    
    for (int j(1); j<l; j++) {
      //on teste si la première ligne est triée
      if ((*this)[0][j] < (*this)[0][j-1]) return false;
    }
    for (int i(1); i<h-1; i++) {
      /* à partir de la 2e ligne, on regarde d'abord si la
	 1re case est supérieure à la dernière de la ligne
	 précédente */
      if ((*this)[i][0] < (*this)[i-1][l-1]) return false;
      for (int j(1); j<l; j++) {

	// on teste ensuite si la ligne i est triée
	if ((*this)[i][j] < (*this)[i][j-1]) return false;
      }
    }

    if ((*this)[h-1][0] < (*this)[h-2][l-1]) return false;
    for (int j(1); j<l-1; j++) {
      /* on teste si la dernière ligne est triée (sans tenir
	 compte de la dernière case, qui doit être vide */
      if ((*this)[h-1][j] < (*this)[h-1][j-1]) return false;
    }

    
    return true;
  }

  virtual void deplacer(Sens s) {
    int sens_l= 0;
    int sens_h=0;

    const int &h=this->hauteur, &l=this->longueur;
    
    switch(s) {
    case Sens::Haut:
      sens_h= pos_vide_h> 0 ? -1 :0;
      break;
    case Sens::Bas:
      sens_h= pos_vide_h < h-1 ? 1 : 0;
      break;
    case Sens::Gauche:
      sens_l= pos_vide_l > 0 ? -1 : 0;
      break;
    case Sens::Droite:
      sens_l= pos_vide_l < l-1 ? 1 : 0;
      break;
    default:
      break;
    }

    C & source=(*this)[pos_vide_h][pos_vide_l];
    C & dest=(*this)[pos_vide_h+sens_h][pos_vide_l+sens_l];

    if (sens_h !=0 || sens_l !=0) {
      C tmp=source;
      source=dest;
      dest=tmp;
      pos_vide_h+=sens_h;
      pos_vide_l+=sens_l;
      this->score++;
    }
  }

};

#endif
