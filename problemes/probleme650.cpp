#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique_modulaire.h"
#include "chiffres.h"
#include "premiers.h"
#include "timer.h"

typedef boost::multiprecision::cpp_int nombre;
typedef arithmetique_modulaire::nombre_modulaire<1'000'000'007> nombre_modulaire;
/*
namespace {
    size_t sum_of_digits(size_t n, size_t p) {
        size_t somme = 0;
        for (size_t i = 0; i < n; ++i) {
            somme += chiffres::somme_chiffres(i, static_cast<unsigned short>(p));
        }

        return somme;
    }

    size_t product_of_binomial_power(size_t n, size_t p) {
        return (2 * sum_of_digits(n, p) -
                (n - 1) * chiffres::somme_chiffres(n, static_cast<unsigned short>(p))) / (p - 1);
    }

    nombre_modulaire sigma_of_binomial_product(size_t n, const std::vector<size_t> &premiers) {
        nombre_modulaire produit(1);
        for (auto p: premiers) {
            if (p > n) {
                break;
            }
            size_t k = product_of_binomial_power(n, p);
            nombre_modulaire f = nombre_modulaire::puissance(nombre_modulaire(p), k + 1);
            f /= p - 1;
            produit *= f;
        }

        return produit;
    }

    nombre_modulaire S(size_t n, const std::vector<size_t> &premiers) {
        nombre_modulaire somme(0);
        for (size_t k = 1; k <= n; ++k) {
            somme += sigma_of_binomial_product(k, premiers);
        }

        return somme;
    }
}
 */
namespace {
    nombre_modulaire D(size_t n, const std::vector<size_t> &premiers) {
        nombre_modulaire s(1);
        size_t m = n + 1;
        for (auto &p: premiers) {
            if (p > n) {
                break;
            }

            size_t compteur = 0;
            for (size_t f = p; f <= m; f *= p) {
                if (m % f == 0) {
                    continue;
                }

                compteur += (f - (m % f)) * (m / f);
            }

            if (compteur != 0) {
                s *= nombre_modulaire::puissance(nombre_modulaire(p), compteur + 1) - 1;
                s /= (p - 1);
            }
        }

        return s;
    }

    nombre_modulaire S(size_t n, const std::vector<size_t> &premiers) {
        nombre_modulaire s(0);
        for (size_t m = 1; m <= n; ++m) {
            s += D(m, premiers);
        }
        return s;
    }
}

ENREGISTRER_PROBLEME(650, "Divisors of Binomial Product") {
    // Let B(n) = Prod_{k=0..n} (n k), a product of binomial coefficients.
    //
    // For example, B(5) = (5 0) ⨯ (5 1) ⨯ (5 2) ⨯ (5 3) ⨯ (5 4) ⨯ (5 5)
    //                   = 1 ⨯ 5 ⨯ 10 ⨯ 10 ⨯ 5 ⨯ 1
    //                   = 2500.
    //
    // Let D(n) = Sum_{d|B(n)} d, the sum of the divisors of B(n).
    //
    // For example, the divisors of B(5) are 1, 2, 4, 5, 10, 20, 25, 50, 100, 125, 250, 500, 625, 1250 and 2500,
    // so D(5) = 1 + 2 + 4 + 5 + 10 + 20 + 25 + 50 + 100 + 125 + 250 + 500 + 625 + 1250 + 2500 = 5467.
    //
    // Let S(n) = Sum_{k=1..n} D(k).
    //
    // You are given S(5) = 5736, S(10) = 141740594713218418 and
    // S(100) mod 1'000'000'007 = 332792866.
    //
    // Find S(20'000) mod 1'000'000'007.
    //
    size_t limite = 20'000;
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite, std::back_inserter(premiers));

    std::cout << "D(5) = " << D(5, premiers) << std::endl;
    std::cout << "S(5) = " << S(5, premiers) << std::endl;

    std::cout << "S(10) = " << S(10, premiers) << std::endl;
    std::cout << "S(100) = " << S(100, premiers) << std::endl;

    return std::to_string(S(20'000, premiers).value());
}
