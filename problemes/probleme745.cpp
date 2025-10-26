#include "problemes.h"
#include "numerique.h"
#include "premiers.h"
#include "timer.h"
#include "arithmetique.h"

namespace {
    size_t g(const std::vector<size_t> &premiers, size_t n) {
        std::map<size_t, size_t> d;
        arithmetique::decomposition(n, premiers, d);
        size_t resultat = 1;
        for (auto [key, value]: d) {
            resultat *= puissance::puissance(key, value - (value & 1));
        }

        return resultat;
    }

    size_t S(const std::vector<size_t> &premiers, size_t N) {
        size_t resultat = 0;

        for (size_t n = 1; n <= N; ++n) {
            resultat += g(premiers, n);
        }

        return resultat;
    }

    // https://en.wikipedia.org/wiki/Square-free_integer#Distribution
    size_t Q(const std::vector<short> &moebius, size_t N) {
        // Q(N) = sum(k=1,sqrt(N),floor(N/k^2)*moebius(k))
        size_t square_free_p = 0;
        size_t square_free_n = 0;
        for (size_t k = 1; k * k <= N; ++k) {
            switch (moebius[k]) {
                case 1:
                    square_free_p += N / (k * k);
                    break;
                case -1:
                    square_free_n += N / (k * k);
                    break;
                case 0:
                default:
                    break;
            }
        }

        return square_free_p - square_free_n;
    }

}

ENREGISTRER_PROBLEME(745, "Sum of Squares") {
    // For a positive integer, n, define g(n) to be the maximum perfect square that divides n.
    // For example, g(18) = 9, g(19) = 1.
    //
    // Also define S(N) = sum_{n=1}^N g(n)
    //
    // For example, S(10) = 24 and S(100) = 767.
    //
    // Find S(10^{14}). Give your answer modulo 1\,000\,000\,007.
    std::vector<size_t> premiers;
    {
        Timer t("Crible235");
        premiers::crible235<size_t>(100'000'000, std::back_inserter(premiers));
    }

    std::cout << "g(18) = " << g(premiers, 18) << std::endl;
    std::cout << "g(19) = " << g(premiers, 19) << std::endl;

    std::cout << "S(10) = " << S(premiers, 10) << std::endl;
    std::cout << "S(100) = " << S(premiers, 100) << std::endl;

    size_t limite_m = 10'000'000;
    std::vector<short> moebius(limite_m + 1, 0);
    {
        Timer t("Moebius");
        for (size_t n = 1; n <= limite_m; ++n) {
            moebius[n] = arithmetique::moebius(n, premiers);
        }
    }

    std::cout << "Q(10) = " << Q(moebius, 10) << std::endl;
    std::cout << "Q(100) = " << Q(moebius, 100) << std::endl;
    std::cout << "Q(1'000) = " << Q(moebius, 1'000) << std::endl;
    std::cout << "Q(10'000) = " << Q(moebius, 10'000) << std::endl;
    std::cout << "Q(100'000) = " << Q(moebius, 100'000) << std::endl;
    std::cout << "Q(1'000'000) = " << Q(moebius, 1'000'000) << std::endl;
    std::cout << "Q(10'000'000) = " << Q(moebius, 10'000'000) << std::endl;
    std::cout << "Q(100'000'000) = " << Q(moebius, 100'000'000) << std::endl;
    std::cout << "Q(1'000'000'000) = " << Q(moebius, 1'000'000'000) << std::endl;
    std::cout << "Q(10'000'000'000) = " << Q(moebius, 10'000'000'000) << std::endl;
    std::cout << "Q(100'000'000'000) = " << Q(moebius, 100'000'000'000) << std::endl;
    std::cout << "Q(1'000'000'000'000) = " << Q(moebius, 1'000'000'000'000) << std::endl;
    std::cout << "Q(10'000'000'000'000) = " << Q(moebius, 10'000'000'000'000) << std::endl;
    std::cout << "Q(100'000'000'000'000) = " << Q(moebius, 100'000'000'000'000) << std::endl;

    size_t limite = puissance::puissance<size_t>(10, 14);

    size_t resultat = 0;
    for (size_t n = 1; n * n <= limite; ++n) {
        resultat += n * n * Q(moebius, limite / (n * n));
        resultat %= 1'000'000'007;
    }
    return std::to_string(resultat);
}
