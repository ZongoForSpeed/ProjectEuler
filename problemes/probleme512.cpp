#include <numeric>
#include "problemes.h"
#include "premiers.h"
#include "arithmetique.h"
#include "timer.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(512, "Sums of totients of powers") {
    // Let φ(n) be Euler's totient function.
    //
    // Let f(n)=(∑i=1..n φ(n**i)) mod (n+1).
    //
    // Let g(n)=∑i=1..n f(i).
    //
    //     g(100) = 2007.
    //
    // Find g(5×10**8).
    nombre limite = 500'000'000;

    std::vector<nombre> phi(limite + 1, 0);

    { 
        Timer t("crible");
        std::vector<bool> crible(limite + 1, true);
        std::iota(phi.begin(), phi.end(), 0ul);
        for (nombre i = 2; i < limite + 1; ++i) {
            if (crible[i]) {
                for (nombre j = i; j < limite + 1; j += i) {
                    crible[j] = false;
                    phi[j] /= i;
                    phi[j] *= i-1;
                }
            }
        }    
        
    }

    // f(n) = phi(n) * (1 - n**n) / (1 - n) mod (n + 1) 
    // mpz_nombre fn = (mpz_nombre::puissance(n, n) - 1) / (n - 1) * phi[n];
    // fn %= n + 1;
    // return fn.get<nombre>();
    
    nombre resultat = 0;
    for (nombre n = 1; n < limite + 1; n += 2) {
        resultat += phi[n];
    }
    
    return std::to_string(resultat);
}
