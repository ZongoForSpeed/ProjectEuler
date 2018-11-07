#include "problemes.h"
#include "arithmetique.h"
#include "pythagoricien.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(39, "Integer right triangles") {
    // If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three
    // solutions for p = 120.
    //
    // {20,48,52}, {24,45,51}, {30,40,50}
    //
    // For which value of p ≤ 1000, is the number of solutions maximised?
    size_t limite = 1'000;
    std::vector<nombre> solutions(limite + 1, 0);
    Pythagoricien pythagoricien(limite);
    std::set<std::tuple<size_t, size_t, size_t>> resultat;
    for (auto t: pythagoricien) {
    	size_t a,b,c;
    	std::tie(a,b,c) = t;
    	size_t s = a + b + c;
    	for (size_t k = s; k < limite + 1; k += s) {
    		solutions[k]++;
    	}
    }

    auto it = std::max_element(solutions.begin(), solutions.end());
	return std::to_string(std::distance(solutions.begin(), it));
}
