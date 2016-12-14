#ifndef SOKOBAN
#define SOKOBAN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>

enum class CaseSok{vide,mur,pers,caisse,but,caisse_but};

ostream& operator<<(ostream&, CaseSok const&);

template <class C>
class Sokoban : public Jeu<CaseSok> {
private:
  const int &l=longueur, &h=hauteur;
protected:
  int pos_h;
  int pos_l;
  int i_haut_gauche, j_haut_gauche;
  int i_haut_droite, j_haut_droite;
  int i_bas_gauche, j_bas_gauche;
  int i_bas_droite, j_bas_droite;
  static const C mur=(C) 1;
  static const C pers=(C) 2;
  static const C caisse=(C) 3;
  static const C but=(C) 4;
  static const C caisse_but=(C) 5;

  
  virtual void afficher(ostream& o=cout) const {
    
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	o << (*this)[i][j] << " ";
      }
      o << endl;

    }

    // enlever les ""
    /*
    o << mur << " : mur" << endl;
    o << pers << " : personnage (" << pos_h << "," << pos_l << ")" << endl;
    o << caisse << " : caisse" << endl;
    o << but << " : but" << endl;
    o << caisse_but << " : caisse placée sur un but" << endl;
    */
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
      (*this)[i][j_haut_gauche]=mur;
    }
    for (int j(j_haut_gauche); j>=0; j--) {
      (*this)[i_haut_gauche][j]=mur;
    }

    /* Coin haut-droite */
    for (int i(i_haut_droite); i>=0; i--) {
      (*this)[i][j_haut_droite]=mur;
    }
    for (int j(j_haut_droite); j<l; j++) {
      (*this)[i_haut_droite][j]=mur;
    }

    /* Coin bas-gauche */
    for (int i(i_bas_gauche); i<h; i++) {
      (*this)[i][j_bas_gauche]=mur;
    }
    for (int j(j_bas_gauche); j>=0; j--) {
      (*this)[i_bas_gauche][j]=mur;
    }

    /* Coin bas-droite */
    for (int i(i_bas_droite); i<h; i++) {
      (*this)[i][j_bas_droite]=mur;
    }
    for (int j(j_bas_droite); j<l; j++) {
      (*this)[i_bas_droite][j]=mur;
    }

    /* On termine de placer les murs externes */
    for (int i(i_haut_gauche); i<i_bas_gauche; i++) {
      (*this)[i][0]=mur;
    }

    for (int j(j_haut_gauche); j<j_haut_droite; j++) {
      (*this)[0][j]=mur;
    }
    
    for (int j(j_bas_gauche); j<j_bas_droite; j++) {
      (*this)[h-1][j]=mur;
    }

    for (int i(i_haut_droite); i<(i_bas_droite); i++) {
      (*this)[i][l-1]=mur;
    }


    /* On décide aléatoirement si on prolonge chaque coin vers
       l'intérieur ou pas */
    if (i_haut_gauche >1) {
      int r=1+rand()%(l/3);
      for (int j(j_haut_gauche); j<j_haut_gauche+r; j++) {
	(*this)[i_haut_gauche][j]=mur;
      }
    }
    if (j_haut_gauche > 1) {
      int r=rand()%(h/3);
      for (int i(i_haut_gauche); i<i_haut_gauche+r; i++) {
	(*this)[i][j_haut_gauche]=mur;
      }
    }

    if (i_haut_droite >1) {
      int r=rand()%(l/3);
      for (int j(j_haut_droite); j<j_haut_droite-r; j--) {
	(*this)[i_haut_droite][j]=mur;
      }
    }
    if (j_haut_droite < l-2) {
      int r=rand()%(h/3);
      for (int i(i_haut_droite); i<i_haut_droite+r; i++) {
	(*this)[i][j_haut_droite]=mur;
      }
    }

    if (i_bas_gauche <h-2) {
      int r=rand()%(l/3);
      for (int j(j_bas_gauche); j<j_bas_gauche+r; j++) {
	(*this)[i_bas_gauche][j]=mur;
      }
    }
    if (j_bas_gauche >1) {
      int r=rand()%(h/3);
      for (int i(i_bas_gauche); i>i_bas_gauche-r; i--) {
	(*this)[i][j_bas_gauche]=mur;
      }
    }

    if (i_bas_droite <h-2) {
      int r=rand()%(l/3);
      for (int j(j_bas_droite); j>j_bas_droite-r; j--) {
	(*this)[i_bas_droite][j]=mur;
      }
    }
    if (j_bas_droite <l-2) {
      int r=rand()%(h/3);
      for (int i(i_bas_droite); i>i_bas_droite-r; i--) {
	(*this)[i][j_bas_droite]=mur;
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
      while ((*this)[h_c][l_c] != caseVide ||
	     (h_c <= i_haut_gauche && l_c <= j_haut_gauche)
	     ||(h_c >= i_bas_gauche && l_c <= j_bas_gauche)
	     ||(h_c <= i_haut_droite && l_c >= j_haut_droite)
	     ||(h_c >= i_bas_droite && l_c >= j_bas_droite));
      (*this)[h_c][l_c]=but;
      
      
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
      while ((*this)[h_c][l_c] != caseVide||
	     (h_c >=h-2 || h_c <=1 || l_c >=l-2 || l_c<=1)
	     ||(h_c <= i_haut_gauche && l_c <= j_haut_gauche)
	     ||(h_c >= i_bas_gauche && l_c <= j_bas_gauche)
	     ||(h_c <= i_haut_droite && l_c >= j_haut_droite)
	     ||(h_c >= i_bas_droite && l_c >= j_bas_droite)
	     ||(*this)[h_c-1][l_c] != caseVide
	     ||(*this)[h_c][l_c-1] != caseVide
	     ||(*this)[h_c][l_c+1] != caseVide
	     ||(*this)[h_c+1][l_c] != caseVide);
      (*this)[h_c][l_c]=caisse;
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
	   ||(*this)[pos_h-1][pos_l] != caseVide
	   ||(*this)[pos_h][pos_l-1] !=caseVide
	   ||(*this)[pos_h][pos_l] != caseVide
	   ||(*this)[pos_h][pos_l+1] != caseVide
	   ||(*this)[pos_h+1][pos_l] != caseVide);
    (*this)[pos_h][pos_l]=pers;
  }

  virtual void deplacer(Sens s) {
    int new_pos_h=pos_h, new_pos_l=pos_l;
    int sens_vertical=0, sens_horizontal=0;
    switch(s) {
    case Sens::Haut:
      new_pos_h-=1;
      sens_vertical=-1;
      break;
    case Sens::Bas:
      new_pos_h+=1;
      sens_vertical=1;
      break;
    case Sens::Gauche:
      new_pos_l-=1;
      sens_horizontal=-1;
      break;
    case Sens::Droite:
      new_pos_l+=1;
      sens_horizontal=1;
      break;
    default:
      break;      
    }

    long & score=this -> score;

        /* si la case juste au-dessus est vide, le personnage
       peut s'y déplacer sans condition */
    if ((*this)[new_pos_h][new_pos_l]==caseVide) {
      (*this)[new_pos_h][new_pos_l]=pers;
      (*this)[pos_h][pos_l]=caseVide;
      pos_h=new_pos_h;
      pos_l=new_pos_l;
      score++;
    }

    /* si la case juste au-dessus contient une caisse,
       elle ne peut être poussée que si la case située derrière
       est vide ou contient un but */
    else if ((*this)[new_pos_h][new_pos_l]==caisse) {

      /* déplacement d'une caisse sur une case caseVide */
      if ((*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]==caseVide) {
	(*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]=caisse;
	(*this)[new_pos_h][new_pos_l]=pers;
	(*this)[pos_h][pos_l]=caseVide;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
      else if ((*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]==but) {

	/* déplacement d'une caisse sur un but */
	(*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]=caisse_but;
	(*this)[new_pos_h][new_pos_l]=pers;
	(*this)[pos_h][pos_l]=caseVide;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
    }

    /* si la case du dessus contient un but occupé
       par une caisse, cette dernière peut être poussée
       s'il y a un autre but ou une case vide derrière
     */
    else if ((*this)[new_pos_h][new_pos_l]==caisse_but) {

      /* d'un but vers un autre */
      if ((*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]==but) {
	(*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]=caisse_but;
	(*this)[new_pos_h][new_pos_l]=but;
	score++;
      }

      /* d'un but vers une case caseVide */
      else if ((*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]==caseVide) {
	(*this)[new_pos_h+sens_vertical][new_pos_l+sens_horizontal]=caisse;
	(*this)[new_pos_h][new_pos_l]=but;
	score++;
      }
    }
    
  }

  virtual void deplacerHaut() {
    deplacer(Sens::Haut);
  }
  
  virtual void deplacerBas() {
    deplacer(Sens::Bas);
  }
  
  virtual void deplacerGauche() {
    deplacer(Sens::Gauche);
  }
  
  virtual void deplacerDroite(){
    deplacer(Sens::Droite);
  }
  
  virtual bool jeuTermine() const {
    if (jeuBloque()) return true;
    for (int i(0); i<h; i++) {
      for (int j(0); j<l; j++) {
	if ((*this)[i][j]==but
	    ||(*this)[i][j]==caisse)
	  return false;
      }
    }
    return true;
  }

  virtual bool jeuBloque() const {
    /* un bloquage peut survenir lorsqu'une caisse ne peut plus être
       déplacée, c'est à dire lorsqu'il y a un mur derrière et sur l'un
       des côtés (gauche/droite)
    */
    for (int i(1); i<h-1; i++) {
      for (int j(1); j<l-1; j++) {
	if ((*this)[i][j]==caisse
	    && ((*this)[i-1][j]==mur
		||(*this)[i+1][j]==mur)
	    && ((*this)[i][j-1]==mur
		||(*this)[i][j+1]==mur)) {
	  return true;
	}
      }
    }
    return false;
  }
public:
  Sokoban(int longueur, int hauteur) :
    Jeu<CaseSok>(longueur,hauteur)
  { initialiser();}
};

#endif
