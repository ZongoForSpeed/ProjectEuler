#include "problemes.h"
#include "combinatoire.h"
#include "utilitaires.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

ENREGISTRER_PROBLEME(15, "Lattice paths")
{
    // Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, 
    // there are exactly 6 routes to the bottom right corner.
    //
    // How many such routes are there through a 20×20 grid?
    return std::to_string(combinatoire::coefficient_binomial<nombre>(40, 20));
}
