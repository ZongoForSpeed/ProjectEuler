#include "problemes.h"
#include "arithmetique.h"
#include "chiffres.h"

#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    size_t calcul_position(size_t n) {
        std::ostringstream oss;
        for (size_t i = 0; i < n * n; ++i)
            oss << i;
        const std::string S = oss.str();

        const std::string ns = std::to_string(n);
        size_t position = 0;
        size_t compteur = 0;
        while (compteur < n) {
            position = S.find(ns, position + 1);
            ++compteur;
        }
        return position;
    }

    nombre d(nombre n) {
        nombre i = 1;
        nombre t = 1;
        nombre c = 1;

        while (10 * i <= n) {
            c += t * i * 9;
            i *= 10;
            t += 1;
        }

        c += t * (n - i);
        return c;
    }

    std::deque<std::string> enumeration(size_t n) {
        std::deque<std::string> resultat{""};
        for (size_t d = 0; d < n; ++d) {
            std::deque<std::string> r;
            for (const auto &x: resultat) {
                for (char y = '0'; y <= '9'; ++y) {
                    r.push_back(x);
                    r.back().push_back(y);
                }
            }

            resultat = std::move(r);
        }

        return resultat;
    }

    nombre f(nombre n) {
        auto ns = std::to_string(n);
        nombre i = 0;

        while (true) {
            std::set<nombre> cc;
            for (auto dd: enumeration(i)) {
                for (size_t j = 0; j < ns.size() + 1; ++j) {
                    std::string x = ns.substr(j) + dd + ns.substr(0, j);
                    if (x[0] != '0') {
                        cc.insert(std::stoul(x));
                    }
                }

                if (!dd.empty() && dd[0] != '0') {
                    for (size_t j = 1; j < dd.size(); ++j) {
                        std::string x = dd.substr(0, j) + ns + dd.substr(j);
                        cc.insert(std::stoul(x));
                    }
                }
            }

            for (nombre x: cc) {
                std::string xx = std::to_string(x) + std::to_string(x + 1);
                for (nombre j = 0; j < chiffres::nombre_chiffres(x); ++j) {
                    if (xx.substr(j, ns.size()) == ns) {
                        --n;
                        if (n == 0)
                            return d(x) + j;
                    }
                }
            }
            i++;
        }
    }
}

ENREGISTRER_PROBLEME(305, "Reflexive Position") {
    // Let's call S the (infinite) string that is made by concatenating the consecutive positive integers (starting from
    // 1) written down in base 10. Thus, S = 1234567891011121314151617181920212223242...
    //
    // It's easy to see that any number will show up an infinite number of times in S.
    //
    // Let's call f(n) the starting position of the nth occurrence of n in S.
    // For example, f(1)=1, f(5)=81, f(12)=271 and f(7780)=111111365.
    //
    // Find ∑f(3k) for 1≤k≤13.
    nombre resultat = 0;

    size_t limite = 13;
    for (size_t k = 1; k <= limite; ++k) {
        auto n = puissance::puissance<nombre>(3, k);
        nombre ff = 0;
        if (n == 243)
            ff = calcul_position(n);
        else
            ff = f(n);
        std::cout << "f(" << n << ") = " << ff << std::endl;
        resultat += ff;
    }

    return std::to_string(resultat);
}
