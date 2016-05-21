#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "matrice.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(213, "Flea Circus")
{
    // A 30×30 grid of squares contains 900 fleas, initially one flea per square.
    // When a bell is rung, each flea jumps to an adjacent square at random (usually 4 possibilities, 
    // except for fleas on the edge of the grid or at the corners).
    // 
    // What is the expected number of unoccupied squares after 50 rings of the bell? Give your answer
    // rounded to six decimal places.
    nombre taille = 30;
    
    matrice::matrice<long double> I(taille*taille, taille*taille, 0.0);
    for (size_t n = 0; n < taille*taille; ++n)
        I(n,n) = 1.0;
    
    matrice::matrice<long double> A(taille*taille, taille*taille);
    for (size_t i = 0; i < taille; ++i)
    for (size_t j = 0; j < taille; ++j)
    {
        nombre ij = i*taille + j;
        vecteur adjacents;
        if (i > 0)
            adjacents.push_back((i - 1)*taille + j);
        if (j > 0)
            adjacents.push_back(i*taille + j - 1);
        if (i < taille - 1)
            adjacents.push_back((i + 1)*taille + j);
        if (j < taille - 1)
            adjacents.push_back(i*taille + j + 1);
            
        for (auto a: adjacents)
            A(ij, a) = 1.0 / adjacents.size();
    }
    
    auto An = matrice::puissance_matrice(A, 50);

    long double resultat = 0.0;
    for (size_t j = 0; j < An.size2(); ++j)
    {
        long double e = 1.0;
        for (size_t i = 0; i < An.size1(); ++i)
            e *= 1.0 - An(i, j);
        resultat += e;
    }
    
    std::cout << std::setprecision(9);
    std::cout << "Solution: " << resultat << std::endl;
}
