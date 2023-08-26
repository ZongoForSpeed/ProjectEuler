#include "problemes.h"
#include "timer.h"
#include "pythagoricien.h"
#include "racine.h"
#include "premiers.h"
#include "arithmetique.h"

namespace {
    size_t P(size_t limite) {
        size_t limite_crible = racine::racine_carre(limite + 1) + 1;

        std::vector<std::vector<size_t>> decomposition(limite_crible);
        {
            Timer t("Crible + décomposition");
            std::vector<size_t> premiers;
            premiers::crible235<size_t>(limite_crible, std::back_inserter(premiers));

            for (size_t p: premiers) {
                for (size_t q = p; q < limite_crible; q += p) {
                    decomposition[q].push_back(p);
                }
            }
        }

        size_t resultat = 0;
        for (size_t n = 2; n < limite_crible; n += 1) {
            const auto &d = decomposition[n];
            // n² + m² < limite et m < n
            // m² < limite - n² et m < n
            // m < sqrt(limite - n²) et m < n
            // m < min (sqrt(limite - n²), n)
            size_t m_max = std::min(n, racine::racine_carre(limite - n * n));

            if (n % 2 == 1) {
                m_max /= 2;
            }

            // Il faut calculer m - m/pi - m/pj ... + m/pi.pj ...
            size_t nb_facteur = d.size();
            size_t L_max = 1u << nb_facteur;
            size_t phi_m = m_max;
            for (size_t l = 1; l < L_max; ++l) {
                size_t L = l;
                size_t P = 1;
                size_t pos_d = 0;
                int compteur = std::popcount(L);
                while (L > 0) {
                    if ((L & 1u) == 1u) {
                        P *= d[pos_d];
                    }
                    ++pos_d;
                    L >>= 1u;
                }

                if (compteur % 2 == 1) {
                    phi_m -= m_max / P;
                } else {
                    phi_m += m_max / P;
                }
            }

            // std::cout << "Phi("<< n <<", "<< m_max <<") = " << phi_m << std::endl;
            // std::cout << "    " << n << " => " << phi_m << std::endl;
            resultat += phi_m;

        }

        std::cout << "P(" << limite << ") = " << resultat << std::endl;

        return resultat;
    }
}

ENREGISTRER_PROBLEME(540, "Counting primitive Pythagorean triples") {
    // A Pythagorean triple consists of three positive integers a, b and c satisfying a² + b² = c².
    // The triple is called primitive if a, b and c are relatively prime.
    // Let P(n) be the number of primitive Pythagorean triples with a < b < c < n.
    // For example P(20) = 3, since there are three triples: (3,4,5), (5,12,13) and (8,15,17).
    //
    // You are given that P(10^6) = 159139.
    //Find P(3141592653589793).
    size_t limite = 3'141'592'653'589'793;

    Pythagoricien pythagoricien(20);
    size_t compteur = 0;
    for (auto[a, b, c]: pythagoricien) {
        std::cout << a << ", " << b << ", " << c << std::endl;
        ++compteur;
    }
    std::cout << "P(20) = " << compteur << std::endl;

    P(20);
    P(1'000'000);
    size_t solution = P(limite);

    return std::to_string(solution);
}
