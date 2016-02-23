#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/assignment.hpp> 

// #include <boost/multiprecision/cpp_int.hpp>
// typedef boost::multiprecision::mpz_int nombre;
typedef long long nombre;

typedef boost::numeric::ublas::matrix<nombre> matrice;

typedef std::vector<nombre> vecteur;

namespace
{
	matrice puissance_matricielle(matrice base, size_t exposant, nombre modulo)
	{
		matrice resultat(base.size1(), base.size2(), 0);
		for (size_t i = 0; i < base.size1(); ++i) resultat(i, i) = 1;
		while (exposant > 0)
        {
            if (exposant%2)
            {
            	resultat = boost::numeric::ublas::prod(resultat, base);
            	for (auto & m: resultat.data()) m %= modulo;
            }
            exposant /= 2;
            base = boost::numeric::ublas::prod(base, base);
           	for (auto & m: base.data()) m %= modulo;
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(237, "Tours on a 4 x n playing board")
{
    Timer timer("probleme 237");
    // Let T(n) be the number of tours over a 4 × n playing board such that:
	// 
	// The tour starts in the top left corner.
	// The tour consists of moves that are up, down, left, or right one square.
	// The tour visits each square exactly once.
	// The tour ends in the bottom left corner.
	// The diagram shows one tour over a 4 × 10 board:
	//
	//					https://projecteuler.net/project/images/p237.gif
	//
	//T(10) is 2329. What is T(1012) modulo 108?
	size_t n = 1000000000000LL;
	// T[n]=2*T[n-1]+2*T[n-2]-2*T[n-3]+T[n-4]
	matrice m(4, 4, 0);
	m <<= 2, 2,-2, 1,
	      1, 0, 0, 0,
	      0, 1, 0, 0,
	      0, 0, 1, 0;
	
	boost::numeric::ublas::vector<nombre> i(4);
	i <<= 8, 4, 1, 1;
	
	auto m_n = puissance_matricielle(m, n - 4, 100000000LL);
	nombre resultat = boost::numeric::ublas::prod(m_n, i)(0);

    std::cout << "Solution: " << resultat << std::endl;
}
