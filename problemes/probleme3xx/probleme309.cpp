#include <ranges>

#include "../problemes.h"
#include "arithmetique.h"
#include "pythagoricien.h"

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> triplet;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(309, "Integer Ladders") {
    // In the classic "Crossing Ladders" problem, we are given the lengths x and y of two ladders resting on the
    // opposite walls of a narrow, level street. We are also given the height h above the street where the two ladders
    // cross and we are asked to find the width of the street (w).
    //
    // Here, we are only concerned with instances where all four variables are positive integers.
    // For example, if x = 70, y = 119 and h = 30, we can calculate that w = 56.
    //
    // In fact, for integer values x, y, h and 0 < x < y < 200, there are only five triplets (x,y,h) producing integer
    // solutions for w: (70, 119, 30), (74, 182, 21), (87, 105, 35), (100, 116, 35) and (119, 175, 40).
    //
    // For integer values x, y, h and 0 < x < y < 1 000 000, how many triplets (x,y,h) produce integer solutions for w?
    nombre limite = 1000000;

    // https://en.wikipedia.org/wiki/Crossed_ladders_problem
    std::map<nombre, std::vector<paire>> dictionnaire;
    Pythagoricien pythagoricien(limite);
    for (const auto[x, y, z]: pythagoricien) {
        for (nombre k = 1; z * k < limite; ++k) {
            dictionnaire[k * x].emplace_back(k * y, k * z);
            dictionnaire[k * y].emplace_back(k * x, k * z);
        }
    }

    // std::cout << dictionnaire << std::endl;
    std::vector<triplet> resultat;

    for (const auto &v: dictionnaire | std::views::values) {
        // const nombre w = d.first;
        for (auto it1 = v.begin(), en = v.end(); it1 != en; ++it1) {
            auto[a1, b1] = *it1;
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                auto[a2, b2] = *it2;
                // 1 / h = 1 / a1 + 1 / a2
                nombre n1 = a1 * a2;
                nombre n2 = a1 + a2;
                if (n1 % n2 == 0) {
                    nombre h = n1 / n2;
                    resultat.emplace_back(std::min(b1, b2), std::max(b1, b2), h);
                }
            }
        }
    }

    return std::to_string(resultat.size());
}
