#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "plateau.hpp"
#include "position.hpp"
#include "vehicule.hpp"
using namespace std;

Plateau* parseFile(string fichier){     // Parse le fichier fourni et génère un Plateau de départ


        ifstream infile(fichier);

        if (!infile.is_open()) {
            cout << "Erreur d'ouverture du fichier." << std::endl;

        } else {
            int posX, posY, longueur, orientation;

            infile >> posX >> posY;

            Position sortie;
            sortie.ligne = posX;
            sortie.colonne = posY;


            bool principale = true;

            vector <Vehicule> listeVehicules;
            while (infile >> posX>> posY>> longueur>> orientation) {
                Position position;
                position.ligne = posX;
                position.colonne = posY;
                listeVehicules.push_back(Vehicule(position, longueur, orientation, principale));
                principale = false;
            }



            infile.close();
            return  new Plateau(listeVehicules, nullptr, sortie, &listeVehicules[0]);

        }

        
    return NULL;
        
}


int main (){
   

    Plateau* depart = parseFile("../Sujet/puzzle.txt");

    // Génération des premiers voisons du plateau initial pour les ajouter à la file
    depart->generate();

    // Pour la destruction
    std::vector<Plateau*> garbage;

    // Tant qu'il y a des plateaux dans la file on continue la génération
    while(file.size() > 1){

        // Quand on a un plateau gagnant on arrête la génération
        if (!fin){
            file.front()->generate();
        }

        garbage.push_back(file.front());
        file.pop();
    }
    
    // Destructeur
    while(garbage.size() > 0){
        delete garbage.front();
        garbage.erase(garbage.begin());
    }

    // Si aucune solution n'a été trouvée
    if(!fin){
        cout << "Il n'y a de solution au problème" << endl;
    }
    
    
    delete depart;

    return 0;
}
