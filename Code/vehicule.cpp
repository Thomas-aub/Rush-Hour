#include "vehicule.hpp"
#include <iostream>

int uniId = 'a';

Vehicule::Vehicule(Position pos, int lon, int orie, bool principal){
        position = pos;
        longueur = lon;
        orientation = orie;
        vehiculePrincipal = principal;
        id = uniId;
        uniId +=1;

};

Vehicule::Vehicule(Position pos, Vehicule v){
        position = pos;
        longueur = v.longueur;
        orientation = v.orientation;
        vehiculePrincipal = v.vehiculePrincipal;
        id = v.id;
};



