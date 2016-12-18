#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> triplet;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(309, "Integer Ladders")
{
    // In the classic "Crossing Ladders" problem, we are given the lengths x and
    // y of two ladders resting on the opposite walls of a narrow, level street. 
    // We are also given the height h above the street where the two ladders cross
    // and we are asked to find the width of the street (w).
    //
    // Here, we are only concerned with instances where all four variables are 
    // positive integers.
    // For example, if x = 70, y = 119 and h = 30, we can calculate that w = 56.
    //
    // In fact, for integer values x, y, h and 0 < x < y < 200, there are only 
    // five triplets (x,y,h) producing integer solutions for w:
    // (70, 119, 30), (74, 182, 21), (87, 105, 35), (100, 116, 35) and (119, 175, 40).
    //
    // For integer values x, y, h and 0 < x < y < 1 000 000, how many triplets 
    // (x,y,h) produce integer solutions for w?
    nombre limite = 1000000;
    
    // https://en.wikipedia.org/wiki/Crossed_ladders_problem
    // https://fr.wikipedia.org/wiki/Triplet_pythagoricien#Th.C3.A9or.C3.A8me_fondamental
    std::vector<triplet> triplets;
    for (nombre p = 1; p*p < limite; ++p) {
        for (nombre q = 1; q < p; ++q) {
            nombre z = p*p + q*q;
            if (z > limite)
                break;
            
            if (p%2 != q%2 && arithmetiques::PGCD(p, q) == 1) {
                nombre x = p*p - q*q;
                nombre y = 2*p*q;
                
                for (nombre k = 1; z*k < limite; ++k) {
                    triplets.push_back(std::make_tuple(k*x, k*y, k*z));
                }
            }
        }
    }
    
    // std::cout << triplets << std::endl;
    std::map<nombre, std::vector<paire>> dictionnaire;
    for (const auto & t: triplets) {
        nombre x,y,z;
        std::tie(x,y,z) = t;
        dictionnaire[x].push_back(std::make_pair(y,z));
        dictionnaire[y].push_back(std::make_pair(x,z));
    }
    
    // std::cout << dictionnaire << std::endl;
    std::vector<triplet> resultat;

    for (const auto & d: dictionnaire) {
        // const nombre w = d.first;
        const auto & v = d.second;
        for (auto it1 = v.begin(), en = v.end(); it1 != en; ++it1) {
            nombre a1, b1;
            std::tie(a1, b1) = *it1;
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                nombre a2, b2;
                std::tie(a2, b2) = *it2;
                // 1 / h = 1 / a1 + 1 / a2
                nombre n1 = a1 * a2;
                nombre n2 = a1 + a2;
                if (n1%n2 == 0) {
                    nombre h = n1 / n2;
                    auto t = std::make_tuple(std::min(b1, b2), std::max(b1, b2), h);
                    resultat.push_back(t);
                    // std::cout << t << std::endl;
                }
            }
        }
    }

    return std::to_string(resultat.size());
}