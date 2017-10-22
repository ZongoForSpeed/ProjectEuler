#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "multidimension.h"
#include "timer.h"

typedef size_t nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::vector<nombre> vecteur;

namespace {
    template<typename T>
    T LSB(T x) {
        return ((x^x-1) + 1) >> 1;
    }

    nombre somme(const vecteur &fenwick, nombre x, nombre modulo)
    {
    	nombre s = 0;
    	for(;x > 0; x -= LSB(x)) { 
    	    s += fenwick[x];
    	    s %= modulo;
    	}
    	return s;
    }
    
    void ajout(vecteur &fenwick, nombre x, nombre d, nombre modulo)
    {
    	for(;x < fenwick.size(); x += LSB(x)) {
    	    fenwick[x] += d;
    	    fenwick[x] %= modulo;
    	}
    }
}

ENREGISTRER_PROBLEME(337, "Totient Stairstep Sequences")
{
    // Let {a1, a2,..., an} be an integer sequence of length n such that:
    //
    // a1 = 6
    // for all 1 ≤ i < n : φ(ai) < φ(ai+1) < ai < ai+1
    // Let S(N) be the number of such sequences with an ≤ N.
    // For example, S(10) = 4: {6}, {6, 8}, {6, 8, 9} and {6, 10}.
    // We can verify that S(100) = 482073668 and S(10 000) mod 108 = 73808307.
    //
    // Find S(20 000 000) mod 108.
    //
    // φ denotes Euler's totient function.
    const nombre limite = 20'000'000;
    const nombre modulo = 100'000'000;
    
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));
    
    vecteur phi(limite + 1, 0);
    std::iota(phi.begin(), phi.end(), 0ul);

    for (auto &p: premiers) {
        for (nombre n = p; n < limite + 1; n += p) {
            phi[n] /= p;
            phi[n] *= p - 1;
        }
    }
    
    vecteur fenwick(limite + 1, 0);
    
    nombre resultat = 0;
	for(nombre n = limite; n > 5; n--)
	{
		nombre k = phi[n];
		resultat = modulo + 1 + somme(fenwick, n - 1, modulo) - somme(fenwick, k, modulo);
		ajout(fenwick, k, resultat, modulo);
	}
	
	resultat %= modulo;
    return std::to_string(resultat);
}
