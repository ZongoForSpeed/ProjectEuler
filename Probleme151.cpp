#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

typedef std::vector<unsigned short> envelope;
typedef boost::rational<nombre> fraction;

namespace
{
    fraction calculEsperance(const envelope & e)
	{
        static std::map<envelope, fraction> cache;
    
		auto it = cache.find(e);
		if (it != cache.end())
			return it->second;

		fraction resultat(0, 1);
		if (!e.empty()) 
		{
			for (size_t i = 0; i < e.size(); i++) 
			{
				envelope nouvelleEnvelope(e);
				unsigned short sheet = e[i];
				nouvelleEnvelope.erase(nouvelleEnvelope.begin() + i);
				for (unsigned short j = sheet + 1; j <= 5; j++)
					nouvelleEnvelope.push_back(j);
				std::sort(nouvelleEnvelope.begin(), nouvelleEnvelope.end());
				resultat += calculEsperance(nouvelleEnvelope);
			}
		
			resultat /= e.size();
			if (e.size() == 1)
				resultat++;
		}
		
		cache[e] = resultat;		
		return resultat;
	}
}

void probleme151()
{
    Timer timer("probleme 151");
	// A printing shop runs 16 batches (jobs) every week and each batch requires a sheet of special 
	// colour-proofing paper of size A5.
    //
    // Every Monday morning, the foreman opens a new envelope, containing a large sheet of the special 
    // paper with size A1.
    //
    // He proceeds to cut it in half, thus getting two sheets of size A2. Then he cuts one of them in
    // half to get two sheets of size A3 and so on until he obtains the A5-size sheet needed for the
    // first batch of the week.
    // 
    // All the unused sheets are placed back in the envelope.
    // 
    // At the beginning of each subsequent batch, he takes from the envelope one sheet of paper at 
    // random. If it is of size A5, he uses it. If it is larger, he repeats the 'cut-in-half' procedure
    // until he has what he needs and any remaining sheets are always placed back in the envelope.
    //  
    // Excluding the first and last batch of the week, find the expected number of times (during each week)
    // that the foreman finds a single sheet of paper in the envelope.
    //
    // Give your answer rounded to six decimal places using the format x.xxxxxx .
	envelope e {1};
	fraction f = calculEsperance(e) - 2;
	double resultat = 1;
	resultat *= f.numerator();
	resultat /= f.denominator();
	std::cout << std::setprecision(6);
    std::cout << "Solution: " << resultat << std::endl;
}
