#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(116, "Red, green or blue tiles") {
    // A row of five black square tiles is to have a number of its tiles replaced with coloured oblong tiles chosen from
    // red (length two), green (length three), or blue (length four).
    //
    // If red tiles are chosen there are exactly seven ways this can be done.
    // If green tiles are chosen there are three ways.
    // And if blue tiles are chosen there are two ways.
    //
    // Assuming that colours cannot be mixed there are 7 + 3 + 2 = 12 ways of replacing the black tiles in a row
    // measuring five units in length.
    // 
    // How many different ways can the black tiles in a row measuring fifty units in length be replaced if colours
    // cannot be mixed and at least one coloured tile must be used?
    //
    // NOTE: This is related to Problem 117.
    nombre longueur = 50;
    nombre resultat = 0;
    for (nombre couleur = 2; couleur < 5; ++couleur) {
        vecteur valeur(couleur, 0);
        for (nombre j = couleur, base = 1; j < longueur + 1; ++j, ++base)
            valeur.push_back(valeur[j - 1] + base + valeur[j - couleur]);

        resultat += valeur[longueur] - valeur[longueur - 1];
    }
    return std::to_string(resultat);
}
