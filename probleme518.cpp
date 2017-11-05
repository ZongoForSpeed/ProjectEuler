#include "problemes.h"
#include "utilitaires.h"
#include "premiers.h"
#include "arithmetiques.h"

ENREGISTRER_PROBLEME(518, "Prime triples and geometric sequences") {
    // Let S(n) = Σ a+b+c over all triples (a,b,c) such that:
    //
    //      a, b, and c are prime numbers.
    //      a < b < c < n.
    //      a+1, b+1, and c+1 form a geometric sequence.
    //
    // For example, S(100) = 1035 with the following triples:
    //
    //      (2, 5, 11), (2, 11, 47), (5, 11, 23), (5, 17, 53),
    //      (7, 11, 17), (7, 23, 71), (11, 23, 47), (17, 23, 31), 
    //      (17, 41, 97), (31, 47, 71), (71, 83, 97)
    //
    // Find S(10**8).
    size_t limite = 100'000'000;
    
    std::set<size_t> premiers;
    premiers::crible235<size_t>(limite, std::inserter(premiers, premiers.end()));
    
    size_t resultat = 0;
    for (size_t x = 1; x < limite / 4 + 1; ++x) {
        for (size_t y = 1;; ++y) {
            size_t a = x * y * y - 1;
            if (a > limite)
                break;
                
            if (premiers.find(a) == premiers.end())
                continue;
                
            for (size_t z = y + 1;; ++z) {
                size_t c = x * z * z - 1;
                if (c > limite)
                    break;
                if (arithmetiques::PGCD(y, z) != 1)
                    continue;
                    
                size_t b = x * y * z - 1;
                if (premiers.find(b) != premiers.end() && premiers.find(c) != premiers.end()) {
                    // std::cout << std::make_tuple(a, b, c) << std::endl;
                    resultat += a + b + c;
                }

            }
        }
    }
    
    return std::to_string(resultat);
}
