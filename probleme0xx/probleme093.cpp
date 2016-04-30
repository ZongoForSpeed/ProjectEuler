#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

namespace
{
    void test(const std::vector<fraction> & n, std::set<nombre> & p) 
    {
    	if (n.size() == 1) 
    	{ 
    	    if (n.front().numerator()%n.front().denominator() == 0)
    	        p.insert(n.front().numerator() / n.front().denominator());
    		return;
    	}
    	for(nombre i = 0; i < n.size(); ++i)
    	for(nombre j = i + 1; j < n.size(); ++j)
    	{
			fraction a = n[i];
			fraction b = n[j];
			auto m = n;
			m.erase(std::next(m.begin(),j));
			m[i] = a + b;
			test(m, p);
			m[i] = a * b;
			test(m, p);
			if(a >= b) 
			{
				m[i] = a - b;
				test(m, p);
			}
			if(a <= b) 
			{
				m[i] = b - a;
				test(m, p);
			}
			if(a != 0) 
			{
				m[i] = b / a;
				test(m, p);
			}
			if(b != 0) 
			{
				m[i] = a / b;
				test(m, p);
			}
    	}
    }

}

ENREGISTRER_PROBLEME(93, "Arithmetic expressions")
{
    // By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and making use of the 
    // four arithmetic operations (+, −, *, /) and brackets/parentheses, it is possible to form 
    // different positive integer targets.
    //
    // For example,
    // 
    //      8 = (4 * (1 + 3)) / 2
    //      14 = 4 * (3 + 1 / 2)
    //      19 = 4 * (2 + 3) − 1
    //      36 = 3 * 4 * (2 + 1)
    //
    // Note that concatenations of the digits, like 12 + 34, are not allowed.
    //
    // Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different target numbers of
    // which 36 is the maximum, and each of the numbers 1 to 28 can be obtained before encountering
    // the first non-expressible number.
    // 
    // Find the set of four distinct digits, a < b &lt c < d, for which the longest set of consecutive
    // positive integers, 1 to n, can be obtained, giving your answer as a string: abcd.
    vecteur iteration;
    for (nombre n = 1; n < 10000; ++n) iteration.push_back(n);
    vecteur resultat;
    nombre maximum = 0;
    for (nombre a = 0; a < 10; ++a)
    for (nombre b = a + 1; b < 10; ++b)
    for (nombre c = b + 1; c < 10; ++c)
    for (nombre d = c + 1; d < 10; ++d)
    {
        std::vector<fraction> v = {a, b, c, d};
        std::set<nombre> e;
        test(v, e);
        
        vecteur difference;
        std::set_difference(iteration.begin(), iteration.end(), e.begin(), e.end(), 
                            std::inserter(difference, difference.begin()));
        if (difference.front() > maximum)
        {
            maximum = difference.front();
            resultat = {a, b, c, d};
        }
    }

    
    std::cout << "Solution: " << chiffres::conversion_nombre<nombre>(resultat.begin(), resultat.end()) << std::endl;
}
