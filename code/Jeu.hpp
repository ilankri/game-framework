#ifndef JEU
#define JEU

#include <iostream>
using namespace std;

enum class Sens{Haut,Bas,Gauche,Droite};

template<class T>
class Jeu {
protected:
  const int longueur,hauteur;
  T** plateau;
  static const T caseVide= (T) 0;
  long score;
  bool quitter;
  virtual void afficher(ostream& o=cout) const=0;
  virtual void deplacer(Sens)=0;
  virtual void deplacerHaut() {deplacer(Sens::Haut);}
  virtual void deplacerBas() {deplacer(Sens::Bas);}
  virtual void deplacerGauche() {deplacer(Sens::Gauche);}
  virtual void deplacerDroite() {deplacer(Sens::Droite);}
  virtual void initialiser()=0;
  virtual bool jeuTermine() const=0;
  virtual bool jeuBloque() const {return false;}
public:
  Jeu(int l, int h) : longueur(l), hauteur(h), plateau(new T*[h]), score(0), quitter(false) {
    for (int i(0); i<h; i++) plateau[i]=new T[l];
  }
  virtual void jouerHumain() {
    int rep;
    while (!jeuTermine() && !quitter) {
      cout << *this;
      cout << "Entrer (2, 4, 8 ou 6) pour effectuer ";
      cout << "un déplacement (resp. bas, gauche, haut, droite) ";
      cout << "ou 0 pour quitter le jeu : ";
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
      case 0:
	quitter=true;
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

  template<class C>
  friend ostream& operator<<(ostream &o, const Jeu<C> &jeu);
  const T* operator[](int i) const {return plateau[i];}
  T* operator[](int i) {return plateau[i];}
  virtual ~Jeu() {
    for (int i(0); i<hauteur; i++) delete[] plateau[i];
    delete[] plateau;
  }
};


template<class T>
ostream& operator<<(ostream& o, const Jeu<T> &j) {
  j.afficher();
  o << "score : " << j.score << endl;
  if (j.jeuBloque()) o << "Game blocked !" << endl;
  if (j.jeuTermine()) o << "Game Over" << endl;
  return o;
}

#endif
