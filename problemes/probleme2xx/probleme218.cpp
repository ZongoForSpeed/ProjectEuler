#include "problemes.h"
#include "arithmetiques.h"
#include "mp_nombre.h"
#include "pythagoricien.h"

ENREGISTRER_PROBLEME(218, "Perfect right-angled triangles") {
    // Consider the right angled triangle with sides a=7, b=24 and c=25. The area of this triangle is 84, which is
    // divisible by the perfect numbers 6 and 28.
    // Moreover it is a primitive right angled triangle as gcd(a,b)=1 and gcd(b,c)=1.
    // Also c is a perfect square.
    //
    // We will call a right angled triangle perfect if
    // -it is a primitive right angled triangle
    // -its hypotenuse is a perfect square
    //
    // We will call a right angled triangle super-perfect if
    // -it is a perfect right angled triangle and
    // -its area is a multiple of the perfect numbers 6 and 28.
    //
    // How many perfect right-angled triangles with c ≤ 10^16 exist that are not super-perfect?
    const auto limite = puissance::puissance<size_t, unsigned>(10, 8);

    mp_nombre resultat = 0;
    Pythagoricien pythagoricien(limite);
    for (const auto t: pythagoricien) {
        mp_nombre x, y, z;
        std::tie(x, y, z) = t;
        mp_nombre a = y * y - x * x;
        mp_nombre b = 2 * x * y;
        // mp_nombre c = z*z;

        mp_nombre A = a * b / 2;
        if (A % 6 != 0 || A % 28 != 0)
            ++resultat;
    }

    return resultat.to_string();
}
