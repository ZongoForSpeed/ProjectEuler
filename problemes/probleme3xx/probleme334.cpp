#include "../problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(334, "Spilling the beans") {
    // In Plato's heaven, there exist an infinite number of bowls in a straight line.
    // Each bowl either contains some or none of a finite number of beans.
    // A child plays a game, which allows only one kind of move: removing two beans from any bowl, and putting one in
    // each of the two adjacent bowls.
    // The game ends when each bowl contains either one or no beans.
    //
    // For example, consider two adjacent bowls containing 2 and 3 beans respectively, all other bowls being empty. The
    // following eight moves will finish the game:
    //
    // p334_beans.gif
    // You are given the following sequences:
    //
    // t0 = 123456.
    // 
    // ti =	ti-1 / 2, if ti-1 is even
    // ti = |ti-1 / 2| ^ 926252, if ti-1 is odd
    // where |x| is the floor function
    // and ^ is the bitwise XOR operator.
    // bi = ( ti mod 2**11) + 1.
    // The first two terms of the last sequence are b1 = 289 and b2 = 145.
    // If we start with b1 and b2 beans in two adjacent bowls, 3419100 moves would be required to finish the game.
    //
    // Consider now 1500 adjacent bowls containing b1, b2,..., b1500 beans respectively, all other bowls being empty. 
    // Find how many moves it takes before the game ends.
    const size_t masque = puissance::puissance<size_t>(2, 11u);
    nombre t = 123456;
    std::vector<nombre> beans;
    for (size_t i = 0; i < 1500; ++i) {
        if (t % 2 == 1) {
            t = (t/2) ^ 926252;
        } else {
            t /= 2;
        }
        
        beans.push_back(t % masque + 1);
    }
    nombre resultat = 0;
    nombre courant = 0;
    std::deque<nombre> holes {0};
    for (size_t i = 0;; ++i) {
        nombre bi = courant;
        if (i < beans.size()) {
            bi += beans[i];
        }
        if (bi < 2) break;
        
        courant = 0;
        std::ranges::for_each(holes, [](nombre &n){ n++; });
        while (bi > 1) {
            if (holes.size() == 1)
                holes.push_back(holes.front() + 1);
            
            nombre deplacer = std::min(holes.front(), bi);
            courant += deplacer;
            bi -= deplacer;
            nombre U = holes.front();
            nombre L = holes.front() - deplacer;
            resultat += U*(U + 1) / 2 - L*(L + 1) / 2;
            holes.front() -= deplacer;
            if (holes.front() == 0) {
                bi -= 1;
                holes.pop_front();
            }
        }
        if (bi == 0) {
            holes.push_front(0);
        }
    }
    
    return std::to_string(resultat);
}
