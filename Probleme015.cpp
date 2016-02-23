#include "Problemes.h"
#include "Arithmetiques.h"
#include "Combinatoire.h"
#include "Timer.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

ENREGISTRER_PROBLEME(15, "Lattice paths")
{
    Timer t("probleme 15");
    // Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, 
    // there are exactly 6 routes to the bottom right corner.
    //
    // How many such routes are there through a 20×20 grid?
    std::cout << "Solution: " << combinatoire::coefficient_binomial<nombre>(40, 20) << std::endl;
}
