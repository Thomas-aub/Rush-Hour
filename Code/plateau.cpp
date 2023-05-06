#include "plateau.hpp"
#include "case.hpp"
#include "vehicule.hpp"
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <unordered_set>


bool fin = false;
int generation = 0;
std::queue<Plateau*> file;
std::unordered_set<std::string> set_id;


Plateau::Plateau(std::vector <Vehicule> lV, Plateau* plateau, Position sortie, Vehicule* principal) {

    // Initialistation variable
    this->precedent = plateau;
    this->sortie = sortie;
    this->principale = principal;


    for (Vehicule v : lV){
        this->listeVehicules.push_back(v);
    }


    // vérifier l'état gagnant
    int voiture, out;
    if (principale->orientation == 1){   // On effectuera la comparaison sur la colonne
        voiture = principale->position.colonne;
        out = sortie.colonne;
    } else {                            // On effectuera la comparaison sur la ligne
        voiture = principale->position.ligne;
        out = sortie.ligne;
    }


    gagnant = ( ((voiture + principale->longueur - 1) == out) || (voiture == out) ) ;// On vérifie si le véhicule est collé à la sortie



    // Génération grille
    Case grille [6][6];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            grille[i][j] = Case();
        }
    }


    for (long unsigned int i = 0; i < listeVehicules.size(); ++i) {
        for(int j = 0; j < listeVehicules[i].longueur; ++j) {
            if(listeVehicules[i].orientation == 0) {
                grille[listeVehicules[i].position.ligne+j][listeVehicules[i].position.colonne].id = listeVehicules[i].id;
            } else {
                grille[listeVehicules[i].position.ligne][listeVehicules[i].position.colonne+j].id = listeVehicules[i].id;
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            this->grilles[i][j] = grille[i][j];
        }
    }
    if (gagnant == true){
        fin = true;
        remonter();

    }
}

void Plateau::afficher(){
    for(int i = 0; i <= 7; ++i){
        if(i == 0 || i == 7){
        std::cout <<" ";

        } else {
        std::cout <<"_ ";

        }
    }

    std::cout << std::endl;

    for (int i = 0; i < 6; ++i) {
        std::cout<<"|";
        int j ;
        for (j = 0;j < 6; ++j) {       
            if (strcmp (grilles[i][j].id.c_str()," ") == 0){
                std::cout << "  ";
            } else {
                std::cout << grilles[i][j].id <<" ";
            }
        }
        if (j != sortie.colonne && i != sortie.ligne){
            std::cout << "|";
        }
        std::cout << std::endl;
    }

     for(int i = 0; i < 6; ++i){
        std::cout <<" ‾";
    }


    std::cout << std::endl;

}


void Plateau::generate(){
    // compteur du nombre d'essais
    generation ++;
    
    // Génère tous les déplacements possibles
    for (long unsigned int i =0; i < listeVehicules.size(); ++i){
        avancer(listeVehicules[i]);
        if (fin){
            break;
        }
        
    }

}

void Plateau::avancer(const Vehicule& v){
    
    switch ( v.orientation )
      {
         case 0:
            deplacementHaut(v);
            deplacementBas(v);
            break;
         case 1:
            deplacementGauche(v) ;      
            deplacementDroite(v);
            break;
      }

}



void Plateau::deplacementDroite(const Vehicule& v){
    

    // Les coordonnées de l'élément le plus à droite
    int limite_colonne = v.position.colonne + v.longueur - 1;
    int limite_ligne = v.position.ligne;

    // On doit vérifier que le véhcule ne soit pas déjà au bord ou en collision
    bool collision = (limite_colonne >= 5);
    if (!collision){
        collision = !(strcmp (grilles[limite_ligne][limite_colonne + 1].id.c_str(), " ") == 0);
    }
    

    // Si il y a collision ou si le véhicule est sur la dernière colonne 
    while (!collision && limite_colonne < 5) {
    
        limite_colonne ++;

        
        if(strcmp (grilles[limite_ligne][limite_colonne].id.c_str(), " ") == 0) {               // Si la case est vide
            

            // Création nouvelle voiture (après déplacement)
            Position position;
            position.ligne = limite_ligne;
            position.colonne = limite_colonne - v.longueur + 1;
            

            // Si possible on appliquera un déplacement
            appliquerDeplacement(v, position);
            

        } else {                                                                                // Si la case n'est pas vide
            collision = true;
        }
            
        
    }
}





void Plateau::deplacementGauche(const Vehicule& v){
    // Les coordonnées de l'élément le plus à gauche
    int limite_colonne = v.position.colonne;
    int limite_ligne = v.position.ligne;

    // On doit vérifier que le véhcule ne soit pas déjà au bord ou en collision
    bool collision = (limite_colonne <= 0);
    if (!collision){
        collision = !(strcmp (grilles[limite_ligne][limite_colonne - 1].id.c_str(), " ") == 0);

    }
    
    
    // Si il y a collision ou si le véhicule est sur la dernière colonne 
    while (!collision && limite_colonne > 0) {
        limite_colonne --;
       
        if(strcmp (grilles[limite_ligne][limite_colonne].id.c_str(), " ") == 0) {               // Si la case est vide
            

            // Création nouvelle voiture (après déplacement)
            Position position;
            position.ligne = limite_ligne;
            position.colonne = limite_colonne;
            
            // Si possible on appliquera un déplacement
            appliquerDeplacement(v, position);

        } else {                                                                                // Si la case n'est pas vide
            collision = true;
        }
    }
    
}





