#ifndef JOUEUR
#define JOUEUR

template<class T>
class Joueur {
private:
  Jeu<T>& j;
public:
  static enum class Deplacement {G,D,H,B};
  virtual void jouer(Deplacement)=0;
};

#endif
