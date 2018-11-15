#include "problemes.h"
#include "numerique.h"
#include "utilitaires.h"
#include "combinatoire.h"

ENREGISTRER_PROBLEME(15, "Lattice paths") {
    // Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, 
    // there are exactly 6 routes to the bottom right corner.
    //
    // How many such routes are there through a 20×20 grid?
    return std::to_string(combinatoire::coefficient_binomial<uint128_t>(40, 20));
}
