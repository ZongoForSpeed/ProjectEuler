#include "../problemes.h"
#include "premiers.h"
#include "arithmetique.h"

#include <memory>
#include <set>
#include <utility>

typedef long long nombre;

namespace {
    struct Edge;
    struct Node;

    typedef std::shared_ptr<Edge> PEdge;
    typedef std::shared_ptr<Node> PNode;

    struct Node {
        nombre value;
        size_t key;

        std::set<PEdge> edges;

        explicit Node(nombre v) : value(v), key(0) {}
    };

    struct Edge {
        PNode n1;
        PNode n2;
        nombre value;

        Edge(PNode n1_, PNode n2_, nombre v) : n1(std::move(n1_)), n2(std::move(n2_)), value(v) {}

        // bool operator<(const Edge &e) const {
        //     if (value != e.value)
        //         return value < e.value;
        //     if (n1->key != e.n1->key)
        //         return n1->key < e.n1->key;
        //     return n2->key < e.n2->key;
        // }
    };
}

ENREGISTRER_PROBLEME(355, "Maximal coprime subset") {
    // Define Co(n) to be the maximal possible sum of a set of mutually co-prime elements from {1, 2, ..., n}.
    // For example Co(10) is 30 and hits that maximum on the subset {1, 5, 7, 8, 9}.
    //
    // You are given that Co(30) = 193 and Co(100) = 1356.
    //
    // Find Co(200000).
    nombre maxVal = 200000;
    nombre sum = 1;

    std::vector<nombre> primes;
    premiers::crible2<nombre>(200000 + 1, std::back_inserter(primes));

    std::vector<PNode> nodes;
    nodes.reserve(primes.size());

    for (nombre p : primes) {
        nombre value = p;
        while (value <= maxVal / p) value *= p;
        nodes.push_back(std::make_shared<Node>(value));
    }

    for (size_t pi1 = 0; pi1 < primes.size(); pi1++) {
        nombre p1 = primes[pi1];
        if (p1 > maxVal / 2) break;
        for (size_t pi2 = pi1 + 1; pi2 < primes.size(); pi2++) {
            nombre p2 = primes[pi2];
            if (p2 > maxVal / 2) break;

            nombre value = nodes[pi1]->value;
            nombre maxLocal = value;
            while (value % p1 == 0) {
                value /= p1;
                while (value <= maxVal / p2) value *= p2;
                if (value > maxLocal) maxLocal = value;
            }

            nombre diff = maxLocal - nodes[pi1]->value - nodes[pi2]->value;
            if (diff > 0) {
                PEdge edge = std::make_shared<Edge>(nodes[pi1], nodes[pi2], diff);
                nodes[pi1]->edges.insert(edge);
                nodes[pi2]->edges.insert(edge);
            }
        }
    }

    size_t nodesLeft = nodes.size();
    size_t noChange = 0;
    size_t index = 0;

    std::vector<PEdge> remEdges;
    while (noChange < nodesLeft) {
        PNode node = nodes[index];

        // remove edges with negative value
        remEdges.clear();
        for (const PEdge &e : node->edges) {
            if (e->value <= 0) {
                remEdges.push_back(e);
            }
        }
        if (!remEdges.empty()) {
            for (const PEdge &e : remEdges) {
                e->n1->edges.erase(e);
                e->n2->edges.erase(e);
            }
        }

        // remove verticies with 0 or 1 edge.
        // if 1 edge, add value to other vertex
        if (node->edges.size() == 1) {
            sum += node->value;

            PEdge e = *(node->edges.begin());
            PNode other = e->n1 == node ? e->n2 : e->n1;

            other->value += e->value;
            other->edges.erase(e);

            for (const PEdge &e2 : other->edges) {
                e2->value -= e->value;
            }

            nodesLeft--;
            nodes[index] = nodes[nodesLeft];
            noChange = 0;
        }
        else if (node->edges.empty()) {
            sum += node->value;

            nodesLeft--;
            nodes[index] = nodes[nodesLeft];
            noChange = 0;
        }
        else {
            noChange++;
        }

        index++;
        if (index >= nodesLeft) index = 0;
    }

    // sum values of remaining verticies
    for (size_t i = 0; i < nodesLeft; ++i) {
        nodes[i]->key = i;
        sum += nodes[i]->value;
    }

    // now remove edges until each vertex has no more
    // than one edge
    std::set<PEdge> edges;
    for (size_t i = 0; i < nodesLeft; ++i) {
        for (const PEdge &e : nodes[i]->edges) {
            edges.insert(e);
        }
    }

    nombre max = 1;
    nombre prev = 0;
    while (max > prev) {
        prev = max;
        PEdge best1;
        PEdge best2;
        for (auto it1 = edges.begin(), en = edges.end(); it1 != en; ++it1) {
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                auto & e1 = *it1;
                auto & e2 = *it2;
                std::vector<bool> used(nodesLeft, false);
                nombre local = 0;
                for (const PEdge &e : edges) {
                    if (e == e1 || e == e2) {
                        continue;
                    }

                    if (!used[e->n1->key] && !used[e->n2->key]) {
                        local += e->value;
                        used[e->n1->key] = true;
                        used[e->n2->key] = true;
                    }
                }

                if (local > max) {
                    best1 = e1;
                    best2 = e2;
                    max = local;
                }
            }
        }

        if (best1)
            edges.erase(best1);
        if (best2)
            edges.erase(best2);
    }
    sum += max;
    
    std::cout << edges.size() << std::endl;

    return std::to_string(sum);
}
