#include "problemes.h"
#include "combinatoire.h"
#include "utilitaires.h"
#include "nombre.h"

#include <fstream>

typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

typedef std::map<nombre, nombre> dictionnaire;

namespace
{
	nombre somme(const vecteur & arrangement)
	{
		nombre resultat = 0;
		for (size_t i = 0; i < arrangement.size(); ++i)
		{
			resultat += i * arrangement[i];
		}
		
		return resultat;
	}
	
	nombre combinaison(const vecteur & arrangement)
	{
		nombre resultat = 1;
		for (nombre a: arrangement)
			resultat *= combinatoire::factorielle(a);
			
		return resultat;
	}
	
	nombre W(size_t n, vecteur arrangement, size_t m)
	{
		if (n == 0)
			return combinatoire::factorielle<nombre>(20);
			
		nombre resultat = 0;
		for (size_t k = 1; k <= m; ++k)
		{
			arrangement[k] += 1;
			resultat += W(n-1, arrangement, k) / arrangement[k];
			arrangement[k] -= 1;
		}
		return resultat;
	}
	
	nombre A(size_t n, vecteur arrangement, size_t m)
	{
		if (n == 0)
		{
			if (somme(arrangement) == 70)
			{
				return W(10, arrangement, m) / combinaison(arrangement);
			}
			
			return 0;
		}
		
		nombre resultat = 0;
		for (size_t k = 1; k <= m; ++k)
		{
			arrangement[k] += 1;
			resultat += A(n-1, arrangement, k);
			arrangement[k] -= 1;
		}
		return resultat;
	}
}

ENREGISTRER_PROBLEME(240, "Top Dice")
{
    // There are 1111 ways in which five 6-sided dice (sides numbered 1 to 6) can be rolled so that 
    // the top three sum to 15. Some examples are: 
    //
    //  D1,D2,D3,D4,D5 = 4,3,6,3,5 
    //  D1,D2,D3,D4,D5 = 4,3,3,5,6 
    //  D1,D2,D3,D4,D5 = 3,3,3,6,6 
    //  D1,D2,D3,D4,D5 = 6,6,3,3,3 
    //
    // In how many ways can twenty 12-sided dice (sides numbered 1 to 12) be rolled so that the top
    // ten sum to 70?
    vecteur arrangement(13, 0);
    
    nombre resultat = A(10, arrangement, 12);
    return resultat.to_string();
}
