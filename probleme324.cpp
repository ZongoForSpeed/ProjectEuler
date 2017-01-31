#include "problemes.h"
#include "utilitaires.h"
#include "grand_nombre.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "combinatoire.h"
#include "polygonal.h"

#include <numeric>
#include <fstream>

typedef unsigned long long int nombre;
typedef std::vector<nombre> vecteur;

namespace 
{
    // nombre f(nombre n) {
    //     // if (n < 0)
    //     //     return 0;
    //     if (n < 1)
    //         return 1;
    //     if (n < 2)
    //         return 229;
    //     return 679*f(n-1) - 76177*f(n-2) + 3519127*f(n-3) - 85911555*f(n-4) + 1235863045*f(n-5) - 11123194131*f(n-6) 
    //         + 65256474997*f(n-7) - 257866595482*f(n-8) + 705239311926*f(n-9) - 1363115167354*f(n-10) + 1888426032982*f(n-11)
    //         - 1888426032982*f(n-12) + 1363115167354*f(n-13) - 705239311926*f(n-14) + 257866595482*f(n-15) - 65256474997*f(n-16)
    //         + 11123194131*f(n-17) - 1235863045*f(n-18) + 85911555*f(n-19) - 3519127*f(n-20) + 76177*f(n-21) - 679*f(n-22) 
    //         + f(n-23);
            
    //     // 1-679+76177-3519127+85911555-1235863045+11123194131-65256474997+257866595482-705239311926+1363115167354-1888426032982+1888426032982-1363115167354+705239311926-257866595482+65256474997-11123194131+1235863045-85911555+3519127-76177+679
    // }
}

ENREGISTRER_PROBLEME(324, "Building a tower")
{
    // Let f(n) represent the number of ways one can fill a 3×3×n tower with blocks of 2×1×1. 
    // You're allowed to rotate the blocks in any way you like+however, rotations, reflections etc of the tower itself 
    // are counted as distinct.
    //
    // For example (with q = 100000007) :
    // f(2) = 229,
    // f(4) = 117805,
    // f(10) mod q = 96149360,
    // f(10**3) mod q = 24806056,
    // f(10**6) mod q = 30808124.
    //
    // Find f(10**10000) mod 100000007.
    unsigned long q = 100000007;
    vecteur init;
    {
        std::ifstream ifs("data/p324_list.txt");
        size_t i;
        grand_nombre n;
        while (ifs >> i >> n) {
            init.push_back(n % q);
        }
    }
    
    std::cout << init << std::endl;
    // std::cout << f(1) << std::endl;
    // std::cout << f(2) << std::endl;
    // std::cout << f(5) << std::endl;
    
    return std::to_string(0);
}
