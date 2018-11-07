#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

namespace {
    bool addition(std::vector<size_t> &P, size_t somme, size_t b, size_t amax) {
        if (somme < P.size())
            P[somme]++;
        else
            return false;
        for (size_t a = 1;;) {
            if (a < amax && addition(P, somme + a * b, b * 3, a))
                a *= 2;
            else if (a > 1) {
                b *= 3;
                a = 1;
            } else
                return true;
        }
    }

}

ENREGISTRER_PROBLEME(333, "Special partitions") {
    // All positive integers can be partitioned in such a way that each and every term of the partition can be expressed
    // as 2ix3j, where i,j ≥ 0.
    //
    // Let's consider only those such partitions where none of the terms can divide any of the other terms. 
    // For example, the partition of 17 = 2 + 6 + 9 = (21x30 + 21x31 + 20x32) would not be valid since 2 can divide 6.
    // Neither would the partition 17 = 16 + 1 = (24x30 + 20x30) since 1 can divide 16. The only valid partition of 17 
    // would be 8 + 9 = (23x30 + 20x32).
    //
    // Many integers have more than one valid partition, the first being 11 having the following two partitions. 
    // 11 = 2 + 9 = (21x30 + 20x32) 
    // 11 = 8 + 3 = (23x30 + 20x31)
    //
    // Let's define P(n) as the number of valid partitions of n. For example, P(11) = 2.
    //
    // Let's consider only the prime integers q which would have a single valid partition such as P(17).
    //
    // The sum of the primes q <100 such that P(q)=1 equals 233.
    //
    // Find the sum of the primes q <1000000 such that P(q)=1.
    // const size_t L2 = 20;
    // const size_t L3 = 13;
    const size_t limite = 1'000'000;

    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite, std::back_inserter(premiers));

    std::vector<size_t> P(limite, 0);
    addition(P, 0, 1, limite);

    size_t resultat = 0;
    for (auto p: premiers) {
        if (P[p] == 1) {
            resultat += p;
        }
    }
    return std::to_string(resultat);
}
