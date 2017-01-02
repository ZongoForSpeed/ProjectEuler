
#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "grand_nombre.h"

typedef std::vector<grand_nombre> vecteur;

namespace
{
    grand_nombre combinaison(size_t m, size_t n)
    {
        return grand_nombre::factorielle(m * n) / grand_nombre::puissance(grand_nombre::factorielle(n), m);
    }
    
    grand_nombre f(size_t m, size_t n, const vecteur & premiers)
    {
        grand_nombre somme = 0;
        for (size_t d = 1; d < n + 1; ++d)
        {
            if (n % d == 0)
                somme += combinaison(m, d) * arithmetiques::phi<grand_nombre>(n / d, premiers);
        }
        return somme / (m*n);
    }
}

ENREGISTRER_PROBLEME(281, "Pizza Toppings")
{
    // You are given a pizza (perfect circle) that has been cut into m·n equal 
    // pieces and you want to have exactly one topping on each slice.
    //
    // Let f(m,n) denote the number of ways you can have toppings on the pizza 
    // with m different toppings (m ≥ 2), using each topping on exactly n slices 
    // (n ≥ 1). 
    // Reflections are considered distinct, rotations are not.
    //
    // Thus, for instance, f(2,1) = 1, f(2,2) = f(3,1) = 2 and f(3,2) = 16. 
    // f(3,2) is shown below:
    //
    // p281_pizza.gif
    // Find the sum of all f(m,n) such that f(m,n) ≤ 10**15.
    vecteur premiers;
    premiers::crible235<grand_nombre>(1000, std::back_inserter(premiers));
    
    grand_nombre resultat = 0;
    grand_nombre limite = grand_nombre::puissance(10, 15);
    
    for (size_t m = 2; f(m, 1, premiers) <= limite; ++m)
    for (size_t n = 1; f(m, n, premiers) <= limite; ++n)
    {
        resultat += f(m, n, premiers);
    }

    return resultat.to_string();
}
