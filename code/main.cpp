#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"
#include "Jeu2048.hpp"

int main() {
  const int l=10,h=10;
  Jeu<CaseSok> *j=new Sokoban<CaseSok>(l,h);
  j -> jouerHumain();
  delete j;
  return 0;
}
