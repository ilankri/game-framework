#ifndef SOKOBAN
#define SOKOBAN

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class CaseSok{vide,mur,pers,caisse,but,caisse_but,pers_but};

ostream& operator<<(ostream&, CaseSok const&);

template <class C>
class Sokoban : public Jeu<CaseSok> {
private:
  const int &l=longueur, &h=hauteur;
protected:
  int nb_caisses;
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
  static const C pers_but=(C) 6;
  
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
    placerMursExternes();
    placerMursInternes();
  }
  
  virtual void placerMursExternes() {

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

  }
  virtual void placerMursInternes() {

    /* On décide aléatoirement si on place des murs internes
       ou pas*/
    int j_h_mil=(j_haut_gauche+j_haut_droite)/2;
    int j_b_mil=(j_bas_gauche+j_bas_droite)/2;
    int i_mil_g=(i_haut_gauche+i_haut_droite)/2;
    int i_mil_d=(i_haut_droite+i_bas_droite)/2;

    int lim_h_mil=1+rand()%(h/4), lim_b_mil=1+rand()%(h/4);
    int lim_mil_g=1+rand()%(l/4), lim_mil_d=1+rand()%(l/4);

    for (int i(0); i<lim_h_mil; i++)
      (*this)[i][j_h_mil]=mur;
    
    for (int i(h-1); i>h-1-lim_b_mil; i--)
      (*this)[i][j_b_mil]=mur;
    
    for (int j(0); j<lim_mil_g; j++)
      (*this)[i_mil_g][j]=mur;

    for(int j(l-1); j>l-1-lim_mil_d; j--) 
      (*this)[i_mil_d][j]=mur;
  }
  
  virtual void placer_buts_caisses() {
    //cout << "placer_buts_caisses()" << endl;
    for (int k(0); k<nb_caisses; k++) {
      int l_c,h_c;
      /* on place les buts aléatoirement sur le plateau, en
	 vérifiant qu'ils ne soient jamais en dehors des murs */
      do {
	l_c=rand()%l;
	h_c=rand()%h;
      }
      while ((*this)[h_c][l_c] != caseVide || horsZoneMurs(h_c,l_c));
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
      while (!zoneLibre(h_c,l_c));
      (*this)[h_c][l_c]=caisse;
    }
  }

  virtual bool zoneLibre(int h_c, int l_c) {

    if (horsZoneMurs(h_c,l_c)) return false;
    if ((*this)[h_c][l_c]!=caseVide) return false;
    if ((*this)[h_c+1][l_c] !=caseVide) return false;
    if ((*this)[h_c-1][l_c] !=caseVide) return false;
    if ((*this)[h_c][l_c-1] != caseVide) return false;
    if ((*this)[h_c][l_c+1] != caseVide) return false;

    return true;
  }

  virtual bool horsZoneMurs(int h_c, int l_c) {
    const int &h=this->hauteur;
    const int &l=this->longueur;
    
    if (h_c>=h-2||h_c<=1) return true;
    if (l_c>=l-2||l_c<=1) return true;

    if (h_c <= i_haut_gauche && l_c <= j_haut_gauche) return true; 
    if (h_c >= i_bas_gauche && l_c <= j_bas_gauche) return true;
    if (h_c <= i_haut_droite && l_c >= j_haut_droite) return true;
    if (h_c >= i_bas_droite && l_c >= j_bas_droite) return true;

    return false;
  }

  virtual void placer_pers() {
    //cout << "placer_pers()" << endl;
    do {
      pos_l=1+rand()%(l-2);
      pos_h=1+rand()%(h-2);
    }

    /* pour que le personnage puisse effectuer au moins un
       mouvement, on le place dans une case entourée uniquement
       de cases vides, toujours à l'intérieur de la zone délimitée
       par les murs externes */
    while (!zoneLibre(pos_h,pos_l));
    (*this)[pos_h][pos_l]=pers;
  }

  virtual void deplacer(Sens s) {
    
    int new_pos_h=pos_h, new_pos_l=pos_l;
    int sens_h=0, sens_l=0;
    
    C & source=(*this)[pos_h][pos_l];
    switch(s) {
    case Sens::Haut:
      new_pos_h-=1;
      sens_h=-1;
      break;
    case Sens::Bas:
      new_pos_h+=1;
      sens_h=1;
      break;
    case Sens::Gauche:
      new_pos_l-=1;
      sens_l=-1;
      break;
    case Sens::Droite:
      new_pos_l+=1;
      sens_l=1;
      break;
    default:
      break;      
    }

    C & dest=(*this)[new_pos_h][new_pos_l];
    C & derriere=(*this)[new_pos_h+sens_h][new_pos_l+sens_l];
    
    long & score=this -> score;
    
        /* si la case juste au-dessus est vide, le personnage
       peut s'y déplacer sans condition */

    if (dest==caseVide||dest==but) {
      dest= dest==caseVide ? pers : pers_but;
      if (source==pers)
	source=caseVide;
      else if (source==pers_but)
	source=but;
      pos_h=new_pos_h;
      pos_l=new_pos_l;
      score++;
    }
    
    /* si la case juste au-dessus contient une caisse,
       elle ne peut être poussée que si la case située derrière
       est vide ou contient un but */
    
    else if (dest==caisse) {

      /* déplacement d'une caisse sur une case caseVide */

      if (derriere==caseVide) {
	derriere=caisse;
	dest=pers;
	if (source==pers)
	  source=caseVide;
	else if (source==pers_but)
	  source=but;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
      else if (derriere==but) {
    
	/* déplacement d'une caisse sur un but */
    
	derriere=caisse_but;
	dest=pers;
	if (source==pers)
	  source=caseVide;
	else if (source==pers_but)
	  source=but;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
    }
    
    /* si la case du dessus contient un but occupé
       par une caisse, cette dernière peut être poussée
       s'il y a un autre but ou une case vide derrière
     */
    
    else if (dest==caisse_but) {
    
      /* d'un but vers un autre */
    
      if (derriere==but) {
	derriere=caisse_but;
	dest=pers_but;
	if (source==pers)
	  source=caseVide;
	else if (source==pers_but)
	  source=but;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
    
      /* d'un but vers une case caseVide */
    
      else if (derriere==caseVide) {
	derriere=caisse;
	dest=pers_but;
	if (source==pers)
	  source=caseVide;
	else if (source==pers_but)
	  source=but;
	pos_h=new_pos_h;
	pos_l=new_pos_l;
	score++;
      }
    }
    
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
  Sokoban(int longueur, int hauteur, int nb_caisses=-1) :
    Jeu<CaseSok>(longueur,hauteur)
  { if (nb_caisses==-1) this->nb_caisses=sqrt(longueur*hauteur)/2;
    else this->nb_caisses=nb_caisses;
    initialiser();
  }
  virtual ~Sokoban() {}
};

#endif
