#include "problemes.h"
#include "timer.h"
#include "graphe.h"

#include <execution>
#include <iostream>

typedef size_t nombre;

namespace {

    size_t S(size_t u, size_t k) {
        std::vector<size_t> d(u + 1, 1);
        {
            Timer t("remplissage d");
            for (size_t p = 2; p <= u; ++p) {
                if (d[p] != 1) {
                    continue;
                }
                size_t e = 1;
                size_t q = p;
                do {
                    for (size_t m = q; m <= u; m += q) {
                        d[m] = (d[m] * (e + 1)) / e;
                    }

                    e++;
                    q *= p;
                } while (q <= u);
            }
        }

        graphe::SegmentTree<size_t> tree(d.size(), [](size_t a, size_t b) {
            return std::max(a, b);
        });

        {
            Timer t("SegmentTree::set");
            for (size_t i = 0; i < d.size(); ++i) {
                tree.set(i, d[i]);
            }
        }

        std::vector<size_t> m(u - k + 1, 0);
        {
            Timer t("remplissage m");
            std::iota(m.begin(), m.end(), 1ul);
        }

        size_t s = std::transform_reduce(
                std::execution::par,
                m.begin(),
                m.end(),
                0ull, std::plus<size_t>{},
                [&tree, k](size_t n) {
                    return tree.get(n, n + k);
                });

        std::cout << "S(" << u << ", " << k << ") = " << s << std::endl;

        return s;
    }
}

ENREGISTRER_PROBLEME(485, "Maximum Number of Divisors") {
    // Let d(n) be the number of divisors of n.
    // Let M(n,k) be the maximum value of d(j) for n <= j <= n+k-1.
    // Let S(u,k) be the sum of M(n,k) for 1 <= n <= u-k+1.
    // 
    // You are given that S(1000,10)=17176.
    //
    // Find S(100,000,000, 100,000).
    S(1000, 10);

    return std::to_string(S(100'000'000, 100'000));
}
