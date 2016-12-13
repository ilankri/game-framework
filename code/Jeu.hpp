#ifndef JEU
#define JEU

#include <iostream>
using namespace std;


template<class T, int l, int h>
class Jeu {
protected:
  T plateau[h][l];
  static const T caseVide= (T) 0;
  long score;
  
  virtual void afficher(ostream& o=cout) const=0;
  virtual void deplacerHaut()=0;
  virtual void deplacerBas()=0;
  virtual void deplacerGauche()=0;
  virtual void deplacerDroite()=0;
  virtual void initialiser()=0;
  virtual bool jeuTermine() const=0;
  virtual bool jeuBloque() const {return false;}
public:
  Jeu() : score(0) {}
  virtual void jouerHumain() {
    int rep;
    while (!jeuTermine()) {
      cout << *this;
      cout << "Entrer (2, 4, 8 ou 6) pour effectuer ";
      cout << "un déplacement (resp. bas, gauche, haut, droite) : ";
      cin >> rep;
      cin.ignore();
      switch (rep) {
      case 6:
	deplacerDroite();
	break;
      case 2:
      deplacerBas();
      break;
      case 4:
	deplacerGauche();
	break;
      case 8:
	deplacerHaut();
	break;
      default:
	break;
      }
    }
    cout << *this;
  }
  
  virtual void jouerRobot() {
    /*ceci est une version naïve : essayer si possible 
      de rendre le robot plus intelligent */
    srand(time(nullptr));
    while (!jeuTermine()) {
      cout << *this;
      int sens=rand()%4;
      switch(sens) {
      case 0:
	deplacerDroite();
	break;
      case 1:
	deplacerBas();
	break;
      case 2:
	deplacerGauche();
	break;
      case 3:
	deplacerHaut();
	break;
      default:
	break;
      }
    }
    cout << *this;
  }

  template<class C, int i, int j>
  friend ostream& operator<<(ostream &o, const Jeu<C,i,j> &jeu);
  const T* operator[](int i) const {return plateau[i];}
  T* operator[](int i) {return plateau[i];}
  virtual ~Jeu() {}
};


template<class T, int l, int h>
ostream& operator<<(ostream& o, const Jeu<T,l,h> &j) {
  j.afficher();
  o << "score : " << j.score << endl;
  if (j.jeuBloque()) o << "Game blocked !" << endl;
  if (j.jeuTermine()) o << "Game Over" << endl;
  return o;
}

#endif
