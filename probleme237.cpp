#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "matrice.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/assignment.hpp> 

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(237, "Tours on a 4 x n playing board")
{
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
	matrice::matrice<nombre> m(4, 4, 0);
	m <<= 2, 2,-2, 1,
	      1, 0, 0, 0,
	      0, 1, 0, 0,
	      0, 0, 1, 0;
	
	matrice::vecteur<nombre> i(4);
	i <<= 8, 4, 1, 1;
	
	auto m_n = matrice::puissance_matrice(m, n - 4, 100000000LL);
	nombre resultat = boost::numeric::ublas::prod(m_n, i)(0);

    std::cout << "Solution: " << resultat << std::endl;
}
