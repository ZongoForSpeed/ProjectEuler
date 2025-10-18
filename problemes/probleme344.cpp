#include "problemes.h"
#include "premiers.h"
#include "puissance.h"

#include "arithmetique_modulaire.h"
#include "multidimension.h"
#include "combinatoire.h"

namespace {
    class Euler344 {
    private:
        size_t pennies;    // Numbers of pennies
        size_t length;     // Strip length
        size_t modulo;
        multidimension<size_t, 2> cache_binomial;

        size_t coefficient_binomial(size_t n, size_t k) {
            if (cache_binomial[(k / 2)][n] == std::numeric_limits<size_t>::max()) {
                cache_binomial[(k / 2)][n] = combinatoire::coefficient_binomial_ul(n, k, modulo);
            }
            return cache_binomial[(k / 2)][n];
        }

        size_t recursion(multidimension<size_t, 2> &cache, size_t segments, size_t extra, size_t free, size_t shift) {
            size_t bit = 1ul << shift;
            if (2 * bit > free) return coefficient_binomial(free + extra, extra);
            if (cache[shift][free] != 0) {
                return cache[shift][free];
            }
            size_t somme = 0;

            for (size_t i = 0; i * bit <= free && i <= segments; i += 2) {
                somme += recursion(cache, segments, extra, free - i * bit, shift + 1) *
                         coefficient_binomial(segments, i);
                somme %= modulo;
            }

            cache[shift][free] = somme;
            return somme;
        }

    public:
        Euler344(size_t p, size_t l, size_t m) : pennies(p), length(l), modulo(m) {
            multidimension<size_t, 2> cache(pennies / 4 + 1, length - pennies / 2 + 1,
                                            std::numeric_limits<size_t>::max());
            std::swap(cache_binomial, cache);
        }

        size_t W() {
            // total
            size_t total = (pennies + 1) * combinatoire::coefficient_binomial_ul(length, pennies + 1, modulo);

            multidimension<size_t, 2> cache(20u, length, 0u);

            // dollar en 2ème position (cas perdants)
            total += modulo - recursion(cache, pennies / 2 + 1, pennies / 2, length - pennies - 1, 0);

            // dollar en 3ème position (ajout 1 à longueur)
            total -= (pennies - 1) * recursion(cache, pennies / 2 + 1, pennies / 2, length - pennies, 0);
            multidimension<size_t, 2> cache2(20u, length, 0u);

            // cas commençants par "0" for dollar 3rd+ positions
            total += (pennies - 1) * recursion(cache2, pennies / 2, pennies / 2, length - pennies, 0);
            return (total + pennies * modulo) % modulo;
        }
    };
}

ENREGISTRER_PROBLEME(344, "Silver dollar game") {
    // One variant of N.G. de Bruijn's silver dollar game can be described as follows:
    //
    // On a strip of squares a number of coins are placed, at most one coin per square. Only one coin, called the silver
    // dollar, has any value. Two players take turns making moves. At each turn a player must make either a regular or
    // a special move.
    //
    // A regular move consists of selecting one coin and moving it one or more squares to the left. The coin cannot move
    // out of the strip or jump on or over another coin.
    //
    // Alternatively, the player can choose to make the special move of pocketing the leftmost coin rather than making a
    // regular move. If no regular moves are possible, the player is forced to pocket the leftmost coin.
    //
    // The winner is the player who pockets the silver dollar.
    //
    // p344_silverdollar.gif
    // A winning configuration is an arrangement of coins on the strip where the first player can force a win no matter
    // what the second player does.
    //
    // Let W(n,c) be the number of winning configurations for a strip of n squares, c worthless coins and one silver
    // dollar.
    //
    // You are given that W(10,2) = 324 and W(100,10) = 1514704946113500.
    //
    // Find W(1 000 000, 100) modulo the semiprime 1000 036 000 099 (= 1 000 003 · 1 000 033).
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(10'000'000, std::back_inserter(premiers));

    size_t pennies = 100;
    size_t length = 1'000'000;

    size_t modulo1 = 1'000'003;
    size_t modulo2 = 1'000'033;

    size_t resultat1 = Euler344(pennies, length, modulo1).W();
    size_t resultat2 = Euler344(pennies, length, modulo2).W();

    const std::vector<size_t> modulos{modulo1, modulo2};
    const std::vector<size_t> restes{resultat1, resultat2};

    auto resultat = arithmetique_modulaire::restes_chinois<size_t>(modulos, restes, premiers);
    return std::to_string(resultat);
}
