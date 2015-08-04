#include <iostream>
#include <vector>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

class Probleme282
{
    // For non-negative integers m, n, the Ackermann function A(m, n) is defined as follows:
    // 
    //
    // For example A(1, 0) = 2, A(2, 2) = 7 and A(3, 4) = 125.
    //
    // Find Sum(A(n, n), n=0..6) and give your answer mod 14^8.
public:
    Probleme282() {}
    
    nombre puissance(nombre a, nombre n, nombre p)
    {
        nombre resultat = 1;
        while (n > 0)
        {
            if (n%2)
                resultat = (resultat * a)%p;
            a = (a*a)%p;
            n /= 2;
        }
        
        return resultat;
    }
    
    void initialiser_ensemble(ensemble & e, nombre k, nombre p)
    {
        nombre n = 1;
        e.insert(n);
        while (true)
        {
            n = (n * k)%p;
            if (e.insert(n).second == false)
                break;
        }
    }
    
    void algorithme()
    {
        nombre k = 2;
        nombre p = 1475789056LL;
        vecteur ackermann;
        ackermann.push_back(1);
        ackermann.push_back(4);
        ackermann.push_back(7);
        ackermann.push_back(61);
        
        nombre n = 0;
        nombre a = 65536;
        while (n < 100)
        {
            a = puissance(2, a, p);
            std::cout << ++n << " : " << a << std::endl;
        }

        // ensemble e;
        // std::cout << e.size() << std::endl;
        
        // size_t n = 0;
        // while (true)
        // {
        //     if (e.empty())
        //     {
        //         initialiser_ensemble(e, k, p);
        //     }
        //     else
        //     {
        //         ensemble s;
        //         for (const auto & i: e)
        //         {
        //             s.insert(puissance(k, i, p));
        //         }
                
        //         if (e.size() == s.size())
        //             break;
                
        //         std::swap(s, e);
        //     }
            
        //     ++n;
        //     std::cout << "Taille " << n << " = " << e.size() << std::endl;
        // }
        
        // for (const auto & i: e)
        // {
        //     std::cout << i << " ";
        // }
        
        // std::cout << std::endl;
    }
};

int main(int argc, char** argv)
{
    Probleme282 p;
    p.algorithme();
    return 0;
}