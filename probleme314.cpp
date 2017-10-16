#include "problemes.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<size_t, size_t> point;
typedef std::map<point, std::pair<long double, point>> graphe;

namespace {
    long double distance(const point &p1, const point &p2) {
        return std::sqrt((1.0L * p1.first - p2.first) * (1.0L * p1.first - p2.first)
                         + (1.0L * p1.second - p2.second) * (1.0L * p1.second - p2.second));
    }

    long double aire_triangle(const point &p1, const point &p2, const point &p3) {
        long double a = distance(p1, p2);
        long double b = distance(p2, p3);
        long double c = distance(p3, p1);
        long double s = (a + b + c) * 0.5;
        // formule de Héron
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    long double calcul_poids(const point &p1, const point &p2, long double objectif_ratio = 132.5) {
        if (p1 == p2)
            return 0.0;

        long double perimetre = distance(p1, p2);
        long double aire = aire_triangle(p1, p2, point(0, 0));

        return objectif_ratio * perimetre - aire;
    }

    auto minimum(graphe &G, const std::set<graphe::key_type> &noeuds) {
        long double min = std::numeric_limits<long double>::max();
        graphe::key_type resultat;
        for (const auto &n: noeuds) {
            const auto &v = G[n];
            if (v.first < min) {
                min = v.first;
                resultat = n;
            }
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(314, "The Mouse on the Moon") {
    // The moon has been opened up, and land can be obtained for free, but there is a catch. You have to build a wall
    // around the land that you stake out, and building a wall on the moon is expensive. Every country has been allotted
    // a 500 m by 500 m square area, but they will possess only that area which they wall in. 251001 posts have been
    // placed in a rectangular grid with 1 meter spacing. The wall must be a closed series of straight lines, each line
    // running from post to post.
    //
    // The bigger countries of course have built a 2000 m wall enclosing the entire 250 000 m2 area. The Duchy of Grand
    // Fenwick, has a tighter budget, and has asked you (their Royal Programmer) to compute what shape would get best
    // maximum enclosed-area/wall-length ratio.
    //
    // You have done some preliminary calculations on a sheet of paper. For a 2000 meter wall enclosing the 250 000 m2
    // area the enclosed-area/wall-length ratio is 125.
    // Although not allowed , but to get an idea if this is anything better: if you place a circle inside the square
    // area touching the four sides the area will be equal to π*2502 m2 and the perimeter will be π*500 m, so the
    // enclosed-area/wall-length ratio will also be 125.
    //
    // However, if you cut off from the square four triangles with sides 75 m, 75 m and 75√2 m the total area becomes
    // 238750 m2 and the perimeter becomes 1400+300√2 m. So this gives an enclosed-area/wall-length ratio of 130.87,
    // which is significantly better.
    // p314_landgrab.gif
    //
    // Find the maximum enclosed-area/wall-length ratio.
    // Give your answer rounded to 8 places behind the decimal point in the form abc.defghijk.
    const size_t rayon = 130;
    const size_t taille = 250;
    const point source(0, rayon);
    const point objectif(rayon, 0);

    // initialisation graphe
    graphe G;
    for (size_t x = 0; x < rayon + 1; ++x)
        for (size_t y = 0; y < rayon + 1; ++y) {
            if (x + y >= rayon
                && std::abs(y - std::sqrt(1.0L * rayon * rayon - x * x)) < 10.0L) {
                G[point(x, y)] = std::make_pair(calcul_poids(point(x, y), source), source);
            }
        }

    // Dijkstra
    std::set<graphe::key_type> noeuds;
    std::transform(G.begin(), G.end(), std::inserter(noeuds, noeuds.begin()),
                   [](const graphe::value_type &entry) { return entry.first; });

    while (!noeuds.empty()) {
        auto u = minimum(G, noeuds);
        noeuds.erase(u);
        if (u == objectif)
            break;

        long double poids = G[u].first;
        for (auto &entry: G) {
            auto nouveau_poids = calcul_poids(entry.first, u) + poids;
            if (nouveau_poids < entry.second.first)
                entry.second = std::make_pair(nouveau_poids, u);
        }
    }

    long double aire = taille * taille - rayon * rayon;
    long double perimetre = (taille - rayon) * 2;

    point courant = objectif;
    while (courant != source) {
        const auto &node = G[courant];
        perimetre += distance(courant, node.second);
        aire += aire_triangle(courant, node.second, point(0, 0));
        courant = node.second;
    }
    long double resultat = aire / perimetre;

    return std::to_string(resultat, 8);
}
