#ifndef JEU_2048
#define JEU_2048

#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template<class C>
class Jeu2048 : public Jeu<C> {
protected:
  virtual void initialiser() {
    srand(time(nullptr));
    const int& l=this->longueur;
    const int& h=this->hauteur;
    int pos_h1=rand()%h;
    int pos_l1=rand()%l;
    int pos_h2, pos_l2;
    do {
      pos_h2=rand()%h;
      pos_l2=rand()%l;
    }
    while (pos_h2 == pos_h1 && pos_l2 == pos_l1);
    (*this)[pos_h1][pos_l1]=(C) ((1+rand()%2)*2);
    (*this)[pos_h2][pos_l2]=(C) ((1+rand()%2)*2);
  }
  virtual bool jeuTermine() const {return false;}
  virtual void deplacer(Sens sens) {
    switch (sens) {
    case Sens::Bas:
      break;
    case Sens::Haut:
      break;
    case Sens::Gauche:
      break;
    case Sens::Droite:
      break;
    default:
      break;
    }
  }
public:
  Jeu2048(int l, int h) : Jeu<C>(l,h) {initialiser();}
  virtual ~Jeu2048() {}
};

#endif
