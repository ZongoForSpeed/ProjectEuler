#include "graphe.h"

#include <algorithm>

namespace graphe {
    Tarjan::Tarjan(const std::map<nombre, vecteur> &g) : index(0), graphe(g) {
        for (auto &p: g) {
            sommets.emplace(p.first, p.first);
        }
    }

    void Tarjan::algorithme() {
        for (const auto &p: graphe) {
            auto &v = sommets.at(p.first);
            if (!v.index)
                strongconnect(v);
        }
    }

    void Tarjan::strongconnect(Sommet &v) {
        // Set the depth index for v to the smallest unused index
        v.index = index;
        v.lowlink = index;
        ++index;
        S.push_back(v.n);
        v.onStack = true;

        // Consider successors of v
        for (const nombre &ww: graphe[v.n]) {
            Sommet &w = sommets.at(ww);
            if (!w.index) {
                // Successor w has not yet been visited; recurse on it
                strongconnect(w);
                v.lowlink = std::min(v.lowlink, w.lowlink);
            } else if (w.onStack) {
                // Successor w is in stack S and hence in the current SCC
                v.lowlink = std::min(v.lowlink, *(w.index));
            }
        }
        // If v is a root node, pop the stack and generate an SCC
        if (v.lowlink == *(v.index)) {
            std::set<nombre> composante_connexe;
            do {
                nombre w = S.back();
                S.pop_back();
                sommets.at(w).onStack = false;
                composante_connexe.insert(w);
                if (w == v.n)
                    break;
            } while (true);
            resultat.push_back(composante_connexe);
        }
    }

    Dijkstra::Dijkstra(const graphe &_G, const nombre _debut, const nombre _fin) : G(_G), debut(_debut), fin(_fin) {}

    nombre Dijkstra::algorithme() {
        const nombre taille = G.size();
        vecteur distance(taille, std::numeric_limits<nombre>::max());
        vecteur precedent(taille, debut);

        distance[debut] = 0;
        std::set<nombre> noeuds;
        for (const auto &arete: G)
            noeuds.insert(arete.first);

        while (!noeuds.empty()) {
            nombre suivant = 0;
            nombre minimum = std::numeric_limits<nombre>::max();
            for (nombre n: noeuds) {
                if (distance[n] < minimum) {
                    suivant = n;
                    minimum = distance[n];
                }
            }

            noeuds.erase(suivant);
            for (const auto &arete: G[suivant]) {
                if (distance[arete.first] > distance[suivant] + arete.second) {
                    distance[arete.first] = distance[suivant] + arete.second;
                    precedent[arete.first] = suivant;
                }
            }
        }

        nombre n = fin;
        while (n != debut) {
            resultat.push_back(n);
            n = precedent[n];
        }

        resultat.push_back(debut);

        resultat = vecteur(resultat.rbegin(), resultat.rend());
        return distance[fin];
    }

    Kruskal::Kruskal(const aretes &_A) : A(_A) {
        std::sort(A.begin(), A.end(),
                  [](const arete &a, const arete &b) { return std::get<2>(a) < std::get<2>(b); });
    }

    Kruskal::aretes Kruskal::algorithme() {
        aretes resultat;
        std::set<nombre> sommets;
        for (const arete &a: A) {
            sommets.insert(std::get<0>(a));
            sommets.insert(std::get<1>(a));
        }

        vecteur groupe;
        for (const nombre sommet: sommets)
            groupe.push_back(sommet);

        for (const arete &a: A) {
            nombre i, j;
            std::tie(i, j, std::ignore) = a;
            if (groupe[i] != groupe[j]) {
                nombre groupe_j = groupe[j];
                nombre groupe_i = groupe[i];
                std::replace(groupe.begin(), groupe.end(), groupe_j, groupe_i);
                resultat.push_back(a);
            }
        }

        return resultat;
    }

}    

