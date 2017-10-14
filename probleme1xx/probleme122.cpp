#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::vector<std::set<nombre>> ensemble;

namespace {
    const ensemble &min_puissance(std::map<nombre, ensemble> &cache, nombre n) {
        if (cache.empty())
            cache[1].push_back(std::set<nombre>());

        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;

        nombre longueur_min = std::numeric_limits<nombre>::max();
        ensemble e_min;
        for (nombre i = 1; i < n / 2 + 1; ++i) {
            const ensemble &e1 = min_puissance(cache, i);
            const ensemble &e2 = min_puissance(cache, n - i);

            for (const auto &s1: e1)
                for (const auto &s2: e2) {
                    std::set<nombre> s;
                    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(s, s.begin()));
                    s.insert(n);
                    if (s.size() == longueur_min)
                        e_min.push_back(s);
                    else if (s.size() < longueur_min) {
                        longueur_min = s.size();
                        e_min.clear();
                        e_min.push_back(s);
                    }
                }
        }

        std::sort(e_min.begin(), e_min.end());
        e_min.erase(std::unique(e_min.begin(), e_min.end()), e_min.end());

        it = cache.insert(it, std::make_pair(n, e_min));
        return it->second;
    }
}

ENREGISTRER_PROBLEME(122, "Efficient exponentiation") {
    // The most naive way of computing n^15 requires fourteen multiplications:
    //
    //      n × n × ... × n = n^15
    //
    // But using a "binary" method you can compute it in six multiplications:
    //
    //      n × n = n^2
    //      n^2 × n^2 = n^4
    //      n^4 × n^4 = n^8
    //      n^8 × n^4 = n^12
    //      n^12 × n^2 = n^14
    //      n^14 × n = n^15
    //
    // However it is yet possible to compute it in only five multiplications:
    //
    //      n × n = n2
    //      n^2 × n = n3
    //      n^3 × n^3 = n6
    //      n^6 × n^6 = n12
    //      n^12 × n^3 = n15
    // 
    // We shall define m(k) to be the minimum number of multiplications to compute n^k; 
    // for example m(15) = 5.
    // 
    // For 1 ≤ k ≤ 200, find ∑ m(k).
    std::map<nombre, ensemble> cache;
    nombre resultat = 0;
    for (nombre n = 1; n < 201; ++n) {
        auto p = min_puissance(cache, n);
        resultat += p.front().size();
    }
    return std::to_string(resultat);
}
