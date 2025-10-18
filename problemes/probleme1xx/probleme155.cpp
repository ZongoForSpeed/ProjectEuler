#include "problemes.h"
#include "arithmetique.h"

#include <boost/rational.hpp>
#include <set>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;
typedef std::set<fraction> set;

ENREGISTRER_PROBLEME(155, "Counting Capacitor Circuits") {
    // An electric circuit uses exclusively identical capacitors of the same value C.
    //
    // The capacitors can be connected in series or in parallel to form sub-units, which can then be connected in series
    // or in parallel with other capacitors or other sub-units to form larger sub-units, and so on up to a final circuit.
    // 
    // Using this simple procedure and up to n identical capacitors, we can make circuits having a range of different
    // total capacitances. For example, using up to n=3 capacitors of 60 F each, we can obtain the following 7 distinct
    // total capacitance values:
    //
    // If we denote by D(n) the number of distinct total capacitance values we can obtain when using up to n
    // equal-valued capacitors and the simple procedure described above, we have: D(1)=1,
    // D(2)=3, D(3)=7 ...
    // 
    // Find D(18).
    //
    // Reminder : When connecting capacitors C1, C2 etc in parallel, the total capacitance is 
    //                      CT = C1 + C2 +..., 
    // whereas when connecting them in series, the overall capacitance is given by: 
    //                      1/CT = 1/C1 + 1/C2 +...
    std::vector<set> capacite(20, set());

    capacite[1].emplace(1);

    set resultat{fraction(1)};
    for (nombre n = 2; n < 19; ++n) {
        auto &c = capacite[n];
        for (nombre i = 1; i <= n / 2; ++i) {
            nombre j = n - i;
            for (const auto &vi: capacite[i])
                for (const auto &vj: capacite[j]) {
                    if (fraction parallel = vi + vj; resultat.find(parallel) == resultat.end()) {
                        c.insert(parallel);
                        resultat.insert(parallel);
                    }

                    // 1 /(1 / (a1 / b1) + 1 / (a2 / b2 )) = a1 * a2 / (a1 * b2 + a2 * b1)
                    fraction series(vi.numerator() * vj.numerator(),
                                    vi.numerator() * vj.denominator() + vi.denominator() * vj.numerator());
                    if (resultat.find(series) == resultat.end()) {
                        c.insert(series);
                        resultat.insert(series);
                    }
                }
        }

        std::cout << "D(" << n << ") = " << resultat.size() << std::endl;
    }

    return std::to_string(resultat.size());
}
