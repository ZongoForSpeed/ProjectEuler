#include "problemes.h"
#include "utilitaires.h"
#include "iterator.h"

#include <algorithm>
#include <numeric>

namespace {
    void reverse(std::vector<size_t> &train, size_t i) {
        std::reverse(iterator::next(train.begin(), i), train.end());
    }

    int compte_maximix(std::vector<size_t> &train) {
        int ret;
        for (size_t i = 0; i < train.size(); i++) {
            if (train[i] == i) continue;
            size_t j = i;
            while (train[++j] != i);
            if (j == train.size() - 1) {
                reverse(train, i);
                ret = 1 + compte_maximix(train);
                reverse(train, i);
            } else {
                reverse(train, j);
                reverse(train, i);
                ret = 2 + compte_maximix(train);
                reverse(train, i);
                reverse(train, j);
            }
            return ret;
        }
        return 0;
    }

    std::string affiche(const std::vector<size_t> &arr) {
        std::string resultat;
        for (auto &&i: arr) {
            resultat += static_cast<char>('A' + i);
        }

        return resultat;
    }
}


ENREGISTRER_PROBLEME(336, "Maximix Arrangements") {
    // A train is used to transport four carriages in the order: ABCD. However, sometimes when the train arrives to
    // collect the carriages they are not in the correct order.
    //
    // To rearrange the carriages they are all shunted on to a large rotating turntable. After the carriages are
    // uncoupled at a specific point the train moves off the turntable pulling the carriages still attached with it.
    // The remaining carriages are rotated 180 degrees. All of the carriages are then rejoined and this process is
    // repeated as often as necessary in order to obtain the least number of uses of the turntable.
    //
    // Some arrangements, such as ADCB, can be solved easily: the carriages are separated between A and D, and after DCB
    // are rotated the correct order has been achieved.
    //
    // However, Simple Simon, the train driver, is not known for his efficiency, so he always solves the problem by
    // initially getting carriage A in the correct place, then carriage B, and so on.
    //
    // Using four carriages, the worst possible arrangements for Simon, which we shall call maximix arrangements, are
    // DACB and DBAC; each requiring him five rotations (although, using the most efficient approach, they could be
    // solved using just three rotations). The process he uses for DACB is shown below.
    //
    // It can be verified that there are 24 maximix arrangements for six carriages, of which the tenth lexicographic
    // maximix arrangement is DFAECB.
    //
    // Find the 2011th lexicographic maximix arrangement for eleven carriages.
    const size_t M = 2011;
    std::string resultat;
    std::vector<size_t> train(11, 0);
    std::iota(train.begin(), train.end(), 0);
    int max = -1;
    int compteur = 0;
    do {
        int maximix = compte_maximix(train);
        if (maximix > max) {
            max = maximix;
            compteur = 1;
        } else if (maximix == max) {
            if (++compteur == M) {
                resultat = affiche(train);
            }
        }
    } while (std::ranges::next_permutation(train).found);

    return resultat;
}
