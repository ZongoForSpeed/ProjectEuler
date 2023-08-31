#include "problemes.h"
#include "timer.h"

#include "arithmetique.h"
#include "chiffres.h"
#include "nombre_modulaire.h"

typedef size_t nombre;

namespace {
    size_t premier_chiffre(size_t N) {
        while (N >= 10) {
            N /= 10;
        }
        return N;
    }

    size_t D_brute_force(size_t N) {
        std::vector<size_t> cas1;
        std::vector<size_t> cas2;
        std::vector<size_t> cas3;
        std::vector<size_t> cas4;
        size_t result = 0;
        size_t limite = puissance::puissance<size_t>(10, N);
        for (size_t n = 1; n < limite; ++n) {
            std::map<size_t, size_t> digits;
            size_t count = 0;
            chiffres::boucle_chiffre(n, [&digits, &count](size_t d) {
                digits[d]++;
                count++;
            });
            bool dominating = false;
            size_t dominant = 10;
            for (auto &entry: digits) {
                if (2 * entry.second > count) {
                    dominating = true;
                    dominant = entry.first;
                    break;
                }
            }
            if (dominating) {
                // std::cout << n << std::endl;
                result++;
                if (digits.size() == 1) {
                    cas1.push_back(n);
                } else if (premier_chiffre(n) == dominant) {
                    cas2.push_back(n);
                } else if (dominant == 0) {
                    cas4.push_back(n);
                } else {
                    cas3.push_back(n);
                }
            }
        }

        // std::cout << "Cas 1 = " << cas1 << " => " << cas1.size() << std::endl;
        // std::cout << "Cas 2 = " << cas2 << " => " << cas2.size() << std::endl;
        // std::cout << "Cas 3 = " << cas3 << " => " << cas3.size() << std::endl;
        // std::cout << "Cas 4 = " << cas4 << " => " << cas4.size() << std::endl;
        return result;
    }

    std::pair<size_t, nombre_modulaire> factoriel(std::map<size_t, std::pair<size_t, nombre_modulaire>> & cache_factoriel, size_t modulo, size_t n) {
        auto it = cache_factoriel.find(n);
        if (it != cache_factoriel.end()) {
            return it->second;
        }

        auto f = nombre_modulaire::factoriel2(modulo, n);
        cache_factoriel.emplace(n, f);
        return f;
    }

    nombre_modulaire coefficient_binomial(std::map<size_t, std::pair<size_t, nombre_modulaire>> & cache_factoriel,
                                          size_t modulo, size_t n, size_t k) {
        auto fn = factoriel(cache_factoriel, modulo, n);
        auto fk = factoriel(cache_factoriel, modulo, k);
        auto fnk = factoriel(cache_factoriel, modulo, n - k);
        if (fn.first - fk.first - fnk.first > 0)
            return nombre_modulaire(modulo, 0);
        return fn.second / (fk.second * fnk.second);
    }

    size_t D(size_t N) {
        std::map<size_t, std::pair<size_t, nombre_modulaire>> cache_factoriel;
        size_t modulo = 1'000'000'007;

        nombre_modulaire result(modulo, 0);

        // i est le nombre d'occurrence de d dans le nombre
        for (size_t i = 1; i <= N; ++i) {

            // Cas dddddddd, tous les chiffres sont identiques (d=0 est exclu de ce cas)
            result += 9;

            // Nombre maximeum de chiffres différents de d que l'on peut ajouter
            auto autre_chiffre = std::min(N - i, i - 1);

            for (size_t t = 1; t <= autre_chiffre; ++t) {
                auto taille_nombre = t + i;
                {
                    // Position possible pour d, sachant que le premier chiffre est d
                    auto C = coefficient_binomial(cache_factoriel, modulo, taille_nombre - 1, i - 1);

                    // Nombres de longueur t ne contenant pas de d
                    auto P = puissance::puissance_modulaire<size_t>(9, t, modulo);

                    // Cas dXXXXXXXXX (d=0 est exclu de ce cas)
                    result += 9 * C * P;
                }

                {
                    // Position possible pour d, sachant que le premier chiffre n'est pas d
                    auto C = coefficient_binomial(cache_factoriel, modulo, taille_nombre - 1, i);

                    // Nombres de longueur t ne commançant ni par 0 ni par d
                    auto P = 8 * puissance::puissance_modulaire<size_t>(9, t - 1, modulo);

                    // Cas X...dXXXXX (d=0 est exclu de ce cas)
                    result += 9 * C * P;
                }

                {
                    // Position possible pour d, sachant que le premier chiffre n'est pas d
                    auto C = coefficient_binomial(cache_factoriel, modulo, taille_nombre - 1, i);

                    // Nombres de longueur t ne commançant ni par 0 ni par d
                    auto P = puissance::puissance_modulaire<size_t>(9, t, modulo);

                    // Cas X...0XXXXX (d est egale à 0)
                    result += C * P;
                }
            }
        }

        return result.value();
    }
}

ENREGISTRER_PROBLEME(788, "Dominating Numbers") {
    // A dominating number is a positive integer that has more than half of its digits equal.
    //
    // For example, 2022 is a dominating number because three of its four digits are equal to 2.
    // But 2021 is not a dominating number.
    //
    // Let D(N) be how many dominating numbers are less than 10^N.
    //
    // For example, D(4) = 603 and D(10) = 21893256.
    //
    // Find D(2022). Give your answer modulo 1\,000\,000\,007.
    std::cout << "D(3) = " << D_brute_force(3) << std::endl;
    std::cout << "D(3) = " << D(3) << std::endl;
    std::cout << "D(4) = " << D_brute_force(4) << std::endl;
    std::cout << "D(4) = " << D(4) << std::endl;
    std::cout << "D(10) = " << D(10) << std::endl;
    return std::to_string(D(2022));
}
