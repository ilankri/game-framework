#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"
#include "Jeu2048.hpp"

int main() {
  const int l=5,h=5;
  Jeu<int> *j=new Jeu2048<int>(l,h);
  j -> jouerHumain();
  delete j;
  return 0;
}
