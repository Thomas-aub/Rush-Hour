#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <iostream>
#include <string>
#include <vector>
#include "case.hpp"
#include "vehicule.hpp"
#include <queue>
#include <unordered_set>



class Plateau {

    public:
        //  Constructeur
        Plateau(std::vector <Vehicule> listeVehicules, Plateau* plateau, Position sortie, Vehicule* principale);


        
        // Attributs
        Case grilles [6][6];
        Plateau* precedent;
        Position sortie;
        Vehicule* principale;
        bool gagnant;
        std::vector <Vehicule> listeVehicules; 


        // Méthodes
        void afficher(); //   affiche l'état actuel du plateau
        void generate(); //   génère tous les plateaux possibles à partir du plateau actuel
        void avancer(const Vehicule& v); //   appelle les déplacements suivant l'orientation du véhicule
        void deplacementDroite(const Vehicule& v); //   fait avancer un véhicule d'autant de cases vers la droite que possible
        void deplacementGauche(const Vehicule& v); //   fait avancer un véhicule d'autant de cases vers la gauche que possible
        void deplacementHaut(const Vehicule& v); //  fait avancer un véhicule d'autant de cases vers le haut que possible
        void deplacementBas(const Vehicule& v); //   fait avancer un véhicule d'autant de cases vers le bas que possible
        void appliquerDeplacement(const Vehicule& v, const Position& position); //   applique un déplacement donné à un véhicule donné
        void remonter(); //   remonte les précédents du plateau pour trouver la solution optimale

};

// File de pointeurs vers les Plateau générés et non-traités
extern std::queue<Plateau*> file;

// Set des id déjà générés
extern std::unordered_set<std::string> set_id;

// Vérifie si un id existe déjà
bool verifId(std::vector <Vehicule> listeVehicules);

// Utile dans la fonction de trie de listeVehicules
bool comparerVehicule(const Vehicule& v1, const Vehicule& v2);

// Créé un id par rapport au position des véhicules sur la grille
std::string createId(std::vector <Vehicule> listeVehicules);

// Remplace un véhicule donné par un autre dans la liste de véhicule (suite à un déplacement)
std::vector <Vehicule> remplacerVehicule(std::vector <Vehicule> listeVehicules, const Vehicule& v, const Vehicule& new_v);

// Booléen décrivant si un plateau gagnant a été trouvé
extern bool fin;

#endif
