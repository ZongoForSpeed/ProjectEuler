#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "grand_nombre.h"

typedef std::vector<grand_nombre> vecteur;

namespace
{
    grand_nombre G0(grand_nombre n)
    {
        return combinatoire::catalan<grand_nombre>(n - 2); 
    }
    
    int signe(grand_nombre n)
    {
        return (n % 2 == 0) ? 1 : -1;
    }
    
    grand_nombre G1(grand_nombre n, grand_nombre k1)
    {
        grand_nombre somme = 0;
        for (grand_nombre j = 0; 2*j < k1 + 1; ++j)
        {
            somme += signe(j)*combinatoire::coefficient_binomial<grand_nombre>(k1-j,j)*G0(n-j);
        }
        
        return somme;
    }
    
    grand_nombre G2(grand_nombre n, grand_nombre k1, grand_nombre k2)
    {
        grand_nombre somme = 0;
        for (grand_nombre j = 0; 2*j < k1 + 1; ++j)
        {
            somme += signe(j)*combinatoire::coefficient_binomial<grand_nombre>(k1-j,j)*G1(n-j, k2);
        }
        
        return somme;
    }
    
    grand_nombre G3(grand_nombre n, grand_nombre k1, grand_nombre k2, grand_nombre k3)
    {
        grand_nombre somme = 0;
        for (grand_nombre j = 0; 2*j < k1 + 1; ++j)
        {
            somme += signe(j)*combinatoire::coefficient_binomial<grand_nombre>(k1-j,j)*G2(n-j, k2, k3);
        }
        
        return somme;
    }
    
    grand_nombre G4(grand_nombre n, grand_nombre k1, grand_nombre k2, grand_nombre k3, grand_nombre k4)
    {
        grand_nombre somme = 0;
        for (grand_nombre j = 0; 2*j < k1 + 1; ++j)
        {
            somme += signe(j)*combinatoire::coefficient_binomial<grand_nombre>(k1-j,j)*G3(n-j, k2, k3, k4);
        }
        
        return somme;
    }
    
    grand_nombre C(grand_nombre n)
    {
        return G4(4*n, n, n, n, n);
    }
}

ENREGISTRER_PROBLEME(270, "Cutting Squares")
{
    // A square piece of paper with integer dimensions N×N is placed with a corner
    // at the origin and two of its sides along the x- and y-axes. Then, we cut 
    // it up respecting the following rules:
    //
    //  . We only make straight cuts between two points lying on different sides
    //    of the square, and having integer coordinates.
    //  . Two cuts cannot cross, but several cuts can meet at the same border
    //    point.
    //  . Proceed until no more legal cuts can be made.
    // 
    // Counting any reflections or rotations as distinct, we call C(N) the number
    // of ways to cut an N×N square. For example, C(1) = 2 and C(2) = 30 (shown 
    // below).
    //
    //                          p270_CutSquare.gif
    // 
    // What is C(30) mod 10**8 ?
    grand_nombre resultat = C(30) % 100000000;
    return resultat.to_string();
}
