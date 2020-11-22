#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"
#include "premiers.h"
#include "mpz_nombre.h"

namespace {

    template<typename Nombre, typename Iterator, class OutputIterator>
    void boucle_diviseurs(Nombre x, Iterator it, Iterator en, Nombre min, Nombre max, OutputIterator sortie) {
        if (it == en) {
            if (x > min) {
                *sortie++ = x;
            }
        } else {
            auto&[p, exposant] = *it;
            for (size_t n = 0; n <= exposant; ++n) {
                boucle_diviseurs(x, std::next(it), en, min, max, sortie);
                Nombre y = x * p;
                if (y > max) {
                    break;
                }
                x = y;
            }
        }
    }

    mpz_nombre f(mpz_nombre n, const std::vector<size_t> &premiers,
             boost::rational<long long> ratio_limite = boost::rational<long long>(1, 2)) {
        double ratio_min = std::numeric_limits<double>::max();
        mpz_nombre abc = 0;
        mpz_nombre limite = std::cbrt(n);
        mpz_nombre limite_min =
                ((ratio_limite.denominator() - ratio_limite.numerator()) * limite) / ratio_limite.denominator();
        mpz_nombre limite_max =
                ((ratio_limite.denominator() + ratio_limite.numerator()) * limite) / ratio_limite.denominator();

        std::map<mpz_nombre, size_t> decomposition;
        arithmetique::decomposition(n, premiers, decomposition);

        std::set<mpz_nombre> diviseurs;
        boucle_diviseurs<mpz_nombre>(1, decomposition.begin(), decomposition.end(), limite_min, limite_max,
                                 std::inserter(diviseurs, diviseurs.begin()));

        for (auto it1 = diviseurs.begin(), en = diviseurs.end(); it1 != en; ++it1) {
            mpz_nombre a = *it1;
            if (a > limite) {
                break;
            }
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                mpz_nombre b = *it2;
                mpz_nombre ab = a * b;
                if (n % ab != 0) {
                    continue;
                }
                mpz_nombre c = n / a / b;
                if (c > b) {
                    double ratio = c.get_double() / a.get_double();
                    if (ratio < ratio_min) {
                        abc = a + b + c;
                        ratio_min = ratio;
                    }
                } else {
                    break;
                }
            }
        }

        return abc;
    }
}

ENREGISTRER_PROBLEME(418, "Factorisation triples") {
    // Let n be a positive integer. An integer triple (a, b, c) is called a factorisation triple of n if:
    //  1 <= a <= b <= c
    //  a·b·c = n.
    //
    // Define f(n) to be a + b + c for the factorisation triple (a, b, c) of n which minimises c / a. One can show that
    // this triple is unique.
    //
    // For example, f(165) = 19, f(100100) = 142 and f(20!) = 4034872.
    //
    // Find f(43!).
    std::vector<size_t> premiers;
    premiers::crible2<size_t>(43, std::back_inserter(premiers));
    std::cout << premiers << std::endl;

    std::cout << "f(165) = " << f(165, premiers) << std::endl;
    std::cout << "f(100100) = " << f(100100, premiers) << std::endl;
    std::cout << "f(20!) = " << f(mpz_nombre::factorielle(20), premiers, boost::rational<long long>(1, 100))
              << std::endl;

    mpz_nombre resultat = f(mpz_nombre::factorielle(43), premiers, boost::rational<long long>(1, 10000));

    return resultat.to_string();
}
