#include "Jeu.hpp"
#include "Taquin.hpp"

int main() {
  Jeu *j=new Taquin(3,3);
  j -> jouerHumain();
  delete j;
  return 0;
}
