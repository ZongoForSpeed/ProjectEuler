#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <bitset>

#include <boost/range/adaptor/reversed.hpp>

// #include <boost/rational.hpp>
// #include <boost/multiprecision/gmp.hpp>
//
// typedef boost::multiprecision::mpz_int nombre;

typedef unsigned long long nombre;
// typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

namespace
{
	struct Sliders
	{
		size_t			position_vide;
		std::string		etat;
		
		Sliders() : position_vide(0), etat("0000000000000000") {}
		
		Sliders(size_t _position, const std::string & _etat) : position_vide(_position), etat(_etat) {}

		static std::deque<char> directions(unsigned short position)
		{
			std::deque<char> d;
			if (position > 3)		d.push_back('D');
			if (position < 12)		d.push_back('U');
			if (position%4 != 0) 	d.push_back('R');
			if (position%4 != 3) 	d.push_back('L');
			return d;
		}
		
		static size_t suivant(char d, size_t position)
		{
			switch(d)
			{
			case 'L': return position + 1;
			case 'R': return position - 1;
			case 'U': return position + 4;
			case 'D': return position - 4;
			}
			
			return 0;
		}
		
		void deplace(char d)
		{
			size_t n_position = suivant(d, position_vide);
			std::swap(etat[position_vide], etat[n_position]);
			position_vide = n_position;
		}
		
		static std::map<char, Sliders> suivant(const Sliders & s)
		{
			std::map<char, Sliders> resultat;
			for (auto d: directions(s.position_vide))
			{
				Sliders n = s;
				n.deplace(d);
				resultat.insert(std::make_pair(d, n));
			}
			
			return resultat;
		}
		
		bool operator<(const Sliders & s) const
		{
			return to_string() < s.to_string();	
		}
		
		std::string to_string() const 
		{
			std::string m = etat;
			m[position_vide] = 'X';
			return m;
		}
		
		size_t count() const
		{
			return std::count(etat.begin(), etat.end(), '1');
		}
	};
	
	typedef std::string chemin;
	
	nombre checksum(const chemin & c)
	{
		nombre resultat = 0;
		for (auto d : c)
			resultat = (resultat * 243 + d)%100000007;

		return resultat;
	}
}

ENREGISTRER_PROBLEME(244, "Sliders")
{
    Timer timer("probleme 244");
    // You probably know the game Fifteen Puzzle. Here, instead of numbered tiles, we have seven red 
    // tiles and eight blue tiles.
	//
	// A move is denoted by the uppercase initial of the direction (Left, Right, Up, Down) in which 
	// the tile is slid, e.g. starting from configuration (S), by the sequence LULUR we reach the 
	// configuration (E):
	// 
	// 				(S)	p244_start.gif	, (E)	p244_example.gif
	// 
	// For each path, its checksum is calculated by (pseudocode):
	// 
	// 				checksum = 0
	// 				checksum = (checksum × 243 + m1) mod 100 000 007
	// 				checksum = (checksum × 243 + m2) mod 100 000 007
	//				         …
	//				checksum = (checksum × 243 + mn) mod 100 000 007
	//
	// where mk is the ASCII value of the kth letter in the move sequence and the ASCII values for 
	// the moves are:
	//
	// 				L	76
	//				R	82
	//				U	85
	//				D	68
	//
	// For the sequence LULUR given above, the checksum would be 19761398.
	// 
	// Now, starting from configuration (S), find all shortest ways to reach configuration (T).
	// 
	// 				(S)	p244_start.gif	, (T)	p244_target.gif
	//
	// What is the sum of all checksums for the paths having the minimal length?
	Sliders debut(0, "0011001100110011");
	Sliders fin(0, "0101101001011010");

	std::map<Sliders, std::vector<chemin>> chemins { {debut, {{}}}};
	std::set<Sliders> visites { debut };
	
	while(visites.find(fin) == visites.end())
	{
		std::map<Sliders, std::vector<chemin>> n_chemins;
		for (auto p: chemins)
		{
			auto suivants = Sliders::suivant(p.first);
			for (auto s: suivants)
			{
				if (visites.find(s.second) == visites.end())
				{
					for (chemin c: p.second)
					{
						c.push_back(s.first);
						n_chemins[s.second].push_back(c);
					}
				}
			}
		}
		
		if (n_chemins.empty())
			break;
		
		for (auto p: n_chemins)
			visites.insert(p.first);
			
		std::swap(chemins, n_chemins);
	}

	nombre resultat = 0;
	for (auto c: chemins[fin])
		resultat += checksum(c);

	std::cout << "Solution: " << resultat << std::endl;
}