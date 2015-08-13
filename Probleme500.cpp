#include "Premiers.h"
#include "Puissance.h"
#include "Timer.h"

#include <set>

class Probleme500
{
	typedef unsigned long long nombre;
	typedef std::vector<nombre> vecteur;

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

    void algorithme()
    {
        vecteur premiers;
        {
            Timer t("crible");
            premiers::crible(100000000, premiers);
        }

        Facteurs facteurs;
        vecteur resultat;
        {
        	Timer t("algorithme");
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

            std::cout << "Resultat = " << r << std::endl;
        }
    }
    
private:

};

int main()
{
	Probleme500 p;
	p.algorithme();
	return 0;
}
