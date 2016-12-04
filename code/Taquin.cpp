#include "Taquin.hpp"

#include <cstdlib>
#include <ctime>


Taquin::Taquin(int l, int h) : Jeu(l,h) {
  initialiser();
}

void Taquin::initialiser() {
  //reste à gérer les grilles impossibles à réordonner :
  // (case vide paire + permutation impaire)
  // ou (case vide impaire + permutation paire)
  srand(time(nullptr));
  int tmp=1;

  //on remplit les cases
  for (int i(0); i<hauteur-1; i++) {
    for (int j(0); j<longueur; j++) {
      plateau[i][j]=tmp++;
    }
  }
  for (int j(0); j<longueur-1; j++) {
    plateau[hauteur-1][j]=tmp++;
  }
  plateau[hauteur-1][longueur-1]=0;
  pos_vide_h=hauteur-1;
  pos_vide_l=longueur-1;

  bool perm_paire=true; // la parité d'une permutation est celle du nombre d'échanges successifs qu'il faut faire pour obtenir la grille finale
  bool case_vide_paire=false; // la parité de la case vide est celle du nombre de déplacements à effectuer pour la mettre en bas à droite

  // on mélange les cases
  int i1(0), j1(0), i2(0), j2(0);

  
  for (int k(0); k<longueur*hauteur; k++) {
    i1=rand()%hauteur;
    j1=rand()%longueur;
    do {
      i2=rand()%hauteur;
      j2=rand()%longueur;
    }
    while (i1==i2 && j1==j2);
    int tmp=(*this)[i1][j1];
    (*this)[i1][j1]=(*this)[i2][j2];
    (*this)[i2][j2]=tmp;
    perm_paire=!perm_paire;
    
    //on met à jour les coordonnées de la case vide
    if ((*this)[i1][j1]==caseVide) {
      pos_vide_h=i1;
      pos_vide_l=j1;
    }
    else if ((*this)[i2][j2]==caseVide) {
	pos_vide_h=i2;
	pos_vide_l=j2;
    }
    case_vide_paire=((longueur-1-pos_vide_l)+(hauteur-1-pos_vide_h))%2==0;
  }

  //pour que la grille soit résolvable, il faut que la permutation soit de même parité que la case vide
  if (case_vide_paire ^ perm_paire) {
    do {
      i1=rand()%hauteur;
      j1=rand()%longueur;
    }
    while (i1==pos_vide_h && j1==pos_vide_l);
    do {
      i2=rand()%hauteur;
      j2=rand()%longueur;
    }
    while ((i2==pos_vide_h && j2==pos_vide_l)
	   ||(i2==i1 && j2==j1));
    tmp=(*this)[i1][j1];
    (*this)[i1][j1]=(*this)[i2][j2];
    (*this)[i2][j2]=tmp;
    
  }
}

bool Taquin::jeuTermine() const {
  if ((*this)[hauteur-1][longueur-1] != caseVide) {
    //cout << "Taquin::jeuTermine() [1] : la dernière case n'est pas vide !"<< endl;
    return false;
  }
  int tmp=1;
  for (int i(0); i<hauteur-1; i++) {
    for (int j(0); j<longueur; j++) {
      if ((*this)[i][j] != (tmp++)) {
	//cout << "Taquin::jeuTermine() [2] : tmp="<<tmp << ", "<< "i=" << i << ", j=" << j << endl;
	return false;
      }
    }
  }
  for (int j(0) ;j< longueur-1; j++) {
    if ((*this)[hauteur-1][j] != (tmp++)) {
      //cout << "Taquin::jeuTermine() [3] : tmp="<<tmp << ", "<< "i=" << (hauteur-1) << ", j=" << j << endl;
      return false;
    }
  }
  //cout << "Jeu terminé" <<endl;
  return true;
}

void Taquin::jouerHumain() {
  int rep;
  while (!jeuTermine()) {
    cout << *this;
    cout << "Entrer (2, 4, 8 ou 6) pour effectuer un déplacement (resp. bas, gauche, haut, droite) : ";
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

void Taquin::jouerRobot() {
  //ceci est une version naïve : essayer si possible de rendre le robot plus intelligent
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

void Taquin::afficher(ostream& o) const {
  for (int j(0); j<9*longueur-(longueur-2); j++) o << "-"; //longueur d'une ligne, en tenant compte des tabulations
  o << endl;
  for (int i(0); i<hauteur; i++) {
    for (int j(0); j<longueur; j++) {
      o << "| ";
      if ((*this)[i][j]==caseVide) o << " ";
      else o<< (*this)[i][j];
      o << "\t";
    }
    o << " |" << endl;
    for (int j(0); j<9*longueur-(longueur-2); j++) o << "-";
    o <<endl;
  }
  //cout << "Coordonnées (h,l) case vide : (" << pos_vide_h << "," << pos_vide_l << ")" << endl;
}


/*
bool Taquin::bienTriePartiel() const {
  //vérifie si toutes les cases avant la case (h,l) sont bien placées
  int tmp(1);
  for (int i(0); i<pos_vide_h; i++) {
    for (int j(0) ; j<longueur; j++)
      if ((*this)[i][j] != tmp++) {
	//cout << "bienTriePartiel() : tmp="<< tmp << ", i="<<i<<", j="<<j<<endl;
	return false;
      }
  }
  for (int j(0); j<pos_vide_l; j++)
    if ((*this)[pos_vide_h][j] != tmp++) {
      //cout << "bienTriePartiel() : tmp="<< tmp << ", i="<<pos_vide_h<<", j="<<j<<endl;
      return false;
    }
  //cout <<"bienTriePartiel() : tmp=" << tmp << endl;
  return true;
}
*/

void Taquin::deplacerHaut() {
  if (pos_vide_h >0) {
    int tmp=(*this)[pos_vide_h][pos_vide_l];
    (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h-1][pos_vide_l];
    (*this)[--pos_vide_h][pos_vide_l]=tmp; //mettre à jour les coordonnées de la case vide
    score++;
  }
}

void Taquin::deplacerBas() {
  if (pos_vide_h < hauteur-1) {
    int tmp=(*this)[pos_vide_h][pos_vide_l];
    (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h+1][pos_vide_l];
    (*this)[++pos_vide_h][pos_vide_l]=tmp; //mettre à jour les coordonnées de la case vide
    score++;
  }
}

void Taquin::deplacerGauche() {
  if (pos_vide_l >0) {
    int tmp=(*this)[pos_vide_h][pos_vide_l];
    (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h][pos_vide_l-1];
    (*this)[pos_vide_h][--pos_vide_l]=tmp; // mettre à jour les coordonnées de la case vide
    score++;
  }
}

void Taquin::deplacerDroite() {
  if (pos_vide_l <longueur-1) {
    int tmp=(*this)[pos_vide_h][pos_vide_l];
    (*this)[pos_vide_h][pos_vide_l]=(*this)[pos_vide_h][pos_vide_l+1];
    (*this)[pos_vide_h][++pos_vide_l]=tmp; // mettre à jour les coordonnées de la case vide
    score++;
  }
}

Taquin::~Taquin() {
}

