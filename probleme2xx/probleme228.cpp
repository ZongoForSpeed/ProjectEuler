#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// #include <boost/multiprecision/cpp_int.hpp>
//
// typedef boost::multiprecision::mpz_int nombre;
typedef unsigned long long nombre;
typedef std::pair<long double, long double> coordonnee;

namespace
{
	long double norme(const coordonnee & v)
	{
		return std::sqrt(v.first*v.first + v.second*v.second);
	}
	
	std::vector<coordonnee> convertion(const std::vector<coordonnee> & v)
	{
		if (v.empty())
			return v;
			
		std::vector<coordonnee> resultat { std::make_pair(v.front().first - v.back().first, v.front().second - v.back().second) };
		for (size_t k = 1; k < v.size(); ++k)
		{
			auto p = std::make_pair(v.at(k).first - v.at(k-1).first, v.at(k).second - v.at(k-1).second);
			auto n = norme(p);
			p.first /= n;
			p.second /= n;
			resultat.push_back(p);
		}
		
		return resultat;
	}
	
	std::vector<coordonnee> S(size_t n)
	{
		std::vector<coordonnee> s;
		for (size_t k = 0; k < n; ++k)
		{
			const long double x = (2.0*k-1)/n + M_PI;
			s.push_back(std::make_pair(std::cos(x), std::sin(x)));
		}
		
		return s;
	}

	long double produit_scalaire(const coordonnee & v1, const coordonnee & v2)
	{
		return (v1.first * v2.first + v1.second * v2.second) / (norme(v1) * norme(v2));
	}
}

ENREGISTRER_PROBLEME(228, "Minkowski Sums")
{
    // Let Sn be the regular n-sided polygon – or shape – whose vertices vk (k = 1,2,…,n) have coordinates:
	//
	// 			x_k = cos( 2*(k-1)/n × 180° )
	// 			y_k = sin( 2*(k-1)/n × 180° )
	// 
	// Each Sn is to be interpreted as a filled shape consisting of all points on the perimeter and in
	// the interior.
	// 
	// The Minkowski sum, S+T, of two shapes S and T is the result of adding every point in S to every 
	// point in T, where point addition is performed coordinate-wise: (u, v) + (x, y) = (u+x, v+y).
	// 
	// For example, the sum of S3 and S4 is the six-sided shape shown in pink below:
	// 
	//							picture showing S_3 + S_4
	//
	// How many sides does S1864 + S1865 + … + S1909 have?
	std::set<coordonnee, std::function<bool(const coordonnee & v1, const coordonnee & v2)>> minkowski([] (const coordonnee & v1, const coordonnee & v2){
		if (std::abs(1.0-produit_scalaire(v1, v2)) < 0.0000000000001)
			return false;
			
		return v1 < v2;
	});
	
	for (size_t n = 1864; n <= 1909; ++n)
	{
		auto Sn = convertion(S(n));
		minkowski.insert(Sn.begin(), Sn.end());
	}

	nombre resultat = minkowski.size();
    return std::to_string(resultat);
}
