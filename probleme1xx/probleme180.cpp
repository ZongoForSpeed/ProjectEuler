#include "problemes.h"
#include "arithmetiques.h"
#include "polygonal.h"
#include "mp_nombre.h"

typedef std::vector<size_t> vecteur;
typedef std::vector<vecteur> matrice;
typedef boost::rational<size_t> fraction;

ENREGISTRER_PROBLEME(180, "Rational zeros of a function of three variables") {
    // For any integer n, consider the three functions
    //
    // f1,n(x,y,z) = x^n+1 + y^n+1 − z^n+1
    // f2,n(x,y,z) = (xy + yz + zx)*(x^n-1 + y^n-1 − z^n-1)
    // f3,n(x,y,z) = xyz*(x^n-2 + y^n-2 − z^n-2)
    //
    // and their combination
    //
    // fn(x,y,z) = f1,n(x,y,z) + f2,n(x,y,z) − f3,n(x,y,z)
    //
    // We call (x,y,z) a golden triple of order k if x, y, and z are all rational numbers of the form a / b with
    // 0 < a < b ≤ k and there is (at least) one integer n, so that fn(x,y,z) = 0.
    //
    // Let s(x,y,z) = x + y + z.
    // Let t = u / v be the sum of all distinct s(x,y,z) for all golden triples (x,y,z) of order 35.
    // All the s(x,y,z) and t must be in reduced form.
    //
    // Find u + v.
    size_t limite = 35;
    std::set<fraction> fractions;
    for (size_t b = 2; b < limite + 1; ++b)
        for (size_t a = 1; a < b; ++a)
            fractions.emplace(a, b);

    std::set<fraction> solutions;
    for (auto it1 = fractions.begin(), en = fractions.end(); it1 != en; ++it1)
        for (auto it2 = it1; it2 != en; ++it2) {
            auto x = *it1;
            auto y = *it2;
            // n = 1: z = x + y
            {
                fraction z = x + y;
                if (fractions.find(z) != fractions.end())
                    solutions.insert(x + y + z);
            }

            // n = -1: 1/z = 1/x + 1/y
            {
                fraction z = x * y / (x + y);
                if (fractions.find(z) != fractions.end())
                    solutions.insert(x + y + z);
            }

            {
                fraction zz = x * x + y * y;
                if (polygonal::est_carre(zz.numerator()) && polygonal::est_carre(zz.denominator())) {
                    fraction z(arithmetiques::racine_carre(zz.numerator()), arithmetiques::racine_carre(zz.denominator()));
                    {
                        // n = 2: z = sqrt(x^2+y^2)
                        if (fractions.find(z) != fractions.end())
                            solutions.insert(x + y + z);
                    }

                    {
                        // n = -2: z=x*y/sqrt(x^2+y^2)
                        z = x * y / z;
                        if (fractions.find(z) != fractions.end())
                            solutions.insert(x + y + z);
                    }
                }
            }
        }

    mp_nombre u = 0;
    mp_nombre v = 1;
    for (auto s: solutions) {
        u = s.denominator() * u + s.numerator() * v;
        v *= s.denominator();
    }

    mp_nombre resultat = (u + v) / mp_nombre::PGCD(u, v);
    return resultat.to_string();
}
