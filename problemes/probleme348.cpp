#include "problemes.h"
#include "arithmetique.h"
#include "chiffres.h"

#include <queue>
#include <set>
#include <tuple>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> triplet;

ENREGISTRER_PROBLEME(348, "Sum of a square and a cube") {
    // Many numbers can be expressed as the sum of a square and a cube. Some of them in more than one way.
    //
    // Consider the palindromic numbers that can be expressed as the sum of a square and a cube, both greater than 1, in exactly 4 different combinaisons.
    // For example, 5229225 is a palindromic number and it can be expressed in exactly 4 different combinaisons:
    //
    // 2285² + 20**3
    // 2223² + 66**3
    // 1810² + 125**3
    // 1197² + 156**3
    //
    // Find the sum of the five smallest such palindromic numbers.
    std::set<paire> seen;
    std::map<nombre, nombre> combinaisons;
    std::priority_queue<triplet, std::vector<triplet>, std::greater<> > q;
    q.emplace(12, 2, 2);
    seen.emplace(2, 2);
    std::vector<nombre> palindromes;
    while (palindromes.size() < 5) {
        auto[p, s, c] = q.top();
        q.pop();
        if (chiffres::palindrome(p)) {
            nombre &ncombinaisons = combinaisons[p];
            ++ncombinaisons;
            if (ncombinaisons == 4 && std::get<0>(q.top()) > p) {
                palindromes.push_back(p);
            }
        }
        auto it = seen.emplace(s + 1, c);
        if (it.second) {
            q.emplace((s + 1) * (s + 1) + c * c * c, s + 1, c);
        }

        it = seen.emplace(s, c + 1);
        if (it.second) {
            q.emplace(s * s + (c + 1) * (c + 1) * (c + 1), s, c + 1);
        }
    }
    nombre resultat = std::reduce(palindromes.begin(), palindromes.end());
    return std::to_string(resultat);
}
