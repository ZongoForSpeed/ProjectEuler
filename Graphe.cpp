#include "Graphe.h"

Tarjan::Tarjan(const graphe & g) : index(0), G(g)
{
    for (auto & p: g)
    {
        sommets.insert(std::make_pair(p.first, Sommet(p.first)));
    }
}

void Tarjan::algorithme()
{
    for (const auto & p: G)
    {
        auto & v = sommets.at(p.first);
        if (!v.index)
            strongconnect(v);
    }
}

void Tarjan::strongconnect(Sommet & v)
{
    // Set the depth index for v to the smallest unused index
    v.index = index;
    v.lowlink = index;
    ++index;
    S.push_back(v.n);
    v.onStack = true;
    
    // Consider successors of v
    for (const nombre & ww: G[v.n])
    {
        Sommet & w = sommets.at(ww);
        if (!w.index)
        {
            // Successor w has not yet been visited; recurse on it
            strongconnect(w);
            v.lowlink = std::min(v.lowlink, w.lowlink);
        }
        else if (w.onStack)
        {
            // Successor w is in stack S and hence in the current SCC
            v.lowlink = std::min(v.lowlink, *(w.index));
        }
    }

    // If v is a root node, pop the stack and generate an SCC
    if (v.lowlink == *(v.index))
    {
        std::set<nombre> composante_connexe;
        do
        {
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
