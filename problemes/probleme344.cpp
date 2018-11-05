#include <maths/multidimension.h>
#include "problemes.h"
#include "premiers.h"
#include "puissance.h"

#include "arithmetiques.h"
#include "arithmetiques_modulaire.h"

using arithmetiques::nombre_modulaire;

namespace {

    template<size_t modulo>
    class Algorithme {
        size_t n;
        size_t m;

        std::vector<size_t> exposant_factoriels;
        std::vector<nombre_modulaire<modulo>> factoriels;
        std::vector<nombre_modulaire<modulo>> inverses;

        nombre_modulaire<modulo> coefficient_binomial(size_t p, size_t k) {
            const auto & fp = factoriels[p];
            const auto & fk = inverses[factoriels[k].value()];
            const auto & fpk = inverses[factoriels[p - k].value()];
            if (exposant_factoriels[p] - exposant_factoriels[k] - exposant_factoriels[p - k] > 0)
                return 0;

            return fp * fk * fpk;
        }

    public:
        Algorithme(size_t n_, size_t m_) : n(n_), m(m_), exposant_factoriels(n + 1), factoriels(n + 1), inverses(modulo) {
            for (size_t i = 0; i < n_ + 1; ++i) {
                auto f2 = nombre_modulaire<modulo>::factoriel2(i);
                exposant_factoriels[i] = f2.first;
                factoriels[i] = f2.second;
            }

            for (size_t i = 0; i < modulo; ++i) {
                inverses[i] = 1 / nombre_modulaire<modulo>(i);
            }
        }
        void dp(std::vector<nombre_modulaire<modulo>> &f, size_t p) {
            f[0] = 1;
            for (size_t b1 = 0; b1 < 21; ++b1) {
                auto b = 20 - b1;
                // 2^b > n
                for (size_t i = n; i; --i) {
                    for (size_t j = 2; j <= p && (j << b) <= i; j += 2) {
                        f[i] += f[i - (j << b)] * coefficient_binomial(p, j);
                    }
                }
            }
        }

        size_t W() {
            auto total = coefficient_binomial(n, m + 1) * (m + 1);
            // zz_p total = cb(n, m + 1) * (m + 1);

            std::vector<nombre_modulaire<modulo>> f(n + 10, 0);
            std::vector<nombre_modulaire<modulo>> g(n + 10, 0);
            dp(f, m / 2 + 1);
            dp(g, m / 2);

            auto ans = total;
            for (size_t i = 0; i <= n - m; ++i) { // silver is the second one
                ans -= coefficient_binomial(n - 1 - m / 2 - i, m / 2) * f[i];
            }

            for (size_t i = 1; i <= n - m + 1; ++i) { // silver is behind the second one
                ans -= coefficient_binomial(n - m / 2 - i, m / 2) * (f[i] - g[i]) * (m - 1);
            }

            return ans.value();
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
    // std::vector<size_t> premiers;
    // premiers::crible235<size_t>(10000000UL, std::back_inserter(premiers));
    const size_t n = 1000000;
    const size_t m = 100;

    size_t resultat = 65579304332;
    size_t resultat_1000003 = Algorithme<1000003>(n, m).W();
    std::cout << resultat_1000003 << std::endl;
    std::cout << (resultat % 1000003) << std::endl;

    size_t resultat_1000033 = Algorithme<1000033>(n, m).W();
    std::cout << resultat_1000033 << std::endl;
    std::cout << (resultat % 1000033) << std::endl;

    std::vector<long long> modulos {1000003, 1000033};
    std::vector<long long> restes {static_cast<long long>(resultat_1000003), static_cast<long long>(resultat_1000033)};

    long long resultat2 = arithmetiques::restes_chinois<long long>(modulos, restes);
    std::cout << resultat2 << std::endl;
    std::cout << (resultat % (1000003UL * 1000033UL)) << std::endl;

    return std::to_string(resultat2);
}
