#include "Jeu.hpp"
#include "Taquin.hpp"

int main() {
  Jeu *j=new Taquin(2,2);
  j -> jouerHumain();
  delete j;
  return 0;
}
