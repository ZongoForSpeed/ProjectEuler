#include "../problemes.h"
#include "matrice.h"

typedef long long int nombre;

namespace {
    std::pair<size_t, size_t> min_compteur_cost(std::map<size_t, std::pair<size_t, size_t>> cache, size_t n) {
        if (n < 2)
            return std::make_pair(0, 0);

        auto it = cache.find(n);
        if (it != cache.end()) {
            return it->second;
        }

        size_t min_compteur = std::numeric_limits<size_t>::max();
        size_t min_cost = std::numeric_limits<size_t>::max();
        for (size_t i = 1; i <= n; i++) {
            auto c1 = min_compteur_cost(cache, i - 1);
            auto c2_ = min_compteur_cost(cache, n - i);
            auto c2 = std::make_pair(c2_.first, c2_.second + c2_.first * i);
            size_t compteur;
            size_t cost;
            if (c1.first > c2.first) {
                compteur = c1.first;
                cost = c1.second;
            } else if (c2.first > c1.first) {
                compteur = c2.first;
                cost = c2.second;
            } else {
                compteur = c1.first;
                cost = std::max(c1.second, c2.second);
            }
            compteur += 1;
            cost += i;
            if (compteur < min_compteur) {
                min_compteur = compteur;
                min_cost = cost;
            } else if (compteur == min_compteur) {
                min_compteur = compteur;
                min_cost = std::min(min_cost, cost);
            }
        }

        auto resultat = std::make_pair(min_compteur, min_cost);
        cache.emplace(n, resultat);
        return resultat;
    }

    size_t
    cost(std::map<size_t, std::pair<size_t, size_t>> &cache, const std::vector<size_t> &costs, size_t n, size_t d) {
        auto mmc = min_compteur_cost(cache, n - d);
        size_t c = d * mmc.first + mmc.second;
        return d + std::max(costs[d - 1], c);
    }
}

ENREGISTRER_PROBLEME(328, "Lowest-cost Search") {
    // We are trying to find a hidden number selected from the set of size_tegers {1, 2, ..., n} by asking questions. 
    // Each number (question) we ask, has a cost equal to the number asked and we get one of three possible answers:
    // 
    // "Your guess is lower than the hidden number", or
    // "Yes, that's it!", or
    // "Your guess is higher than the hidden number".
    // Given the value of n, an optimal strategy minimizes the total cost (i.e. the sum of all the questions asked)
    // for the worst possible case. E.g.
    //
    // If n=3, the best we can do is obviously to ask the number "2". The answer will immediately lead us to find 
    // the hidden number (at a total cost = 2).
    //
    // If n=8, we might decide to use a "binary search" type of strategy: Our first question would be "4" and if the
    // hidden number is higher than 4 we will need one or two additional questions.
    // Let our second question be "6". If the hidden number is still higher than 6, we will need a third question 
    // in order to discriminate between 7 and 8.
    //
    // Thus, our third question will be "7" and the total cost for this worst-case scenario will be 4+6+7=17.
    //
    // We can improve considerably the worst-case cost for n=8, by asking "5" as our first question.
    // If we are told that the hidden number is higher than 5, our second question will be "7", then we'll know for 
    // certain what the hidden number is (for a total cost of 5+7=12).
    // If we are told that the hidden number is lower than 5, our second question will be "3" and if the hidden number
    // is lower than 3 our third question will be "1", giving a total cost of 5+3+1=9.
    // Since 12>9, the worst-case cost for this strategy is 12. That's better than what we achieved previously with 
    // the "binary search" strategy; it is also better than or equal to any other strategy.
    // So, in fact, we have just described an optimal strategy for n=8.

    // Let C(n) be the worst-case cost achieved by an optimal strategy for n, as described above.
    // Thus C(1) = 0, C(2) = 1, C(3) = 2 and C(8) = 12.
    // Similarly, C(100) = 400 and Sum n=1..100 C(n) = 17575.
    //
    // Find Sum n=1..200000 C(n).
    const size_t T = 200000;

    std::vector<size_t> costs(T + 1, 0);

    std::map<size_t, std::pair<size_t, size_t>> cache;

    size_t resultat = 0;
    size_t divider = 1;
    size_t div_offset = 1;
    for (size_t i = 2; i <= T; ++i) {
        size_t c = cost(cache, costs, i, divider);
        for (size_t off = 1; off <= 2 * div_offset; off <<= 1) {
            if (off > divider) {
                break;
            }
            size_t d = divider - off;
            size_t c2 = cost(cache, costs, i, d);
            if (c2 <= c) {
                c = c2;
                divider = d;
                div_offset = std::max(div_offset, off);
            }
        }
        costs[i] = c;
        resultat += c;
        ++divider;
    }
    return std::to_string(resultat);
}
