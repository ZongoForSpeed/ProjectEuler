#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"
#include "premiers.h"
#include "combinatoire.h"

typedef boost::multiprecision::cpp_int nombre;

namespace {

    template<typename Nombre, typename Conteneur>
    std::deque<Nombre> _diviseurs(Nombre n, const Conteneur &premiers, Nombre limite) {
        std::map<Nombre, size_t> d;
        arithmetique::decomposition<Nombre>(n, premiers, d);
        std::deque<Nombre> resultat{1};
        for (const auto &[p, exposant]: d) {
            // std::cout << "p = " << p << ", exposant = " << exposant << std::endl;
            std::deque<Nombre> r = resultat;
            Nombre f = p;
            for (size_t e = 0; e < exposant; ++e) {
                for (const auto &i: resultat) {
                    if (Nombre ff = i * f; ff < limite) {
                        r.push_back(i * f);
                    }
                }
                f *= p;
            }

            // std::cout << "r.size() = " << r.size() << std::endl;
            resultat.swap(r);
        }

        std::sort(resultat.begin(), resultat.end());
        return resultat;
    }

    nombre racine_cubique(const nombre &x) {
        nombre l = 1;
        nombre r = x;
        while (l < r) {
            nombre m = (l + r + 1) / 2;
            if (m * m * m <= x) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        return r;
    }

    nombre f(nombre n, const std::vector<size_t> &premiers,
             boost::rational<long long> ratio_limite = boost::rational<long long>(1, 2)) {
        long double ratio_min = std::numeric_limits<long double>::max();
        nombre abc = 0;
        nombre limite = racine_cubique(n);
        // std::cout << "limite = " << limite << std::endl;
        nombre limite_inf =
                ((ratio_limite.denominator() - ratio_limite.numerator()) * limite) / ratio_limite.denominator();
        nombre limite_sup =
                ((ratio_limite.denominator() + ratio_limite.numerator()) * limite) / ratio_limite.denominator();

        auto diviseurs = _diviseurs<nombre>(n, premiers, limite_sup);
        // std::cout << "diviseurs : " << diviseurs.size() << std::endl;
        auto it1 = std::lower_bound(diviseurs.begin(), diviseurs.end(), limite_inf);
        auto en = std::upper_bound(diviseurs.begin(), diviseurs.end(), limite_sup);

        // std::cout << "std::distance(it1, en) = " << std::distance(it1, en) << std::endl;
        for (; it1 != en; ++it1) {
            nombre a = *it1;
            if (a > limite) {
                break;
            }
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                nombre b = *it2;
                nombre ab = a * b;
                if (n % ab != 0) {
                    continue;
                }
                nombre c = n / a / b;
                if (c > b) {
                    long double ratio = c.convert_to<long double>() / a.convert_to<long double>();
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
    std::cout << "f(20!) = " << f(combinatoire::factorielle<nombre>(20), premiers, boost::rational<long long>(1, 100))
              << std::endl;

    nombre resultat = f(combinatoire::factorielle<nombre>(43), premiers, boost::rational<long long>(1, 10000));

    return resultat.str();
}
