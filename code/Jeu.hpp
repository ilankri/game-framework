#ifndef JEU
#define JEU

#include <iostream>
using namespace std;


class Jeu {
protected:
  const int longueur;
  const int hauteur;
  float** plateau;
  static const float caseVide;
  int score;
  virtual void afficher(ostream& o=cout) const=0;
public:
  Jeu(int,int);
  virtual void initialiser()=0;
  virtual bool jeuTermine() const=0;
  virtual void jouerHumain()=0;
  virtual void jouerRobot()=0;
  virtual void deplacerHaut()=0;
  virtual void deplacerBas()=0;
  virtual void deplacerGauche()=0;
  virtual void deplacerDroite()=0;
  friend ostream& operator<<(ostream&, const Jeu&);
  float* operator[](int) const;
  virtual ~Jeu();
};

#endif
