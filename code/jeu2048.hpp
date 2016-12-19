#ifndef JEU_2048
#define JEU_2048

#include "Jeu.hpp"
#include "square2048.hpp"
/* #include <cstdlib> */
/* #include <ctime> */
/* #include <iostream> */

/* using namespace std; */

class Jeu2048 : public Jeu<Square2048> {
public:
	Jeu2048(int l, int h);

	virtual ~Jeu2048() {}

protected:
	virtual void initialiser();

	virtual bool jeuTermine() const;

	virtual void deplacer(Sens sens);
};

#endif
