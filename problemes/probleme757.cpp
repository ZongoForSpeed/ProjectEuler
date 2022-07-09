#include "problemes.h"
#include "timer.h"

#include <unordered_set>
#include "racine.h"

namespace {
    size_t stealthy(size_t n) {
        size_t limit = racine::racine(n, 4);
        std::unordered_set<size_t> seen;

        size_t count = 0;

        for (size_t x = 1; x <= limit; ++x) {
            size_t y = x;
            while (true) {
                size_t v = x*(x + 1)*y*(y+1);
                if (v > n) {
                    break;
                }

                auto it = seen.insert(v);
                if (it.second) {
                    ++count;
                }

                y++;
            }
        }

        return count;
    }
}

ENREGISTRER_PROBLEME(757, "Stealthy Numbers") {
    // A positive integer N is stealthy, if there exist positive integers a, b, c, d such that a.b = c.d = N and a + b = c + d + 1.
    // For example, 36 = 4 * 9 = 6 * 6 is stealthy.
    //
    // You are also given that there are 2851 stealthy numbers not exceeding 10^6.
    //
    //How many stealthy numbers are there that don't exceed 10^14?
    std::cout << "stealthy(1'000'000) = " << stealthy(1'000'000) << std::endl;
    return std::to_string(stealthy(100'000'000'000'000));
}
