#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(182, "RSA encryption")
{
    Timer timer("probleme 182");
    // The RSA encryption is based on the following procedure:
    //
    // Generate two distinct primes p and q.
    // Compute n=pq and φ=(p-1)(q-1).
    // Find an integer e, 1<e<φ, such that gcd(e,φ)=1.
    //
    // A message in this system is a number in the interval [0,n-1].
    // A text to be encrypted is then somehow converted to messages (numbers in the interval [0,n-1]).
    // To encrypt the text, for each message, m, c=m^e mod n is calculated.
    //
    // To decrypt the text, the following procedure is needed: calculate d such that ed=1 mod φ, then
    // for each encrypted message, c, calculate m=c^d mod n.
    //
    // There exist values of e and m such that m^e mod n=m.
    // We call messages m for which m^e mod n=m unconcealed messages.
    //
    // An issue when choosing e is that there should not be too many unconcealed messages. 
    // For instance, let p=19 and q=37.
    // Then n=19*37=703 and φ=18*36=648.
    // If we choose e=181, then, although gcd(181,648)=1 it turns out that all possible messages
    // m (0≤m≤n-1) are unconcealed when calculating m^e mod n.
    // For any valid choice of e there exist some unconcealed messages.
    // It's important that the number of unconcealed messages is at a minimum.
    //
    // Choose p=1009 and q=3643.
    // Find the sum of all values of e, 1<e<φ(1009,3643) and gcd(e,φ)=1, so that the number of unconcealed
    // messages for this value of e is at a minimum.
    nombre p = 1009;
    nombre q = 3643;
    nombre n = p*q;
    
    vecteur premiers;
    premiers::crible235<nombre>(n, std::back_inserter(premiers));
    
    nombre phi_n = (p - 1)*(q - 1);
    
    std::map<nombre, nombre> decomposition;
    arithmetiques::decomposition(phi_n, premiers, decomposition);

    std::vector<bool> crible(phi_n, true);
    crible[0] = false;
    crible[1] = false;
    for (auto d: decomposition)
    {
        for (nombre q = d.first; q < phi_n; q += d.first)
            crible[q] = false;
    }
    
    vecteur exposants;
    for (nombre i = 0; i < phi_n; ++i) if (crible.at(i)) exposants.push_back(i);

    nombre resultat = 0;
    nombre minimum_collision = n;
    for (auto e: exposants)
    {
        nombre collision = (arithmetiques::PGCD(e-1,p-1) + 1) * (arithmetiques::PGCD(e-1,q-1) + 1);
        if (collision < minimum_collision)
        {
            resultat = e;
            minimum_collision = collision;
        }
        else if (collision == minimum_collision)
            resultat += e;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
