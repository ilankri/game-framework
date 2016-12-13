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
  int i_haut_gauche, j_haut_gauche;
  int i_haut_droite, j_haut_droite;
  int i_bas_gauche, j_bas_gauche;
  int i_bas_droite, j_bas_droite;
  virtual void afficher(ostream& o=cout) const {
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	o << (*this)[i][j] << " ";
      }
      o << endl;

    }

    o << CaseSok::mur << " : mur" << endl;
    o << CaseSok::pers << " : personnage" << endl;
    o << CaseSok::caisse << " : caisse" << endl;
    o << CaseSok::but << " : but" << endl;
    o << CaseSok::caisse_but << " : caisse_but" << endl;
  }
  virtual void initialiser() {
    //cout << "initialiser()" << endl;
    placer_murs();
    placer_buts_caisses();
    placer_pers();
  }
  virtual void placer_murs() {
    //cout <<"placer_murs()" << endl;
    srand(time(nullptr));


    /* Les coins des murs externes ne seront pas forcément au bord 
       du plateau, afin d'obtenir la disposition la plus aléatoire 
       possible */
    i_haut_gauche=rand()%(h/3);
    j_haut_gauche=rand()%(l/3);
    
    i_haut_droite=rand()%(h/3);
    j_haut_droite=l-1-rand()%(l/3);

    i_bas_gauche=h-1-rand()%(h/3);
    j_bas_gauche=rand()%(h/3);

    i_bas_droite=h-1-rand()%(h/3);
    j_bas_droite=l-1-rand()%(h/3);

    /* Coin haut-gauche : on prolonge le mur jusqu'au bord du
       plateau */
    for (int i(i_haut_gauche); i>=0; i--) {
      (*this)[i][j_haut_gauche]=CaseSok::mur;
    }
    for (int j(j_haut_gauche); j>=0; j--) {
      (*this)[i_haut_gauche][j]=CaseSok::mur;
    }

    /* Coin haut-droite */
    for (int i(i_haut_droite); i>=0; i--) {
      (*this)[i][j_haut_droite]=CaseSok::mur;
    }
    for (int j(j_haut_droite); j<l; j++) {
      (*this)[i_haut_droite][j]=CaseSok::mur;
    }

    /* Coin bas-hauche */
    for (int i(i_bas_gauche); i<h; i++) {
      (*this)[i][j_bas_gauche]=CaseSok::mur;
    }
    for (int j(j_bas_gauche); j>=0; j--) {
      (*this)[i_bas_gauche][j]=CaseSok::mur;
    }

    /* Coin bas-droite */
    for (int i(i_bas_droite); i<h; i++) {
      (*this)[i][j_bas_droite]=CaseSok::mur;
    }
    for (int j(j_bas_droite); j<l; j++) {
      (*this)[i_bas_droite][j]=CaseSok::mur;
    }

    /* On termine de placer les murs externes */
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


    /* On décide aléatoirement si on prolonge chaque coin vers
       l'intérieur ou pas */
    if (i_haut_gauche >1) {
      int r=1+rand()%(l/3);
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
  
  virtual void placer_buts_caisses() {
    //cout << "placer_buts_caisses()" << endl;
    for (int k(0); k<4; k++) {
      int l_c,h_c;
      /* on place les buts aléatoirement sur le plateau, en
	 vérifiant qu'ils ne soient jamais en dehors des murs */
      do {
	l_c=rand()%l;
	h_c=rand()%h;
      }
      while ((*this)[h_c][l_c] != CaseSok::vide||
	     (h_c <= i_haut_gauche && l_c <= j_haut_gauche)
	     ||(h_c >= i_bas_gauche && l_c <= j_bas_gauche)
	     ||(h_c <= i_haut_droite && l_c >= j_haut_droite)
	     ||(h_c >= i_bas_droite && l_c >= j_bas_droite));
      (*this)[h_c][l_c]=CaseSok::but;
      
      
      /* on place autant de caisses que de buts, en vérifiant
	 toujours qu'elles ne soient jamais en dehors des murs.
	 De plus, pour que la grille soit résolvable, les caisses
	 ne doivent jamais être placées dans une zone entourée de 
	 murs. S'il y a un mur devant/derrière et à gauche/à droite,
	 la caisse ne pourra pas être déplacée, et donc le jeu sera
	 bloqué. */
      do {
	l_c=rand()%l;
	h_c=rand()%h;
      }
      while ((*this)[h_c][l_c] != CaseSok::vide||
	     (h_c >=h-2 || h_c <=1 || l_c >=l-2 || l_c<=1)
	     ||(h_c <= i_haut_gauche && l_c <= j_haut_gauche)
	     ||(h_c >= i_bas_gauche && l_c <= j_bas_gauche)
	     ||(h_c <= i_haut_droite && l_c >= j_haut_droite)
	     ||(h_c >= i_bas_droite && l_c >= j_bas_droite)
	     ||(*this)[h_c-1][l_c] != CaseSok::vide
	     ||(*this)[h_c][l_c-1] != CaseSok::vide
	     ||(*this)[h_c][l_c+1] != CaseSok::vide
	     ||(*this)[h_c+1][l_c] != CaseSok::vide);
      (*this)[h_c][l_c]=CaseSok::caisse;
    }
  }

  virtual void placer_pers() {
    //cout << "placer_pers()" << endl;
    do {
      pos_l=1+rand()%(l-2);
      pos_h=1+rand()%(h-2);
    }

    /* pour que le personnage puisse effectuer au moins un
       mouvement, on le place dans une case entourée uniquement
       de case vide, toujours à l'intérieur de la zone délimitée
       par les  murs externes */
    while ((pos_h <= i_haut_gauche && pos_l <=j_haut_gauche)
	   ||(pos_h >= i_bas_gauche && pos_l <= j_bas_gauche)
	   ||(pos_h <= i_haut_droite && pos_l >= j_haut_droite)
	   ||(pos_h >= i_bas_droite && pos_l >= j_bas_droite)
	   ||(*this)[pos_h-1][pos_l] != CaseSok::vide
	   ||(*this)[pos_h][pos_l-1] !=CaseSok::vide
	   ||(*this)[pos_h][pos_l] != CaseSok::vide
	   ||(*this)[pos_h][pos_l+1] != CaseSok::vide
	   ||(*this)[pos_h+1][pos_l] != CaseSok::vide);
    (*this)[pos_h][pos_l]=CaseSok::pers;
  }

  virtual void deplacerHaut() {
    long & score=this->score;
    if ((*this)[pos_h-1][pos_l]==CaseSok::vide) {
      (*this)[pos_h-1][pos_l]=CaseSok::pers;
      (*this)[pos_h--][pos_l]=CaseSok::vide;
      score++;
    }
    else if ((*this)[pos_h-1][pos_l]==CaseSok::caisse) {
      if ((*this)[pos_h-2][pos_l]==CaseSok::vide) {
	(*this)[pos_h-2][pos_l]=CaseSok::caisse;
	(*this)[pos_h-1][pos_l]=CaseSok::pers;
	(*this)[pos_h--][pos_l]=CaseSok::vide;
	score++;
      }
      else if ((*this)[pos_h-2][pos_l]==CaseSok::but) {
	(*this)[pos_h-2][pos_l]=CaseSok::caisse_but;
	(*this)[pos_h-1][pos_l]=CaseSok::pers;
	(*this)[pos_h--][pos_l]=CaseSok::vide;
	score+=2;
      }
    }
  }
  
  virtual void deplacerBas() {
    long & score=this->score;
    if ((*this)[pos_h+1][pos_l]==CaseSok::vide) {
      (*this)[pos_h+1][pos_l]=CaseSok::pers;
      (*this)[pos_h++][pos_l]=CaseSok::vide;
      score++;
    }
    else if ((*this)[pos_h+1][pos_l]==CaseSok::caisse) {
      if ((*this)[pos_h+2][pos_l]==CaseSok::vide) {
	(*this)[pos_h+2][pos_l]=CaseSok::caisse;
	(*this)[pos_h+1][pos_l]=CaseSok::pers;
	(*this)[pos_h++][pos_l]=CaseSok::vide;
	score++;
      }
      else if ((*this)[pos_h+2][pos_l]==CaseSok::but) {
	(*this)[pos_h+2][pos_l]=CaseSok::caisse_but;
	(*this)[pos_h+1][pos_l]=CaseSok::pers;
	(*this)[pos_h++][pos_l]=CaseSok::vide;
	score+=2;
      }
    }
  }
  
  virtual void deplacerGauche() {
    long & score=this->score;
    if ((*this)[pos_h][pos_l-1]==CaseSok::vide) {
      (*this)[pos_h][pos_l-1]=CaseSok::pers;
      (*this)[pos_h][pos_l--]=CaseSok::vide;
      score++;
    }
    else if ((*this)[pos_h][pos_l-1]==CaseSok::caisse) {
      if ((*this)[pos_h][pos_l-2]==CaseSok::vide) {
	(*this)[pos_h][pos_l-2]=CaseSok::caisse;
	(*this)[pos_h][pos_l-1]=CaseSok::pers;
	(*this)[pos_h][pos_l--]=CaseSok::vide;
	score++;
      }
      if ((*this)[pos_h][pos_l-2]==CaseSok::but) {
	(*this)[pos_h][pos_l-2]=CaseSok::caisse_but;
	(*this)[pos_h][pos_l-1]=CaseSok::pers;
	(*this)[pos_h][pos_l--]=CaseSok::vide;
	score+=2;
      }
    }
  }
  
  virtual void deplacerDroite(){
    long & score=this->score;
    if ((*this)[pos_h][pos_l+1]==CaseSok::vide) {
      (*this)[pos_h][pos_l+1]=CaseSok::pers;
      (*this)[pos_h][pos_l++]=CaseSok::vide;
      score++;
    }
    else if ((*this)[pos_h][pos_l+1]==CaseSok::caisse) {
      if ((*this)[pos_h][pos_l+2]==CaseSok::vide) {
	(*this)[pos_h][pos_l+2]=CaseSok::caisse;
	(*this)[pos_h][pos_l+1]=CaseSok::pers;
	(*this)[pos_h][pos_l++]=CaseSok::vide;
	score++;
      }
      else if ((*this)[pos_h][pos_l+2]==CaseSok::but) {
	(*this)[pos_h][pos_l+2]=CaseSok::caisse_but;
	(*this)[pos_h][pos_l+1]=CaseSok::pers;
	(*this)[pos_h][pos_l++]=CaseSok::vide;
	score+=2;
      }
    }
  }
  
  virtual bool jeuTermine() const {
    if (jeuBloque()) return true;
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	if ((*this)[i][j]==CaseSok::but
	    ||(*this)[i][j]==CaseSok::caisse)
	  return false;
      }
    }
    return true;
  }

  virtual bool jeuBloque() const {
    /* un bloquage peut survenir lorsqu'une caisse ne peut plus être
       déplacée, c'est à dire lorsqu'il y a un mur devant et sur l'un
       des côtés (gauche/droite)
    */
    for (int i(1); i<h-1; i++) {
      for (int j(1); j<l-1; j++) {
	if ((*this)[i][j]==CaseSok::caisse
	    && ((*this)[i-1][j]==CaseSok::mur
		||(*this)[i+1][j]==CaseSok::mur)
	    && ((*this)[i][j-1]==CaseSok::mur
		||(*this)[i][j+1]==CaseSok::mur)) {
	  return true;
	}
      }
    }
    return false;
  }
public:
  Sokoban() :
    Jeu<CaseSok,l,h>()
  { initialiser();}
};

#endif
