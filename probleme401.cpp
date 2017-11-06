#include "problemes.h"
#include "arithmetiques.h"
#include "mp_nombre.h"
#include "polygonal.h"

typedef unsigned long long nombre;

namespace {
    nombre somme_carres(nombre n, nombre m) {
        nombre n1=n+1;
        nombre z=2*n+1;
        
        if (n%2 == 0) 
            n /= 2; 
        else 
            n1 /= 2; 
        if (n%3 == 0) 
            n /= 3; 
        else if (n1%3 == 0) 
            n1 /= 3; 
        else 
            z /= 3;
            
        n %= m;
        n1 %= m;
        z %= m;
        return ( ((n*n1)%m) * (z%m) )%m;
    }
}

ENREGISTRER_PROBLEME(401, "Sum of squares of divisors") {
    // The divisors of 6 are 1,2,3 and 6.
    // The sum of the squares of these numbers is 1+4+9+36=50.
    //
    // Let sigma2(n) represent the sum of the squares of the divisors of n. Thus sigma2(6)=50.
    // Let SIGMA2 represent the summatory function of sigma2, that is SIGMA2(n)=∑sigma2(i) for i=1 to n.
    //
    // The first 6 values of SIGMA2 are: 1,6,16,37,63 and 113.
    //
    // Find SIGMA2(10**15) modulo 10**9.
    nombre limite = puissance::puissance<nombre>(10, 15u);
    nombre modulo = 1'000'000'000;
    
    nombre racine_limite = arithmetiques::racine_carre(limite);
    
    nombre resultat = 0; 
    for(nombre n = 1; n < racine_limite + 1; ++n) {
        resultat += (n * n)%modulo * ((limite/n - n + 1)%modulo);
        resultat += modulo + somme_carres(limite/n, modulo) - somme_carres(n, modulo);
        resultat %= modulo;
    }
    
    return std::to_string(resultat);
}
