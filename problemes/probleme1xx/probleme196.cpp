#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "polygonal.h"
#include "premiers.h"

typedef mpz_nombre nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

namespace {
    nombre triangle(const nombre &i, const nombre &j) {
        if (i == 0 || j == 0)
            return 0;

        if (i == 1 && j == 1)
            return 1;

        if (j > i)
            return 0;

        return polygonal::triangulaire<nombre>(i - 1) + j;
    }

    bool test(const nombre &i, const nombre &j) {
        nombre t_ij = triangle(i, j);
        if (t_ij % 2 == 0)
            return false;

        return premiers::miller_rabin(t_ij, 25);
        // return mpz_probab_prime_p(t_ij.get_data(), 25) != 0;
    }

    bool triplet_premier(const nombre &i, const nombre &j, bool recursif = false) {
        std::vector<paire> p;
        if (test(i + 1, j - 1)) p.emplace_back(i + 1, j - 1);
        if (test(i + 1, j)) p.emplace_back(i + 1, j);
        if (test(i + 1, j + 1)) p.emplace_back(i + 1, j + 1);
        if (test(i - 1, j - 1)) p.emplace_back(i - 1, j - 1);
        if (test(i - 1, j)) p.emplace_back(i - 1, j);
        if (test(i - 1, j + 1)) p.emplace_back(i - 1, j + 1);

        if (p.size() > 1)
            return true;

        if (recursif && p.size() == 1)
            return triplet_premier(p.front().first, p.front().second, false);

        return false;
    }

    nombre S(const nombre &ligne) {
        auto min = polygonal::triangulaire<nombre>(ligne - 1);
        auto max = polygonal::triangulaire<nombre>(ligne);

        // std::set<nombre> premiers;
        nombre resultat = 0;
        for (nombre premier = min;;) {
            premier = premiers::suivant(premier);
            if (premier > max)
                break;

            if (triplet_premier(ligne, premier - min, true))
                resultat += premier;
        }

        return resultat;
    }

}

ENREGISTRER_PROBLEME(196, "Prime triplets") {
    // Build a triangle from all positive integers in the following way:
    //
    //        1
    //        2  3
    //        4  5  6
    //        7  8  9 10
    //       11 12 13 14 15
    //       16 17 18 19 20 21
    //       22 23 24 25 26 27 28
    //       29 30 31 32 33 34 35 36
    //       37 38 39 40 41 42 43 44 45
    //       46 47 48 49 50 51 52 53 54 55
    //       56 57 58 59 60 61 62 63 64 65 66
    //       . . .
    //
    // Each positive integer has up to eight neighbours in the triangle.
    //
    // A set of three primes is called a prime triplet if one of the three primes has the other two as neighbours in the
    // triangle.
    //
    // For example, in the second row, the prime numbers 2 and 3 are elements of some prime triplet.
    //
    // If row 8 is considered, it contains two primes which are elements of some prime triplet, i.e. 29 and 31.
    // If row 9 is considered, it contains only one prime which is an element of some prime triplet: 37.
    //
    // Define S(n) as the sum of the primes in row n which are elements of any prime triplet. Then S(8)=60 and S(9)=37.
    //
    // You are given that S(10000)=950007619.
    //
    // Find  S(5678027) + S(7208785).
    std::cout << std::boolalpha;
    nombre resultat = S(5678027) + S(7208785);
    return std::to_string(resultat);
}
