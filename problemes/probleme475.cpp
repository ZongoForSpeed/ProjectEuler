#include "problemes.h"
#include "utilitaires.h"
#include "multidimension.h"
#include "arithmetiques.h"

typedef boost::multiprecision::cpp_int nombre;
typedef std::tuple<short, short, short> triplet;

namespace {
    void algorithme(const triplet& s0, triplet s, std::map<triplet, nombre>& dp, const nombre &v, short d = 0);

    template<std::size_t N> void doUpdate(const triplet &s0, triplet &s, std::map<triplet, nombre>& dp, const nombre &v, short d) {
        if (std::get<N>(s)) {
            std::get<N>(s)--;
            algorithme(s0, s, dp, v*(std::get<N>(s) + 1), d + 1);
            std::get<N>(s)++;
        }
    }
    
    void algorithme(const triplet& s0, triplet s, std::map<triplet, nombre>& dp, const nombre &v, short d) {
        if (d == 4) {
            std::get<2>(s) += std::get<1>(s0) - std::get<1>(s);
            std::get<1>(s) += std::get<0>(s0) - std::get<0>(s);
            dp[s] += v;
            return;
        }
        
        doUpdate<0>(s0, s, dp, v, d);
        doUpdate<1>(s0, s, dp, v, d);
        doUpdate<2>(s0, s, dp, v, d);
    }
}

ENREGISTRER_PROBLEME(475, "Music festival") {
    // 12n musicians participate at a music festival. On the first day, they form 3n quartets and practice anombre 
    // day.
    //
    // It is a disaster. At the end of the day, anombre musicians decide they winombre never again agree to play 
    // with any member of their quartet.
    //
    // On the second day, they form 4n trios, each musician avoiding his previous quartet partners.
    //
    // Let f(12n) be the number of ways to organize the trios amongst the 12n musicians.
    //
    // You are given f(12) = 576 and f(24) mod 1 000 000 007 = 509089824.
    //
    // Find f(600) mod 1 000 000 007.
    const short n = 600 / 12;

    std::map<triplet, nombre> dp;
    dp[triplet(4*n, 0, 0)] = 1;

    for (short i = 0; i < 3*n; i++) {
        std::map<triplet, nombre> suivant;
        for (auto &p : dp)
            algorithme(p.first, p.first, suivant, p.second);
        dp.swap(suivant);
    }

    auto a = dp.begin()->second;
    for (short i = 2; i <= 4*n; i++)
        a /= i;
    
    nombre resultat = a % 1000000007;
    return resultat.str();
}
