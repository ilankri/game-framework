#include "Jeu.hpp"
#include "Taquin.hpp"
#include "Sokoban.hpp"
#include "Jeu2048.hpp"

int main() {
  const int l=4,h=4;
  Jeu<int> *j=new Taquin<int>(l,h);
  j -> jouerHumain();
  delete j;
  return 0;
}
