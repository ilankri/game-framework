#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"

int main() {
  const int l=5,h=5;
  Jeu<int> *j=new Taquin<int>(l,h);
  j -> jouerHumain();
  delete j;
  return 0;
}
