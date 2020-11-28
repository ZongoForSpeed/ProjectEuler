#pragma once

#include <deque>

#include "arithmetique.h"
#include "premiers.h"

namespace crible {
    template<typename Nombre>
    Nombre abs(Nombre x, Nombre y) {
        return x > y ? x - y : y - x;
    }

    template<typename Nombre>
    Nombre g1(Nombre x, Nombre n) {
        return (x * x + 1) % n;
    }

    // https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Algorithm
    template<typename Nombre>
    std::optional<Nombre> pollard_rho(Nombre n) {
        Nombre loop = 1;
        Nombre count;
        Nombre x_fixed = 2;
        Nombre x = 2;
        Nombre size = 2;
        Nombre factor;

        do {
            // printf("----   loop %4i   ----\n", loop);
            count = size;
            do {
                x = g1(x, n);
                factor = arithmetique::PGCD(abs(x, x_fixed), n);
                // printf("count = %4i  x = %6i  factor = %i\n", size - count + 1, x, factor);
            } while ((--count > 0) && (factor == 1));
            size *= 2;
            x_fixed = x;
            loop = loop + 1;
        } while (factor == 1);
        // printf("factor is %i\n", factor);

        if (factor == n) {
            return std::nullopt;
        } else {
            return std::make_optional(factor);
        }
        // return factor == number ? EXIT_FAILURE : EXIT_SUCCESS;
        // Nombre x = 2;
        // Nombre y = 2;
        // Nombre d = 1;
        //
        // while (d == 1) {
        //     x = g1(x, n);
        //     y = g1(g1(y, n), n);
        //     d = arithmetique::PGCD(abs(x, y), n);
        // }
        //
        // if (d == n) {
        //     return std::nullopt;
        // } else {
        //     return std::make_optional(d);
        // }
    }

    template<typename Nombre>
    std::optional<Nombre> pollard_brent(Nombre n) {
        static std::random_device rd;
        static std::mt19937 mt(rd());

        std::uniform_int_distribution<Nombre> distribution(1, n - 1);

        Nombre y = distribution(mt);
        Nombre c = distribution(mt);
        Nombre m = distribution(mt);

        Nombre g = 1;
        size_t r = 1;
        Nombre q = 1;

        Nombre ys = 1;
        Nombre x = 1;

        while (g == 1) {
            x = y;
            for (size_t i = 0; i < r; ++i) {
                y = y * y + c;
                y %= n;
            }

            Nombre k = 0;
            while (k < r && g == 1) {
                ys = y;
                size_t iMin = std::min(m, r - k);
                for (size_t i = 0; i < iMin; ++i) {
                    y = y * y + c;
                    y %= n;

                    q = (q * abs(x, y)) % n;
                }

                g = arithmetique::PGCD(q, n);
                k += m;
            }

            r *= 2;
        }

        if (g == n) {
            while (true) {
                ys = (ys * ys + c) % n;
                g = arithmetique::PGCD(abs(x, ys), n);
                if (g > 1) {
                    break;
                }
            }
        }

        return std::move(g);
    }

    template<typename Nombre>
    std::deque<Nombre> facteurs_premiers(Nombre n) {
        std::deque<Nombre> facteurs;

        static std::vector<Nombre> premiers{
                2, 3, 5, 7, 11, 13, 17, 19, 23,
                29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
                71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
                113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
                229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
                349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
                409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
                463, 467, 479, 487, 491, 499, 503, 509, 521, 523,
                541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
                601, 607, 613, 617, 619, 631, 641, 643, 647, 653,
                659, 661, 673, 677, 683, 691, 701, 709, 719, 727,
                733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
                809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
                863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
                941, 947, 953, 967, 971, 977, 983, 991, 997
        };

        for (auto premier: premiers) {
            while (n % premier == 0) {
                facteurs.push_back(premier);
                n /= premier;
            }
            if (premier > n) {
                break;
            }
        }

        if (n < 2) {
            return facteurs;
        }

        while (n > 1) {
            if (premiers::miller_rabin(n)) {
                facteurs.push_back(n);
                break;
            }

            if (auto rho = pollard_rho(n)) {
                auto facteurs_rho = facteurs_premiers(rho.value());
                facteurs.insert(facteurs.end(), facteurs_rho.begin(), facteurs_rho.end());
                n /= rho.value();
            } else if (auto brent = pollard_brent(n)) {
                auto facteurs_brent = facteurs_premiers(brent.value());
                facteurs.insert(facteurs.end(), facteurs_brent.begin(), facteurs_brent.end());
                n /= brent.value();
            }
        }

        std::sort(facteurs.begin(), facteurs.end());
        return facteurs;
    }
}
