#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

namespace
{
    nombre maximum(const vecteur & v)
    {
        nombre max_tmp = 0;
        nombre max_total = 0;
        for (nombre n: v)
        {
            max_tmp = std::max(max_tmp + n, 0LL);
            max_total = std::max(max_total, max_tmp);
        }
        
        return max_total;
    }
}


void probleme149()
{
    Timer t("probleme 149");
	// Looking at the table below, it is easy to verify that the maximum possible sum of adjacent numbers
	// in any direction (horizontal, vertical, diagonal or anti-diagonal) is 16 (= 8 + 7 + 1).
	//
	//	                                           −2   5   3   2
	//                                              9  −6   5   1
	//                                              3   2   7   3
	//                                             −1   8  −4   8
	//
	// Now, let us repeat the search, but on a much larger scale:
	//
	// First, generate four million pseudo-random numbers using a specific form of what is known as a 
	// "Lagged Fibonacci Generator":
	// 
	// For 1 ≤ k ≤ 55, sk = [100003 − 200003.k + 300007.k^3] (modulo 1000000) − 500000.
	// For 56 ≤ k ≤ 4000000, sk = [sk−24 + sk−55 + 1000000] (modulo 1000000) − 500000.
	// 
	// Thus, s10 = −393027 and s100 = 86613.
	// 
	// The terms of s are then arranged in a 2000×2000 table, using the first 2000 numbers to fill the 
	// first row (sequentially), the next 2000 numbers to fill the second row, and so on.
	// 
	// Finally, find the greatest sum of (any number of) adjacent entries in any direction (horizontal,
	// vertical, diagonal or anti-diagonal).
	nombre taille = 2000;
	vecteur s(taille * taille + 1, 0);
	for (nombre k = 1; k < 56; ++k)
	{
		s.at(k) = (100003 - 200003*k + 300007*k*k*k)%1000000 - 500000;
	}
	
	for (nombre k = 56; k < taille * taille + 1; ++k)
	{
		s.at(k) = (s.at(k-24) + s.at(k-55) + 1000000)%1000000 - 500000;
	}
	
	// std::cout << "s(10) = " << s.at(10) << std::endl;
	// std::cout << "s(100) = " << s.at(100) << std::endl;
	
	matrice m(taille, vecteur(taille, 0));
	
	for (size_t n = 1; n < s.size(); ++n)
	{
		m[(n-1)/taille][(n-1)%taille] = s.at(n);
	}
    
    nombre resultat = 0;
    // Somme ligne
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; j < m.size(); ++j)
    		v.push_back(m[i][j]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    // Somme colonne
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; j < m.size(); ++j)
    		v.push_back(m[j][i]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    // Somme diagonale avec i = 0
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; i+j < m.size(); ++j)
    		v.push_back(m[i+j][j]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    // Somme diagonale avec j = 0 
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; i+j < m.size(); ++j)
    		v.push_back(m[j][i+j]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    // Somme anti-diagonale avec i = 0 
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; j < i + 1; ++j)
    		v.push_back(m[i-j][j]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    // Somme anti-diagonale avec i = m.size() - 1 
    for (size_t i = 0; i < m.size(); ++i)
    {
    	vecteur v;
    	for (size_t j = 0; i + j < m.size(); ++j)
    		v.push_back(m[i + j][m.size() - 1 - j]);
    		
    	resultat = std::max(resultat, maximum(v));
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
