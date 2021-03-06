#include "problemes.h"
#include "polygonal.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(94, "Almost equilateral triangles") {
    // It is easily proved that no equilateral triangle exists with integral length sides and integral area. However,
    // the almost equilateral triangle 5-5-6 has an area of 12 square units.
    //
    // We shall define an almost equilateral triangle to be a triangle for which two sides are equal and the third
    // differs by no more than one unit.
    // 
    // Find the sum of the perimeters of all almost equilateral triangles with integral side lengths and area and whose
    // perimeters do not exceed one billion (1,000,000,000).
    nombre limite = 1000000000;
    nombre resultat = 0;
    for (nombre k = 1; 6 * k + 2 < limite; ++k) {
        if (polygonal::est_carre(3 * k * k + 2 * k)) {
            resultat += 6 * k + 4;
        }
        if (polygonal::est_carre(3 * k * k + 4 * k + 1)) {
            resultat += 6 * k + 2;
        }
    }
    return std::to_string(resultat);
}
