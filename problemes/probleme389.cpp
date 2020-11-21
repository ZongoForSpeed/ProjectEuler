#include "problemes.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

// namespace {
//     size_t dp(size_t n, size_t d, std::vector<long double> & probabilites) {
//         size_t nd = n * d;
//         std::vector<long double> f(nd + 1, 0);
//         std::vector<long double> temp(nd + 1, 0);
//         f[0] = 1;
//         for (size_t i = 1; i < n + 1; ++i) {
//             for (size_t jj = 0; jj < nd + 1; ++jj) {
//                 size_t j = nd - jj;
//                 f[j] = 0;
//                 for (size_t k = 1; k <= d && k <= j; ++k)
//                     f[j] += f[j - k] / d;
//             }
//             for (size_t j = 1 * i; j < d * i + 1; ++j)
//                 temp[j] += f[j] * probabilites[i];
//         }
//         std::swap(probabilites, temp);
//         return nd;
//     }
// }

ENREGISTRER_PROBLEME(389, "Platonic Dice") {
    // An unbiased single 4-sided die is thrown and its value, T, is noted.
    // T unbiased 6-sided dice are thrown and their scores are added together. The sum, C, is noted.
    // C unbiased 8-sided dice are thrown and their scores are added together. The sum, O, is noted.
    // O unbiased 12-sided dice are thrown and their scores are added together. The sum, D, is noted.
    // D unbiased 20-sided dice are thrown and their scores are added together. The sum, I, is noted.
    // Find the variance of I, and give your answer rounded to 4 decimal places.
    long double e = 1;
    std::vector<short> dices {4,6,8,12,20};
    for (auto d: dices) {
        e = e * (d + 1) / 2;
    }
    
    long double variance = e * (e-1) / 3;
    return std::to_fixed(variance, 4);
    // std::cout << std::to_string(variance, 4) << std::endl;
    
    // std::vector<long double> probabilites {0, 1};
    // size_t n = 1;
    // n = dp(n, 4, probabilites);
    // n = dp(n, 6, probabilites);
    // n = dp(n, 8, probabilites);
    // n = dp(n, 12, probabilites);
    // n = dp(n, 20, probabilites);
    
    // long double esperance = 0;
    // long double somme_carre = 0;
    // for (size_t i = 0; i <= n; ++i) {
    //     esperance += probabilites[i] * i;
    //     somme_carre += probabilites[i] * i * i;
    // }
    // long double resultat = somme_carre - esperance * esperance;
    // return std::to_string(resultat, 4);
}
