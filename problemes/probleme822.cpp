#include "problemes.h"
#include "arithmetique.h"
#include "format/deque.h"
#include "mpz_nombre.h"
#include "timer.h"
#include "premiers.h"
#include "utilitaires.h"

#include <execution>

typedef unsigned long long nombre;

namespace {
    mpz_nombre S_brute_force(size_t n, size_t m, size_t modulo = 1234567891L) {
        std::deque<mpz_nombre> list(n - 1);
        std::iota(list.begin(), list.end(), 2);
        std::cout << list << std::endl;
        for (size_t r = 1; r <= m; ++r) {
            mpz_nombre front = list.front();
            list.pop_front();
            list.push_back((front * front));
            std::ranges::sort(list);
            // std::cout << "After " << r << ": " << list << std::endl;
        }

        // std::cout << list << std::endl;
        mpz_nombre result = std::reduce(list.begin(), list.end()) % modulo;
        std::cout << "S(" << n << ", " << m << ") = " << result << std::endl;
        return result;
    }

    nombre S(const std::vector<nombre> &premiers, size_t n, size_t m, size_t modulo = 1234567891L) {
        std::deque<nombre> list(n - 1);
        std::iota(list.begin(), list.end(), 2);
        size_t tour = 1;
        size_t p = 0;
        bool search_cycle = true;
        while (tour <= m) {
            nombre front = list.front();
            if (search_cycle) {
                nombre back = list.back();
                auto log_front = std::log2(std::log2(front));
                auto log_back = std::log2(std::log2(back));
                if (log_back < log_front + 1) {
                    search_cycle = false;
                    std::cout << "Période trouvée après " << tour << " tours" << std::endl;
                    p = (m - tour) / list.size();
                    tour += p * list.size();
                    std::cout << "puissance à appliqué: " << p << std::endl;
                }
            }

            list.pop_front();
            list.push_back((front * front));
            std::ranges::sort(list);
            // std::cout << "After " << r << ": " << list << std::endl;

            ++tour;
        }

        auto phi = arithmetique::phi(modulo, premiers);

        auto exposant = puissance::puissance_modulaire<nombre>(2, p, phi);

        auto plus_mod = [modulo](nombre a, nombre b) {
            return (a + b) % modulo;
        };
        auto puissance_mod = [modulo, exposant](nombre e) -> nombre {
            return puissance::puissance_modulaire(e, exposant, modulo);
        };

        nombre result = std::transform_reduce(std::execution::par, list.begin(), list.end(), 0ULL,
                                              plus_mod,
                                              puissance_mod);

        std::cout << "S(" << n << ", " << m << ") = " << result << std::endl;
        return result;
    }

}


ENREGISTRER_PROBLEME(822, "Square the Smallest") {
    // A list initially contains the numbers 2, 3, ..., n.<br />
    // At each round, the smallest number in the list is replaced by its square. If there is more than one such number, then only one of them is replaced.
    // For example, below are the first three rounds for n = 5:
    //  [2, 3, 4, 5] --> [4, 3, 4, 5] --> [4, 9, 4, 5] --> [16, 9, 4, 5].
    //
    // Let S(n, m) be the sum of all numbers in the list after m rounds.
    //
    // For example, S(5, 3) = 16 + 9 + 4 + 5 = 34. Also S(10, 100) = 845339386 mod(1234567891).
    //
    // Find S(10^4, 10^{16}). Give your answer modulo 1234567891.
    std::vector<nombre> premiers;
    {
        Timer t("Crible");
        premiers::crible235<nombre>(1'000'000, std::back_inserter(premiers));
    }

    S_brute_force(5, 3);
    S_brute_force(10, 100);
    S(premiers, 10, 100);

    auto result = S(premiers, 10'000L, 10'000'000'000'000'000L);
    return std::to_string(result);
}
