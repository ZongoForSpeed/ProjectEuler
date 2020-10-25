#include "problemes.h"
#include "timer.h"

typedef unsigned long long nombre;

namespace {
    nombre eulercoins(nombre modulo, nombre n) {
        nombre low = n;
        nombre high = n;
        nombre total = low;
        while (low > 0) {
            nombre suivant = (low + high) % modulo;
            if (suivant < low) {
                low = suivant;
                total += low;
            } else {
                high = suivant;
            }
        }
        return total;
    }
}

ENREGISTRER_PROBLEME(700, "Eulercoin") {
    // Leonhard Euler was born on 15 April 1707.
    //
    // Consider the sequence 1504170715041707n mod 4503599627370517.
    //
    // An element of this sequence is defined to be an Eulercoin if it is strictly smaller than all previously found
    // Eulercoins.
    //
    // For example, the first term is 1504170715041707 which is the first Eulercoin. The second term is 3008341430083414
    // which is greater than 1504170715041707 so is not an Eulercoin. However, the third term is 8912517754604 which is
    // small enough to be a new Eulercoin.
    //
    // The sum of the first 2 Eulercoins is therefore 1513083232796311.
    //
    //Find the sum of all Eulercoins.
    return std::to_string(eulercoins(4503599627370517, 1504170715041707));
}
