#include "problemes.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool trinary(nombre n) {
        while (n % 10 < 3 && n > 10) {
            n /= 10;
        }
        return n % 10 < 3;
    }

    nombre f(size_t n) {
        nombre base = 1;
        vecteur v;
        v.emplace_back(0);
        while (true) {
            vecteur tmp;
            for (size_t i = 1; i < 11; ++i) {
                for (const nombre &f : v) {
                    nombre m = i * base + f;
                    nombre mn = m * n;
                    if (trinary(mn))
                        return m;
                    else if (trinary(mn % base))
                        tmp.push_back(m);
                }
            }
            base *= 10;
            std::sort(tmp.begin(), tmp.end());
            std::swap(tmp, v);
        }
    }
}

ENREGISTRER_PROBLEME(303, "Multiples with small digits") {
    // For a positive integer n, define f(n) as the least positive multiple of n that, written in base 10, uses only
    // digits ≤ 2.
    //
    // Thus f(2)=2, f(3)=12, f(7)=21, f(42)=210, f(89)=1121222.
    // ∑
    // Also, ∑ n=1..100 f(n)/n = 11363107
    // 
    // Find ∑ n=1..10000 f(n)/n.
    size_t limite = 10000;
    nombre resultat = 0;
    for (size_t n = 1; n < limite + 1; ++n) {
        resultat += f(n);
    }
    return std::to_string(resultat);
}
