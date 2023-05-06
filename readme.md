# Projet Rush Hour

Le but de ce projet est d'écrire un programme permettant de trouver une
solution au jeu *Rush Hour*.

## Règles du jeu

Le jeu Rush Hour se joue seul sur une grille carrée de six cases de côté. Sur
cette grille sont répartis des véhicules d'une case de largeur, et de deux ou
trois cases de longueur. Ces véhicules peuvent être placés horizontalement ou
verticalement. Chaque véhicule peut être déplacé en avant ou en arrière, mais
pas latéralement, tant qu'il n'entre pas en collision avec un autre véhicule.
Le but du jeu est de faire sortir l'un des véhicules par une sortie placée sur
le bord du plateau. L'image ci dessous illustre un exemple de partie.

![Exemple Rush Hour](Sujet/rush_hour.gif)

Chaque déplacement de véhicule compte pour un coup, quelle que soit la longueur
du déplacement. La qualité de votre solution dépend donc du nombre de coups
nécessaires depuis la situation initiale pour faire sortir le véhicule.

## Principe

Le programme présenté est un algorithme de recherche de chemin appelé l'algorithme de recherche en largeur d'abord (BFS). Il s'agit d'une méthode pour parcourir tous les états possibles à partir de l'état initial (dans ce cas-ci, le plateau de jeu initial) jusqu'à l'état final (dans ce cas-ci, le plateau de jeu gagnant).

Le principe de l'algorithme BFS est de créer une file (FIFO) et d'y ajouter l'état initial. Ensuite, on extrait l'état en tête de file, on génère tous les états possibles à partir de celui-ci, et on les ajoute à la fin de la file. On répète ce processus jusqu'à ce qu'on atteigne l'état final ou que la file soit vide.

Dans le cas présent, l'état initial est le plateau de jeu initial, et l'état final est un plateau de jeu où le véhicule principal (la voiture rouge) est à la position de la sortie.

Chaque état du plateau de jeu est représenté par une instance de la classe Plateau, qui contient la position de chaque véhicule ainsi que la position de la sortie.

L'algorithme BFS parcourt donc tous les états possibles du plateau de jeu, en essayant de déplacer chaque véhicule dans toutes les directions possibles. À chaque déplacement, on vérifie si on a atteint l'état final. Si c'est le cas, on arrête le processus de recherche et on retourne le chemin trouvé pour atteindre cet état final.

Pour trouver le plus court chemin, on peut utiliser une variante de l'algorithme BFS appelée "BFS modifié". Cette variante consiste à ajouter à chaque état visité une référence à l'état qui l'a généré. De cette manière, lorsque l'on atteint l'état final, on peut remonter la chaîne des états parents pour reconstruire le chemin le plus court qui mène à cet état final.

Dans le programme présenté, la liste des états parents est implicitement stockée dans la file, car chaque état généré est ajouté à la fin de la file, après l'état qui l'a généré. Lorsqu'on atteint l'état final, on peut donc remonter la file pour reconstruire le chemin le plus court qui mène à cet état final.


## Structure du projet


### <ins>Plateau</ins>

**Attributs :**

  - grilles : un tableau de 6x6 de la classe "Case" qui représente l'état actuel du plateau de jeu.
  - precedent : un pointeur vers le plateau précédent.
  - sortie : un objet de la classe "Position" qui représente la position de la sortie.
  - principale : un pointeur vers l'objet de la classe "Vehicule" qui représente la voiture qui doit sortir du plateau.
  - gagnant : un booléen qui indique si le plateau actuel est gagnant ou non.
  - listeVehicules : un vecteur qui contient tous les véhicules sur le plateau.


**Méthodes :**

  -  Plateau() : le constructeur de la classe qui prend en paramètre une liste de véhicules, un pointeur vers le plateau précédent, la position de la sortie et un pointeur vers la voiture principale.
  -  afficher() : une méthode qui affiche l'état actuel du plateau.
  -  generate() : une méthode qui génère tous les plateaux possibles à partir du plateau actuel.
  -  avancer() : une méthode qui appelle les déplacements suivant l'orientation du véhicule.
  -  deplacementDroite() : une méthode qui fait avancer un véhicule d'autant de cases vers la droite que possible.
  -  deplacementGauche() : une méthode qui fait avancer un véhicule d'autant de cases vers la gauche que possible.
  -  deplacementHaut() : une méthode qui fait avancer un véhicule d'autant de cases vers le haut que possible.
  -  deplacementBas() : une méthode qui fait avancer un véhicule d'autant de cases vers le bas que possible.
  -  appliquerDeplacement() : une méthode qui applique un déplacement donné à un véhicule donné.
  -  remonter() : une méthode qui remonte les précédents du plateau pour trouver la solution optimale.
  -  verifId() : une fonction qui vérifie si un état est déjà présent dans le tableau set_id.
  -  comparerVehicule() : une fonction qui compare deux véhicules selon leur id pour ensuite effectuer un trie.
  -  createId() : une fonction qui crée un identifiant unique pour un état donné.
  -  remplacerVehicule() : une fonction qui remplace un véhicule par un nouveau véhicule dans une liste de véhicules donnée.

  **Variables Globales :**
  - file : une file de pointeurs vers des objets de la classe "Plateau".
  - set_id : un tableau de hachage qui contient les identifiants des états déjà visités.
  - fin : un booléen qui indique si la solution a été trouvée ou non.
  - nb_coups : un entier qui représente le nombre de coups effectués pour atteindre la solution.


### <ins>Vehicule</ins>

  **Attributs :**

  - position : un objet Position représentant la position du véhicule sur le plateau de jeu.
  - longueur : un entier représentant la longueur du véhicule.
  - orientation : un entier représentant l'orientation du véhicule (0 pour horizontal, 1 pour vertical).
  - vehiculePrincipal : un booléen indiquant si le véhicule est le véhicule principal.
  - id : un entier représentant l'identifiant unique du véhicule. 

  **Variables Globales :**

  La classe Véhicule utilise la variable globale **uniId** pour générer des identifiants uniques pour chaque nouveau véhicule créé. La variable uniId est initialisée à 'a', et est incrémentée à chaque création de véhicule.


### <ins>Case</ins>

  La classe Véhicule dispose de deux constructeurs :

  - Case(std::string id) : Constructeur qui prend un identifiant en paramètre et initialise l'objet Case avec cet identifiant.
  - Case() : Constructeur par défaut qui initialise l'objet Case avec un identifiant vide.
  std::string id : Attribut qui stocke l'identifiant de la case.


### <ins>Position</ins>

  La structure "Position" a deux membres de données, "ligne" et "colonne", qui sont des entiers.



