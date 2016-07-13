#include "problemes.h"
#include "premiers.h"
#include "puissance.h"

#include <set>
#include <deque>

class Probleme500
{
	typedef unsigned long long nombre;
	typedef std::deque<nombre> vecteur;
	struct Facteur
	{
	    Facteur(nombre v, nombre p, nombre e) :
	        valeur(v), premier(p), exposant(e)
	    {}
	    bool operator<(const Facteur& op) const
	    {
	        if (valeur != op.valeur)
	            return valeur < op.valeur;
	        else if (premier != op.premier)
	            return premier < op.premier;
	        else
	            return exposant < op.exposant;
	    }
	    nombre valeur;
	    nombre premier;
	    nombre exposant;
	};
	typedef std::set<Facteur> Facteurs;
    // The number of divisors of 120 is 16.
    // In fact 120 is the smallest number having 16 divisors.
    // 
    // Find the smallest number with 2^500500 divisors.
    // Give your answer modulo 500500507.
	nombre limite;
public:
	Probleme500(nombre l = 500500) : limite(l) {}
    nombre algorithme()
    {
        vecteur premiers;
        premiers::crible<nombre>(100000000, std::back_inserter(premiers));

        Facteurs facteurs;
        vecteur resultat;
        for (size_t i = 0; i < premiers.size(); ++i)
        {
            facteurs.insert(Facteur(premiers[i], i, 1));
        }
        for (nombre i = 0; i < limite; ++i)
        {
            Facteur facteur = *(facteurs.begin());
            facteurs.erase(facteurs.begin());
            if (facteur.premier == resultat.size())
                resultat.push_back(facteur.exposant);
            else
                resultat[facteur.premier] += facteur.exposant;
            facteur.valeur *= facteur.valeur;
            facteur.exposant *= 2;
            facteurs.insert(facteur);
        }
        nombre p = 500500507;
        nombre r = 1;
        for (size_t n = 0; n < resultat.size(); ++n)
        {
            r *= puissance::puissance_modulaire(premiers[n], resultat[n], p);
            r %= p;
        }
        return r;
    }
};

ENREGISTRER_PROBLEME(500, "Problem 500!!!")
{
	Probleme500 p;
	return std::to_string(p.algorithme());
}
