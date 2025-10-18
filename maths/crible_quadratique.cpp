#include "crible_quadratique.h"
#include <optional>
#include <boost/random/uniform_int.hpp>

#include "arithmetique.h"
#include "distribution.h"
#include "premiers.h"

namespace {
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
    std::optional<Nombre> internal_pollard_rho(Nombre n) {
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
    }

    template<typename Nombre>
    std::optional<Nombre> internal_pollard_brent(Nombre n) {
        std::mt19937 &mt = distribution::generator();

        boost::uniform_int<Nombre> distribution(1, n - 1);

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
                Nombre iMin = std::min(m, r - k);
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

}

namespace crible {
    std::optional<unsigned long> pollard_rho(unsigned long n) {
        return internal_pollard_rho(n);
    }

    std::optional<unsigned long long> pollard_rho(unsigned long long n) {
        return internal_pollard_rho(n);
    }

    std::optional<unsigned long> pollard_brent(unsigned long n) {
        return internal_pollard_brent(n);
    }

    std::optional<unsigned long long> pollard_brent(unsigned long long n) {
        return internal_pollard_brent(n);
    }

}
