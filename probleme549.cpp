#include "problemes.h"
#include "utilitaires.h"

ENREGISTRER_PROBLEME(549, "Divisibility of factorials") {
    // The smallest number m such that 10 divides m! is m=5.
    // The smallest number m such that 25 divides m! is m=10.
    //
    // Let s(n) be the smallest number m such that n divides m!.
    // So s(10)=5 and s(25)=10.
    // Let S(n) be ∑s(i) for 2 ≤ i ≤ n.
    // S(100)=2012.
    //
    // Find S(10**8).
    size_t limite = 100'000'000;
    
    std::vector<size_t> dp(limite + 1, 0);
    for (size_t p = 2; p < limite + 1; ++p) {
        if (dp[p] != 0)
            continue;
        
        size_t puissance = 1;
        for (size_t j = p;; j += p) {
            puissance *= p;
            if (puissance > limite) {
                break;
            }
            
            for (size_t k = puissance; k < limite + 1; k += puissance) {
				dp[k] = std::max(j, dp[k]);
            }
			
			size_t facteur = j / p;
			while (facteur % p == 0) {
				puissance *= p;
				facteur /= p;
			}
        }
    }

    unsigned long long solution = std::accumulate(dp.begin(), dp.end(), 0ull);
    return std::to_string(solution);
}
