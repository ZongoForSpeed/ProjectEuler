#include "problemes.h"
#include "arithmetique.h"
#include "mpq_fraction.h"
#include "utilitaires.h"
#include "iterator.h"

#include <execution>
#include <fstream>
#include <vector>

#include "format.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

typedef std::vector<unsigned short> envelope;

namespace {
    mpq_fraction calculEsperance(std::map<envelope, mpq_fraction> &cache, const envelope &e) {
        if (auto it = cache.find(e);it != cache.end())
            return it->second;

        mpq_fraction resultat(0ul, 1ul);
        if (!e.empty()) {
            for (size_t i = 0; i < e.size(); i++) {
                envelope nouvelleEnvelope(e);
                const unsigned short sheet = e[i];
                nouvelleEnvelope.erase(iterator::next(nouvelleEnvelope.begin(), i));
                for (unsigned short j = sheet + 1; j <= 5; j++)
                    nouvelleEnvelope.push_back(j);
                std::sort(std::execution::par, nouvelleEnvelope.begin(), nouvelleEnvelope.end());
                resultat += calculEsperance(cache, nouvelleEnvelope);
            }

            resultat /= e.size();
            if (e.size() == 1)
                ++resultat;
        }

        cache[e] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(151, "Paper sheets of standard sizes: an expected-value problem") {
    // A printing shop runs 16 batches (jobs) every week and each batch requires a sheet of special colour-proofing
    // paper of size A5.
    //
    // Every Monday morning, the foreman opens a new envelope, containing a large sheet of the special paper with size
    // A1.
    //
    // He proceeds to cut it in half, thus getting two sheets of size A2. Then he cuts one of them in half to get two
    // sheets of size A3 and so on until he obtains the A5-size sheet needed for the first batch of the week.
    // 
    // All the unused sheets are placed back in the envelope.
    // 
    // At the beginning of each subsequent batch, he takes from the envelope one sheet of paper at random. If it is of
    // size A5, he uses it. If it is larger, he repeats the 'cut-in-half' procedure until he has what he needs and any
    // remaining sheets are always placed back in the envelope.
    //  
    // Excluding the first and last batch of the week, find the expected number of times (during each week) that the
    // foreman finds a single sheet of paper in the envelope.
    //
    // Give your answer rounded to six decimal places using the format x.xxxxxx .
    std::map<envelope, mpq_fraction> cache;
    const envelope e{1};
    mpq_fraction f = calculEsperance(cache, e) - 2;
    return format::to_fixed(f.get_double(), 6);
}
