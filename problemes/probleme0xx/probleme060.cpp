#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"

#include <execution>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::map<vecteur, vecteur> graphe;

ENREGISTRER_PROBLEME(60, "Prime pair sets") {
    // The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in 
    // any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
    // The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
    //
    // Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
    nombre limite = 10000;

    std::set<nombre> premiers;
    premiers::crible23<nombre>(limite * limite, std::inserter(premiers, premiers.begin()));

    graphe groupe;
    for (auto p: premiers) {
        if (p > limite)
            break;
        for (auto q: premiers) {
            if (q >= p)
                break;

            if (premiers.find(chiffres::concatener(p, q)) != premiers.end()
                && premiers.find(chiffres::concatener(q, p)) != premiers.end()) {
                vecteur v = {q};
                groupe[v].push_back(p);
            }
        }
    }

    auto groupe_suivant = [&groupe](const graphe &g) -> graphe {
        graphe suivant;
        for (auto &arete: g) {
            auto p = arete.first;
            for (auto &q: arete.second) {
                vecteur v = {q};
                auto &arete_q = groupe[v];

                vecteur v_intersection;
                std::set_intersection(arete.second.begin(), arete.second.end(),
                                      arete_q.begin(), arete_q.end(),
                                      std::back_inserter(v_intersection));

                if (!v_intersection.empty()) {
                    v.insert(v.begin(), p.begin(), p.end());
                    suivant[v] = v_intersection;
                }
            }
        }
        return suivant;
    };

    auto suivant = groupe_suivant(groupe);
    suivant = groupe_suivant(suivant);
    suivant = groupe_suivant(suivant);

    vecteur solution;
    if (!suivant.empty()) {
        solution = suivant.begin()->first;
        solution.insert(solution.end(), suivant.begin()->second.begin(), suivant.begin()->second.end());
    }

    nombre resultat = std::reduce(std::execution::par,solution.begin(), solution.end());
    return std::to_string(resultat);
}
