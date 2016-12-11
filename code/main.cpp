#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"

int main() {
  Jeu<CaseSok,10,10> *j=new Sokoban<10,10>();
  j -> jouerHumain();
  delete j;
  return 0;
}
