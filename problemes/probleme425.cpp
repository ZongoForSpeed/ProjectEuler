#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "chiffres.h"

#include <queue>
#include <unordered_map>

typedef std::priority_queue<std::pair<size_t, size_t>> queue;

namespace {
    void ajout_queue(queue &q, std::vector<size_t> &dp, size_t x, size_t d) {
        if (d < dp[x]) {
            dp[x] = d;
            q.emplace(std::numeric_limits<size_t>::max() - d, x);
        }
    }
}

ENREGISTRER_PROBLEME(425, "Prime connection") {
    // Two positive numbers A and B are said to be connected (denoted by "A ↔ B") if one of these conditions holds:
    //      (1) A and B have the same length and differ in exactly one digit; for example, 123 ↔ 173.
    //      (2) Adding one digit to the left of A (or B) makes B (or A); for example, 23 ↔ 223 and 123 ↔ 23.
    //
    // We call a prime P a 2's relative if there exists a chain of connected primes between 2 and P and no prime in the
    // chain exceeds P.
    //
    // For example, 127 is a 2's relative. One of the possible chains is shown below:
    // 2 ↔ 3 ↔ 13 ↔ 113 ↔ 103 ↔ 107 ↔ 127
    //
    // However, 11 and 103 are not 2's relatives.
    //
    // Let F(N) be the sum of the primes ≤ N which are not 2's relatives.
    //
    // We can verify that F(10**3) = 431 and F(10**4) = 78728.
    //
    // Find F(10**7).
    size_t limite = 10'000'000;

    std::vector<bool> premiers;
    premiers::crible_simple(limite, premiers);

    std::vector<size_t> dp(limite, std::numeric_limits<size_t>::max());

    queue q;
    ajout_queue(q, dp, 2, 2);

    std::vector<bool> visite(limite, false);

    while (!q.empty()) {
        size_t x = q.top().second;
        q.pop();
        if (visite[x]) continue;
        visite[x] = true;
        size_t d = dp[x];

        auto chiffres = chiffres::extraire_chiffres(x);

        size_t nombre_chiffres = chiffres.size();
        for (size_t i = 0; i < nombre_chiffres; ++i) {
            auto ai = chiffres[i];
            for (size_t j = 0; j < 10; ++j) {
                chiffres[i] = j;
                auto n = chiffres::conversion_nombre<size_t>(chiffres.begin(), chiffres.end());
                if (premiers[n]) ajout_queue(q, dp, n, std::max(n, d));
            }
            chiffres[i] = ai;
        }
        if (10 * x < limite) {
            chiffres.push_front(0);
            for (short i = 0; i < 9; ++i) {
                chiffres.front()++;
                auto n = chiffres::conversion_nombre<size_t>(chiffres.begin(), chiffres.end());
                if (premiers[n]) ajout_queue(q, dp, n, std::max(n, d));
            }
        }
    }

    size_t resultat = 0;
    for (size_t p = 0; p < limite; ++p) {
        if (premiers[p] && dp[p] > p) resultat += p;
    }

    return std::to_string(resultat);

}
