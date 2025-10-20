#include "../problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(375, "Minimum of subsequences") {
    // Let Sn be an integer sequence produced with the following pseudo-random number generator:
    //
    // S0	= 	290797 
    // Sn+1	= 	Sn² mod 50515093
    //
    // Let A(i, j) be the minimum of the numbers Si, Si+1, ... , Sj for i ≤ j.
    // Let M(N) = ΣA(i, j) for 1 ≤ i ≤ j ≤ N.
    // We can verify that M(10) = 432256955 and M(10 000) = 3264567774119.
    //
    // Find M(2 000 000 000).
    const nombre limite = 2'000'000'000;
    
    nombre somme = 0;
    nombre resultat = 0;
    
    nombre s = 290'797;
    nombre modulo = 50'515'093;

    std::deque<paire> q;
    q.emplace_back(0, 0);
    for (nombre i = 1; i < limite + 1; ++i) {
        s = s*s % modulo;
        
        while (q.size() > 1 && q.front().first > s) {
            auto q0 = q.front(); 
            q.pop_front();
            
            somme -= (q0.second - q.front().second) * q0.first;
        }
        
        somme += (i - q.front().second)*s;
        q.emplace_front(s, i);
        resultat += somme;
    }
    
    return std::to_string(resultat);
}
