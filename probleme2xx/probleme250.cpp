#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(250, "250250") {
    // Find the number of non-empty subsets of {1^1, 2^2, 3^3,..., 250250^250250}, the sum of whose elements is
    // divisible by 250. Enter the rightmost 16 digits as your answer.
    auto masque = puissance::puissance<nombre, unsigned>(10, 16);

    nombre m = 250;
    vecteur frequence(m, 0);
    for (nombre i = 1; i <= 250250; ++i) {
        frequence[puissance::puissance_modulaire<nombre>(i, i, m)] += 1;
    }

    vecteur dp(m, 0);
    dp[0] = 1;
    for (nombre i = 0; i < m; ++i)
        for (nombre j = 0; j < frequence[i]; ++j) {
            vecteur temp(m, 0);
            for (nombre k = 0; k < m; ++k)
                temp[k] = (dp[k] + dp[(m + k - i) % m]) % masque;
            std::swap(dp, temp);
        }

    nombre resultat = dp.front() - 1;
    return std::to_string(resultat);
}
