#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(121, "Disc game prize fund")
{
    // A bag contains one red disc and one blue disc. In a game of chance a player takes a disc at 
    // random and its colour is noted. After each turn the disc is returned to the bag, an extra red
    // disc is added, and another disc is taken at random.
    //
    // The player pays £1 to play and wins if they have taken more blue discs than red discs at the 
    // end of the game.
    //
    // If the game is played for four turns, the probability of a player winning is exactly 11/120, 
    // and so the maximum prize fund the banker should allocate for winning in this game would be £10
    // before they would expect to incur a loss. Note that any payout will be a whole number of pounds
    // and also includes the original £1 paid to play the game, so in the example given the player 
    // actually wins £9.
    //
    // Find the maximum prize fund that should be allocated to a single game in which fifteen turns are
    // played.
    nombre limite = 15;
    std::vector<fraction> probabilites;
    for (nombre n = 1; n < limite + 1; ++n)
    {
        probabilites.push_back(fraction(1, n + 1));
    }
    
    fraction probabilite;
    
    for (nombre bleu = limite / 2 + 1; bleu < limite + 1; ++bleu)
    {
        vecteur possibilite;
        possibilite.insert(possibilite.end(), limite - bleu, 0);
        possibilite.insert(possibilite.end(), bleu, 1);
        do
        {
            fraction p(1);
            for (size_t n = 0; n < limite; ++n)
            {
                if (possibilite.at(n) == 1)
                    p *= probabilites.at(n);
                else
                    p *= 1 - probabilites.at(n);
            }
            
            probabilite += p;
        }
        while (std::next_permutation(possibilite.begin(), possibilite.end()));
    }

    nombre resultat = probabilite.denominator() / probabilite.numerator();
    return std::to_string(resultat);
}
