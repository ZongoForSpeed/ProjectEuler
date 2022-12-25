#include "problemes.h"
#include "timer.h"

#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"

typedef int128_t nombre;

namespace {
    nombre f(const std::set<nombre> &premiers, nombre n) {
        std::map<nombre, size_t> d;
        arithmetique::decomposition(n, premiers, d);

        nombre resultat = 1;
        for (auto &e: d) {
            resultat *= puissance::puissance(e.first, e.second / 2);
        }
        return resultat;
    }

    nombre g2(std::map<nombre, nombre> &cache, const std::set<nombre> &premiers, nombre n) {
        if (premiers.contains(n)) {
            return 2 * n - 1;
        }

        if (auto it = cache.find(n);it != cache.end())
            return it->second;

        nombre sum = 0;

        auto diviseurs = arithmetique::diviseurs(n, premiers);
        for (nombre d: diviseurs) {
            sum += d * arithmetique::phi(n / d, premiers) * f(premiers, n / d);
        }

        cache.emplace(n, sum);
        return sum;
    }

    nombre g(std::map<nombre, nombre> &cache, const std::set<nombre> &premiers, nombre n) {
        if (n == 4) {
            return 6;
        }
        if (n % 2 == 1) {
            return -n;
        }

        if (premiers.contains(n >> 1)) {
            return n - 1;
        }

        nombre v = arithmetique::nombre_facteur(n, 2);
        nombre t = n >> v;

        nombre w = g2(cache, premiers, 1 << v) - (1 << v);
        if (t == 1) {
            return w;
        }

        std::map<nombre, size_t> d;
        arithmetique::decomposition(t, premiers, d);
        for (auto &e: d) {
            w *= g2(cache, premiers, puissance::puissance(e.first, e.second));
        }

        return w;
    }

    nombre G(std::map<nombre, nombre> &cache, const std::set<nombre> &premiers, nombre n) {
        nombre sum = 0;
        for (nombre k = 1; k <= n; ++k) {
            sum += g(cache, premiers, k);
        }

        return sum;
    }
}

ENREGISTRER_PROBLEME(795, "Alternating GCD Sum") {
    // For a positive integer n, the function g(n) is defined as
    //              g(n) = Sum_{i=1}^{n} (-1)^i gcd (n, i^2)
    //
    // For example, g(4) = -gcd(4,1^2) + gcd(4,2^2) - gcd(4,3^2) + gcd(4,4^2) = -1 + 4 - 1 + 4 = 6.
    //
    // You are also given g(1234) = 1233.
    //
    // Let $G(N) = sum_{n=1}^N g(n). You are given G(1234) = 2194708.
    //
    // Find G(12345678).
    std::set<nombre> premiers;
    premiers::crible235<nombre>(12345678, std::inserter(premiers, premiers.end()));

    std::map<nombre, nombre> cache;

    std::cout << "g(4) = " << g(cache, premiers, 4) << std::endl;
    std::cout << "g(2 * 47) = " << g(cache, premiers, 2 * 47) << std::endl;
    std::cout << "g(97) = " << g(cache, premiers, 97) << std::endl;
    std::cout << "g(3 * 31) = " << g(cache, premiers, 3 * 31) << std::endl;
    std::cout << "g(1234) = " << g(cache, premiers, 1234) << std::endl;

    std::cout << "G(100) = " << G(cache, premiers, 100) << std::endl;
    std::cout << "G(200) = " << G(cache, premiers, 200) << std::endl;
    std::cout << "G(300) = " << G(cache, premiers, 300) << std::endl;
    std::cout << "G(1234) = " << G(cache, premiers, 1234) << std::endl;

    return std::to_string(G(cache, premiers, 12'345'678));
}
