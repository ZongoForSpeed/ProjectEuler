#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "chiffres.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// typedef boost::multiprecision::mpz_limite     nombre;

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(256, "Tatami-Free Rooms")
{
    // Tatami are rectangular mats, used to completely cover the floor of a room,
    // without overlap.
    //
    // Assuming that the only type of available tatami has dimensions 1×2, there
    // are obviously some limitations for the shape and size of the rooms that 
    // can be covered.
    //
    // For this problem, we consider only rectangular rooms with nombre    eger dimensions
    // a, b and even size s = a·b.
    // We use the term 'size' to denote the floor surface area of the room, and 
    // — without loss of generality — we add the condition a ≤ b.
    // 
    // There is one rule to follow when laying out tatami: there must be no ponombre    s
    // where corners of four different mats meet.
    // For example, consider the two arrangements below for a 4×4 room:
    //
    // p256_tatami3.gif
    // The arrangement on the left is acceptable, whereas the one on the right 
    // is not: a red "X" in the middle, marks the ponombre     where four tatami meet.
    //
    // Because of this rule, certain even-sized rooms cannot be covered with 
    // tatami: we call them tatami-free rooms.
    // Further, we define T(s) as the number of tatami-free rooms of size s.
    //
    // The smallest tatami-free room has size s = 70 and dimensions 7×10.
    // All the other rooms of size s = 70 can be covered with tatami; they are: 
    // 1×70, 2×35 and 5×14.
    // Hence, T(70) = 1.
    //
    // Similarly, we can verify that T(1320) = 5 because there are exactly 5 
    // tatami-free rooms of size s = 1320:
    // 20×66, 22×60, 24×55, 30×44 and 33×40.
    // In fact, s = 1320 is the smallest room-size s for which T(s) = 5.
    //
    // Find the smallest room-size s for which T(s) = 200.
    const nombre limite = puissance::puissance<nombre, unsigned>(10, 8);
    const nombre Q = 200;

    vecteur t(limite, 0);
    for (nombre a = 3; a * a < limite; ++a)
    {
        if (a % 2)
        {
            for (nombre r = 2; r < a / 2; ++r)
            for (nombre k = 1, b = a - 1 + 2 * r; k < r && a * b < limite; ++k)
            {
                t[a * b]++;
                b += a-1;
            }
        }
        else
        {
            for (nombre r = 3; r < a - 3; ++r)
            for (nombre k = 1, b = a + r, uk = std::min(r - 1, a - r - 2); k < uk && a * b < limite; ++k)
            {
                t[a * b]++;
                b += a;
            }
        }
    }
    
    nombre resultat = 0;
    for (nombre s = 2; s < limite; s += 2)
        if (t[s] == Q)
        {
            resultat = s;
            break;
        }
    
    return std::to_string(resultat);
}
