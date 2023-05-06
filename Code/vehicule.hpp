#ifndef VEHICULE_HPP
#define VEHICULE_HPP

#include "position.hpp"
#include "case.hpp"
#include <string>
#include <vector>

class Vehicule {

    public :
        Vehicule(Position position, int longueur, int orientation, bool vehiculePrincipal);
        Vehicule(Position position, Vehicule v);
        
        Position position;
        int longueur;
        int orientation; // 1 : horizontale  &   0 : verticale
        bool vehiculePrincipal;
        std::string id;

};


#endif
