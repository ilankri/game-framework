#include "Jeu.hpp"


const float Jeu::caseVide=0.0;

Jeu::Jeu(int l, int h) : longueur(l), hauteur(h), plateau(new float*[h]), score(0) {
  for (int i(0); i<h; i++) plateau[i]=new float[l];
}

Jeu::~Jeu() {
  for (int i(0); i<hauteur; i++) delete[] plateau[i];
  delete[] plateau;
}

void Jeu::afficher(ostream &o) const { o<<"";}

float* Jeu::operator[](int i) const {
  return plateau[i];
}

ostream& operator<<(ostream& o, const Jeu& j) {
  j.afficher();
  o << "score : " << j.score << endl;
  return o;
}
