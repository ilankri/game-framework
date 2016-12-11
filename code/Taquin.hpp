#ifndef TAQUIN
#define TAQUIN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>


template<int l, int h>
class Taquin : public Jeu<int,l,h> {
protected:
  //coordonnées de la case vide
  int pos_vide_l;
  int pos_vide_h;
  
  virtual void afficher(ostream& o) const {
    for (int j(0); j<9*l-(l-2); j++) o << "-"; //longueur d'une ligne, en tenant compte des tabulations
    o << endl;
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	o << "| ";
	if (this->plateau[i][j]==Jeu<int,l,h>::caseVide) o << " ";
	else o<< this->plateau[i][j];
	o << "\t";
      }
      o << " |" << endl;
      for (int j(0); j<9*l-(l-2); j++) o << "-";
      o <<endl;
    }
  }

  //virtual bool bienTriePartiel() const;
public:
  Taquin() : Jeu<int, l, h>() {initialiser();}
  virtual ~Taquin() {}
  virtual void initialiser() {
    //reste à gérer les grilles impossibles à réordonner :
    // (case vide paire + permutation impaire)
    // ou (case vide impaire + permutation paire)
    srand(time(nullptr));
    int tmp=1;
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
    if ((*this)[i1][j1]==Jeu<int,l,h>::caseVide) {
      pos_vide_h=i1;
      pos_vide_l=j1;
    }
    else if ((*this)[i2][j2]==Jeu<int,l,h>::caseVide) {
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
    if ((*this)[h-1][l-1] != Jeu<int,l,h>::caseVide) {
      return false;
    }
    int tmp=1;
    for (int i(0); i<h-1; i++) {
      for (int j(0); j<l; j++) {
	if ((*this)[i][j] != (tmp++)) {
	  return false;
	}
      }
    }
    for (int j(0) ;j< l-1; j++) {
      if ((*this)[h-1][j] != (tmp++)) {
	return false;
      }
    }
    return true;
  }

  virtual void deplacerHaut() {
    if (pos_vide_h >0) {
      int tmp=(*this)[pos_vide_h][pos_vide_l];
      (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h-1][pos_vide_l];
      (*this)[--pos_vide_h][pos_vide_l]=tmp; //mettre à jour les coordonnées de la case vide
      this->score++;
    }
  }
  
  virtual void deplacerBas() {
    if (pos_vide_h < h-1) {
      int tmp=(*this)[pos_vide_h][pos_vide_l];
      (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h+1][pos_vide_l];
      (*this)[++pos_vide_h][pos_vide_l]=tmp; //mettre à jour les coordonnées de la case vide
      this->score++;
    }
  }

  virtual void deplacerGauche() {
    if (pos_vide_l >0) {
      int tmp=(*this)[pos_vide_h][pos_vide_l];
      (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h][pos_vide_l-1];
      (*this)[pos_vide_h][--pos_vide_l]=tmp; // mettre à jour les coordonnées de la case vide
      this->score++;
    }
  }

  virtual void deplacerDroite() {
    if (pos_vide_l <l-1) {
      int tmp=(*this)[pos_vide_h][pos_vide_l];
      (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h][pos_vide_l+1];
      (*this)[pos_vide_h][++pos_vide_l]=tmp; // mettre à jour les coordonnées de la case vide
      this->score++;
    }
  }

};

#endif
