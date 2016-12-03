#ifndef TAQUIN
#define TAQUIN

#include "Jeu.hpp"

using namespace std;

class Taquin : public Jeu {
protected:
  //coordonnées de la case vide
  int pos_vide_l;
  int pos_vide_h;
  virtual void afficher(ostream& o=cout) const;
  virtual bool bienTriePartiel() const;
public:
  Taquin(int, int);
  virtual ~Taquin();
  virtual void initialiser();
  virtual bool jeuTermine() const;
  virtual void jouerHumain();
  virtual void jouerRobot();
  virtual void deplacerHaut();
  virtual void deplacerBas();
  virtual void deplacerGauche();
  virtual void deplacerDroite();
};


#endif