void Plateau::deplacementHaut(const Vehicule& v){


    // Les coordonnées de l'élément le plus haut
    int limite_colonne = v.position.colonne;
    int limite_ligne = v.position.ligne;

    // On doit vérifier que le véhcule ne soit pas déjà au bord ou en collision
    bool collision = (limite_ligne <= 0);
    if (!collision){
        collision = !(strcmp (grilles[limite_ligne - 1][limite_colonne].id.c_str(), " ") == 0);
    }

    // Si il y a collision ou si le véhicule est sur la dernière colonne 
    while (!collision && limite_ligne > 0) {

        limite_ligne --;
        
        if(strcmp (grilles[limite_ligne][limite_colonne].id.c_str(), " ") == 0) {       // Si la case est vide
            

            // Création nouvelle voiture (après déplacement)
            Position position;
            position.ligne = limite_ligne;
            position.colonne = limite_colonne ;

            // Si possible on appliquera un déplacement
            appliquerDeplacement(v, position);

            
        } else {                                                                       // Si la case n'est pas vide
            collision = true;
        }
    }

    

}





void Plateau::deplacementBas(const Vehicule& v){


    // Les coordonnées de l'élément le plus bas
    int limite_colonne = v.position.colonne ;
    int limite_ligne = v.position.ligne + v.longueur - 1;

    // On doit vérifier que le véhcule ne soit pas déjà au bord ou en collision
    bool collision = (limite_ligne >= 5);
    if (!collision){
        collision = !(strcmp (grilles[limite_ligne + 1][limite_colonne].id.c_str(), " ") == 0);
    }

    // Si il y a collision ou si le véhicule est sur la dernière colonne 
    while (!collision && limite_ligne < 5) {
        limite_ligne ++;

        
        if(strcmp (grilles[limite_ligne][limite_colonne].id.c_str(), " ") == 0) {       // Si la case est vide
            
            // Création nouvelle voiture (après déplacement)
            Position position;
            position.ligne = limite_ligne - v.longueur + 1;
            position.colonne = limite_colonne ;
            
            // Si possible on appliquera un déplacement
            appliquerDeplacement(v, position);

        
        } else {                                                                        // Si la case n'est pas vide 

            collision = true;
        }
    }
    
}


void Plateau::appliquerDeplacement(const Vehicule& v, const Position& position){

    Vehicule new_v = Vehicule(position, v);

    // Nouvelle liste de véhicule pour le nouveau plateau
    std::vector <Vehicule> new_listeVehicules = remplacerVehicule(listeVehicules, v, new_v);
    

    // On vérifie si le plateau généré n'existe pas déjà
    if(verifId(new_listeVehicules)){

        // On génère le nouveau plateau en gérant le cas du véhicule principal

        if (new_v.vehiculePrincipal){
            Plateau* new_plateau = new Plateau(new_listeVehicules, this, sortie, &new_v);
            // Emfile le plateau suivant
            file.push(new_plateau);

        } else {
            int id_principal = 0;
            for ( long unsigned int i = 0; i < listeVehicules.size(); ++i){
                if (listeVehicules[i].vehiculePrincipal){
                    id_principal = i;
                    break;
                }
            }

            Plateau* new_plateau = new Plateau(new_listeVehicules, this, sortie, &listeVehicules[id_principal]);

            // Emfile le plateau suivant
            file.push(new_plateau);

        }
    }
}






void Plateau::remonter(){
    Plateau* precedent = this;
    int nb_coups = -1;

    // On stock dans affichage le vector des précédents
    std::vector <Plateau*> affichage;

    while(precedent){
        nb_coups ++;
        affichage.push_back(precedent);
        precedent = precedent->precedent;
    }

    // On affiche chaque plateau deu vector affichage en commencant par le départ (qui est à la fin)
    for (long unsigned int i = affichage.size(); i > 0; i--){
        if (i != affichage.size()){
            std::cout << "Coup n°" << affichage.size()-i << std::endl;
        } else {
            std::cout << "\nSituation de départ" << std::endl;
        }
        affichage[i-1]->afficher();
    }
    

    std::cout << "Nombre de coups : " << nb_coups << std::endl; 
    std::cout << "Nombre de générations : " << generation << std::endl;
    
    delete this;
    
}





// On compare l'id de 2 véhicules
bool comparerVehicule(const Vehicule& v1, const Vehicule& v2){
    return v1.id < v2.id;
}

// on génère un id par rapport au placement des véhicules
std::string createId(std::vector <Vehicule> listeVehicules){
    std::string  id_plateau = "";
    // On commence par trier listeVehicule par id (ordre alphabétique)
    sort(listeVehicules.begin(), listeVehicules.end(), comparerVehicule);
    
    // On génère ensuite son id
    for (Vehicule v : listeVehicules){
         id_plateau =  id_plateau + std::to_string(v.position.ligne) + std::to_string(v.position.colonne);
    }
    return  id_plateau;
}

// On vérifie si l'id généré est déjà dans le set
bool verifId(std::vector <Vehicule> listeVehicules){

    std::string id_plateau = createId(listeVehicules);

    if (set_id.find(id_plateau) == set_id.end()){
        set_id.insert(id_plateau);
        return true;
    }

    return false;
     
}


// Nouvelle liste de véhicule pour le nouveau plateau
std::vector <Vehicule> remplacerVehicule(std::vector <Vehicule> listeVehicules, const Vehicule& v, const Vehicule& new_v){

    // On modifie l'ancien véhicule par le nouveau
    std::vector <Vehicule> new_listeVehicules = listeVehicules;
    std::vector<Vehicule>::iterator it;
    it = new_listeVehicules.begin();
    for (Vehicule veh : new_listeVehicules){
        it ++;
        if (strcmp (veh.id.c_str(), v.id.c_str()) == 0){
            new_listeVehicules.erase(it - 1);
        }
    }
    new_listeVehicules.push_back(new_v);
    return new_listeVehicules;
}
