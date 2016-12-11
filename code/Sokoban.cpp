#include "Sokoban.hpp"


ostream& operator<<(ostream& o, CaseSok const& c) {
  switch(c) {
  case CaseSok::vide:
    o << " ";
    break;
  case CaseSok::mur:
    o << "=";
    break;
  case CaseSok::pers:
    o << "*";
    break;
  case CaseSok::caisse:
    o << "x";
    break;
  case CaseSok::but:
    o << "o";
    break;
  case CaseSok::caisse_but:
    o << "ø";
    break;
  }
  return o;
}

