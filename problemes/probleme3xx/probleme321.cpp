#include "../problemes.h"
#include "utilitaires.h"
#include "iterator.h"

#include <algorithm>
#include <numeric>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(321, "Swapping Counters") {
    // A horizontal row comprising of 2n + 1 squares has n red counters placed at one end and n blue counters at the
    // other end, being separated by a single empty square in the centre. For example, when n = 3.
    //
    // p321_swapping_counters_1.gif
    // A counter can move from one square to the next (slide) or can jump over another counter (hop) as long as the
    // square next to that counter is unoccupied.
    // 
    // p321_swapping_counters_2.gif
    // Let M(n) represent the minimum number of moves/actions to completely reverse the positions of the coloured
    // counters; that is, move all the red counters to the right and all the blue counters to the left.
    // 
    // It can be verified M(3) = 15, which also happens to be a triangle number.
    // 
    // If we create a sequence based on the values of n for which M(n) is a triangle number then the first five terms
    // would be:
    //      1, 3, 10, 22, and 63, and their sum would be 99.
    // 
    // Find the sum of the first forty terms of this sequence.
    size_t limite = 40;
    // M(n) = n.(n+2) = t.(t+1)/2
    // 2*n*(n+2) = t.(t+1)
    // 2X² + 4X - Y² - Y = 0

    // Xn+1 = 3 Xn + 2 Yn + 3
    // Yn+1 = 4 Xn + 3 Yn + 5

    vecteur solutions;
    {
        std::pair<nombre, nombre> s(0, 0);
        for (size_t i = 0; i < limite; ++i) {
            nombre Xn = s.first;
            nombre Yn = s.second;

            nombre X1 = 3 * Xn + 2 * Yn + 3;
            nombre Y1 = 4 * Xn + 3 * Yn + 5;

            s = std::make_pair(X1, Y1);
            solutions.push_back(s.first);
            // std::cout << s << std::endl;
        }
    }
    {
        std::pair<nombre, nombre> s(1, 2);
        solutions.push_back(s.first);
        for (size_t i = 0; i < limite; ++i) {
            nombre Xn = s.first;
            nombre Yn = s.second;

            nombre X1 = 3 * Xn + 2 * Yn + 3;
            nombre Y1 = 4 * Xn + 3 * Yn + 5;

            s = std::make_pair(X1, Y1);
            solutions.push_back(s.first);
            // std::cout << s << std::endl;
        }
    }

    std::ranges::sort(solutions);
    // std::cout << solutions << std::endl;

    nombre resultat = std::reduce(solutions.begin(), iterator::next(solutions.begin(), limite));
    return std::to_string(resultat);
}
