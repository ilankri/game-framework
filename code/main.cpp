#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"

int main() {
  const int l=10,h=10;
  Jeu<CaseSok,l,h> *j=new Sokoban<l,h>();
  j -> jouerHumain();
  delete j;
  return 0;
}
