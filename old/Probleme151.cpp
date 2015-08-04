#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/rational.hpp>

#define foreach BOOST_FOREACH

class Probleme151
{
public:
	// A printing shop runs 16 batches (jobs) every week and each batch requires 
	// a sheet of special colour-proofing paper of size A5.
	//
	// Every Monday morning, the foreman opens a new envelope, containing a large 
	// sheet of the special paper with size A1.
	//
	// He proceeds to cut it in half, thus getting two sheets of size A2. Then he 
	// cuts one of them in half to get two sheets of size A3 and so on until he 
	// obtains the A5-size sheet needed for the first batch of the week.
	//
	// All the unused sheets are placed back in the envelope.
	//
	// At the beginning of each subsequent batch, he takes from the envelope one 
	// sheet of paper at random. If it is of size A5, he uses it. If it is larger, 
	// he repeats the 'cut-in-half' procedure until he has what he needs and any 
	// remaining sheets are always placed back in the envelope.
	//
	// Excluding the first and last batch of the week, find the expected number of
	// times (during each week) that the foreman finds a single sheet of paper in
	// the envelope.
	//
	// Give your answer rounded to six decimal places using the format x.xxxxxx .

	enum Feuille { 
		A1,
		A2,
		A3,
		A4,
		A5
	};

	typedef std::vector<Feuille> Envelope;
	typedef unsigned long long Nombre;
	typedef boost::rational<Nombre> Fraction;

	typedef std::pair<Envelope, Nombre> Paire;
	typedef std::map<Envelope, Nombre> Batches;


	std::string toString(const Feuille & f)
	{
		switch(f)
		{
			case A1: return "A1";
			case A2: return "A2";
			case A3: return "A3";
			case A4: return "A4";
			case A5: return "A5";
		}

		return "";
	}

	std::string toString(const Envelope & e)
	{
		std::ostringstream oss;
		bool premier = true;
		foreach(const Feuille & f, e)
		{
			if (!premier)
				oss << ", ";
			else
				premier = false;
			oss << toString(f);
		}

		return oss.str();
	}

	std::string toString(const Batches & b)
	{
		std::ostringstream oss;
		bool premier = true;
		foreach(const Paire & p, b)
		{
			if (!premier)
				oss << std::endl;
			else
				premier = false;
			oss << "[" << toString(p.first) << "] ==> " << p.second;
		}

		return oss.str();
	}

	void removeOne(Envelope & e, Feuille f){
		Envelope::iterator found = std::find(e.begin(), e.end(), f) ;
		if (found!=e.end())
			e.erase(found);
	}

	void suivant(const Batches & entree, Batches & sortie)
	{
		sortie.clear();

		foreach(const Paire & p, entree)
		{
			foreach(const Feuille & f, p.first)
			{
				Envelope copie = p.first;
				removeOne(copie, f);
				switch(f)
				{
				case A1: copie.push_back(A2);
				case A2: copie.push_back(A3);
				case A3: copie.push_back(A4);
				case A4: copie.push_back(A5);
				default: break;
				}

				std::sort(copie.begin(), copie.end());
				Batches::iterator it = sortie.find(copie);
				if (it != sortie.end())
					it->second += p.second;
				else
					sortie.insert(std::make_pair(copie, p.second));					
			}
		}
	}

	void algorithme()
	{
		Envelope init;
		init.push_back(A2);
		init.push_back(A3);
		init.push_back(A4);
		init.push_back(A5);

		Batches b;
		b[init] = 1;

		Fraction esperance(0,1);

		for (unsigned jour = 1; jour < 17; ++jour)
		{
			Batches tmp;
			suivant(b, tmp);
			std::cout << "Batch " << jour << std::endl;
			std::cout << toString(b) << std::endl;

			Nombre numerateur = 0;
			Nombre denominator = 0;

			foreach(const Paire & p, b)
			{
				denominator += p.second;
				if (p.first.size() == 1)
					numerateur += p.second;
			}

			Fraction f(numerateur, denominator);

			std::cout << "probabilite = " << f << std::endl;
			esperance += f;

			std::swap(b, tmp);
		}

		std::cout << "esperance = " << esperance - 1 << std::endl;
	}
};

class Probleme151bis
{
public:
	typedef std::vector<unsigned> Envelope;
	typedef unsigned long long Nombre;
	typedef boost::rational<Nombre> Fraction;

	typedef std::map<Envelope, Fraction> Esperance;

	Esperance cacheEsperance;

	void algorithme()
	{
		Envelope e;
		e.push_back(1);
		std::cout << calculEsperance(e) - 2 << std::endl;
	}

	Fraction calculEsperance(const Envelope & e)
	{
		Esperance::const_iterator it = cacheEsperance.find(e);
		if (it != cacheEsperance.end())
			return it->second;

		Fraction resultat(0, 1);
		if (!e.empty()) 
		{
			for (size_t i = 0; i < e.size(); i++) 
			{
				Envelope nouvelleEnvelope(e);
				unsigned sheet = e[i];
				nouvelleEnvelope.erase(nouvelleEnvelope.begin() + i);
				for (unsigned j = sheet + 1; j <= 5; j++)
					nouvelleEnvelope.push_back(j);
				std::sort(nouvelleEnvelope.begin(), nouvelleEnvelope.end());
				resultat += calculEsperance(nouvelleEnvelope);
			}
		
			resultat /= e.size();
			if (e.size() == 1)
				resultat++;
		}
		
		cacheEsperance[e] = resultat;		
		return resultat;
	}
};

int main(int argc, char** argv)
{
	Probleme151bis p;
	p.algorithme();
	
	return 0;
}

