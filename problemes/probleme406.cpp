#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<double, nombre, nombre> triplet;

namespace {
    double C(nombre n, double a, double b) {
        const double epsilon = 1e-6;

        std::priority_queue<triplet, std::vector<triplet>, std::greater<>> tas;
        tas.emplace(a, 1, 0);
        tas.emplace(b, 0, 1);
        std::map<double, nombre> mem{{0.0, 1}};
        std::set<paire> used;
        used.emplace(0, 0);
        while (true) {
            auto[courant, move_a, move_b] = tas.top();
            tas.pop();

            auto ret = used.emplace(move_a, move_b);
            if (!ret.second) {
                continue;
            }
            nombre optimum = 1;
            if (courant >= a) optimum += (--mem.upper_bound(courant - a + epsilon))->second;
            if (courant >= b) optimum += (--mem.upper_bound(courant - b + epsilon))->second;
            if (optimum >= n) {
                return courant;
            }
            mem[courant] = optimum;
            tas.emplace(courant + a, move_a + 1, move_b);
            tas.emplace(courant + b, move_a, move_b + 1);
        }
    }
}

ENREGISTRER_PROBLEME(406, "Guessing Game") {
    // We are trying to find a hidden number selected from the set of integers {1, 2, ..., n} by asking questions. Each 
    // number (question) we ask, we get one of three possible answers:
    //
    // "Your guess is lower than the hidden number" (and you incourant a cost of a), or
    // "Your guess is higher than the hidden number" (and you incourant a cost of b), or
    // "Yes, that's it!" (and the game ends).
    // Given the value of n, a, and b, an optimal strategy minimizes the total cost for the worst possible case.
    //
    // For example, if n = 5, a = 2, and b = 3, then we may begin by asking "2" as our first question.
    //
    // If we are told that 2 is higher than the hidden number (for a cost of b=3), then we are sure that "1" is the 
    // hidden number (for a total cost of 3).
    // If we are told that 2 is lower than the hidden number (for a cost of a=2), then our next question will be "4".
    // If we are told that 4 is higher than the hidden number (for a cost of b=3), then we are sure that "3" is the 
    // hidden number (for a total cost of 2+3=5).
    // If we are told that 4 is lower than the hidden number (for a cost of a=2), then we are sure that "5" is the 
    // hidden number (for a total cost of 2+2=4).
    // Thus, the worst-case cost achieved by this strategy is 5. It can also be shown that this is the lowest worst-case
    // cost that can be achieved. So, in fact, we have just described an optimal strategy for the given values of n, a, 
    // and b.
    //
    // Let C(n, a, b) be the worst-case cost achieved by an optimal strategy for the given values of n, a, and b.
    //
    // Here are a few examples:
    // C(5, 2, 3) = 5
    // C(500, √2, √3) = 13.22073197...
    // C(20000, 5, 7) = 82
    // C(2000000, √5, √7) = 49.63755955...
    //
    // Let Fk be the Fibonacci numbers: Fk = Fk-1 + Fk-2 with base cases F1 = F2 = 1.
    // Find ∑1≤k≤30 C(10**12, √k, √Fk), and give your answer rounded to 8 decimal places behind the decimal point.
    std::cout << std::setprecision(10);
    std::cout << "C(5, 2, 3) = " << C(5, 2, 3) << std::endl;
    std::cout << "C(500, √2, √3) = " << C(500, std::sqrt(2.0), std::sqrt(3.0)) << std::endl;
    std::cout << "C(20000, 5, 7) = " << C(20000, 5, 7) << std::endl;
    std::cout << "C(2000000, √5, √7) = " << C(2000000, std::sqrt(5.0), std::sqrt(7.0)) << std::endl;

    vecteur fibonacci{0, 1};
    for (size_t k = 2; k < 31; ++k) {
        fibonacci.push_back(fibonacci[k - 2] + fibonacci[k - 1]);
    }

    nombre limite = 1'000'000'000'000;

    double resultat = 0.0;
    for (size_t k = 1; k < 31; ++k) {
        resultat += C(limite, std::sqrt(k), std::sqrt(fibonacci[k]));
    }

    return std::to_fixed(resultat, 8);
}
