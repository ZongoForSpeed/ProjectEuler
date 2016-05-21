#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace matrice
{
    template<typename Nombre>
    using matrice = boost::numeric::ublas::matrix<Nombre>;
    
    template<typename Nombre>
    using vecteur = boost::numeric::ublas::vector<Nombre>;
    
    template<typename Nombre>
    matrice<Nombre> puissance_matrice(matrice<Nombre> base, size_t exposant)
    {
        matrice<Nombre> resultat(base.size1(), base.size2(), 0);
		for (size_t i = 0; i < base.size1(); ++i) resultat(i, i) = 1;
		
        while (exposant > 0)
        {
            if (exposant%2)
                resultat = boost::numeric::ublas::prod(resultat, base);
            exposant /= 2;
            base = boost::numeric::ublas::prod(base, base);
        }
        return resultat;
    }
    
    template<typename Nombre>
    matrice<Nombre> puissance_matrice(matrice<Nombre> base, size_t exposant, Nombre modulo)
	{
		matrice<Nombre> resultat(base.size1(), base.size2(), 0);
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
