#include "../problemes.h"
#include "arithmetique.h"

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre covers(nombre m, nombre n, nombre racine) {
        nombre p = 1;
        while (n >= p) {
            p *= racine;
        }

        nombre m1 = m;
        nombre n1 = n;
        nombre result = m / p;
        // m is not counted as a covering, but we need to count certain lesser
        // values depending on whether the digits processed so far would be
        bool coveredAtLimit = true;
        while (p > 1) {
            m1 %= p;
            n1 %= p;
            p /= racine;
            nombre md = m1 / p;
            nombre nd = n1 / p;
            result *= racine - nd;
            if (coveredAtLimit) {
                if (md >= nd) {
                    result += md - nd;
                } else {
                    coveredAtLimit = false;
                }
            }
        }
        return result;
    }

    /** Value to be added to i to get to the next cover */
    nombre increment(nombre i, nombre n, nombre racine) {
        nombre d = 1;
        nombre result = 0;
        nombre max = 0;
        while (n > 0) {
            nombre md = i % racine;
            nombre nd = n % racine;
            result += (nd - md) * d;

            d *= racine;
            i /= racine;
            n /= racine;
            if (result > max) {
                max = result;
            }
        }
        // result <= 0, no increment necessary
        return max;
    }

    /** Counts the coefficients divisible by neither 2 nor 5 */
    nombre intersection(nombre m, nombre n) {
        nombre count = 0;
        for (nombre i = n; i < m;) {
            i += increment(i, n, 5);
            nombre diff = increment(i, n, 2);
            if (diff == 0) {
                ++count;
                ++i;
            } else {
                i += diff;
            }
        }
        std::cout << "counted " << count << std::endl;
        return count;
    }
}

ENREGISTRER_PROBLEME(322, "Binomial coefficients divisible by 10") {
    // Let T(m, n) be the number of the binomial coefficients iCn that are divisible by 10 for n ≤ i < m
    // (i, m and n are positive integers).
    // You are given that T(10**9, 10**7-10) = 989697000.
    //
    // Find T(10**18, 10**12-10).
    const auto m = puissance::puissance<nombre>(10, 18u);
    const auto n = puissance::puissance<nombre>(10, 12u) - 10;

    nombre resultat = m - n;
    resultat -= covers(m, n, 5);
    resultat -= covers(m, n, 2);
    resultat += intersection(m, n);

    return std::to_string(resultat);
}
