#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre maximum(const vecteur &fibonacci, const nombre &n) {
        for (const auto &f: boost::adaptors::reverse(fibonacci)) {
            if (f < n)
                return f;
        }

        return fibonacci.back();
    }

    nombre Zeckendorf(const vecteur &fibonacci, const nombre n) {
        if (n < 2)
            return 0;

        static std::map<nombre, nombre> cache;

        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;

        nombre m = maximum(fibonacci, n);

        nombre resultat = n - m + Zeckendorf(fibonacci, m) + Zeckendorf(fibonacci, n - m);

        cache[n] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(297, "Zeckendorf Representation") {
    // Each new term in the Fibonacci sequence is generated by adding the previous two terms. Starting with 1 and 2, the
    // first 10 terms will be: 1, 2, 3, 5, 8, 13, 21, 34, 55, 89.
    //
    // Every positive integer can be uniquely written as a sum of nonconsecutive terms of the Fibonacci sequence. For
    // example, 100 = 3 + 8 + 89. Such a sum is called the Zeckendorf representation of the number.
    //
    // For any integer n>0, let z(n) be the number of terms in the Zeckendorf representation of n.
    // Thus, z(5) = 1, z(14) = 2, z(100) = 3 etc.
    // Also, for 0<n<10**6, ∑ z(n) = 7894453.
    //
    // Find ∑ z(n) for 0<n<10**17.
    const auto limite = puissance::puissance<nombre, unsigned>(10, 17);
    vecteur fibonacci{1, 1};
    while (fibonacci.back() < limite) {
        fibonacci.push_back(fibonacci.back() + fibonacci.at(fibonacci.size() - 2));
    }

    nombre resultat = Zeckendorf(fibonacci, limite);
    return std::to_string(resultat);
}
