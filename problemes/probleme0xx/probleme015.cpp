#include "problemes.h"
#include "utilitaires.h"
#include "combinatoire.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(15, "Lattice paths") {
    // Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, 
    // there are exactly 6 routes to the bottom right corner.
    //
    // How many such routes are there through a 20×20 grid?
    return combinatoire::coefficient_binomial<nombre>(40, 20).convert_to<std::string>();
}
