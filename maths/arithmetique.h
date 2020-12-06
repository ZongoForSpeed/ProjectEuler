#pragma once

#include <cstdlib>

#include <algorithm>
#include <deque>
#include <map>

#include "puissance.h"
#include "utilitaires.h"

class mpz_nombre;

namespace arithmetique {
    template<typename Nombre>
    constexpr Nombre PGCD(const Nombre &_a, const Nombre &_b) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        if (_a == 0)
            return _b;
        if (_b == 0)
            return _a;

        Nombre a = _a;
        Nombre b = _b;
        Nombre pgcd;
        while (true) {
            pgcd = a % b;
            if (pgcd == 0) {
                pgcd = b;
                break;
            }
            a = b;
            b = pgcd;
        }
        return pgcd;
    }

    template<>
    mpz_nombre PGCD(const mpz_nombre &a, const mpz_nombre &b);

    template<typename Nombre>
    constexpr Nombre PGCD(Nombre a, Nombre b, Nombre c) {
        return PGCD(a, PGCD(b, c));
    }

    template<typename Nombre>
    constexpr Nombre PGCD(Nombre a, Nombre b, Nombre c, Nombre d) {
        return PGCD(PGCD(a, b), PGCD(c, d));
    }

    template<typename Nombre>
    constexpr Nombre PPCM(Nombre a, Nombre b) {
        return (a * b) / PGCD(a, b);
    }

    template<typename Nombre>
    Nombre Bezout(Nombre a, Nombre b, Nombre &x, Nombre &y) {
        // static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode
        Nombre s = 0, old_s = 1;
        Nombre t = 1, old_t = 0;
        Nombre r = b, old_r = a;
        while (r != 0) {
            Nombre quotient = old_r / r;
            std::tie(old_r, r) = std::make_pair(r, old_r - quotient * r);
            std::tie(old_s, s) = std::make_pair(s, old_s - quotient * s);
            std::tie(old_t, t) = std::make_pair(t, old_t - quotient * t);
        }

        // std::cout << "Bézout coefficients:" << std::make_pair(old_s, old_t) << std::endl;
        // std::cout << "greatest common divisor:" << old_r << std::endl;
        // std::cout << "quotients by the gcd:" << std::make_pair(t, s) << std::endl;
        x = old_s;
        y = old_t;

        return old_r;
    }

    template<typename Nombre>
    constexpr Nombre arrondi(Nombre n, Nombre d) {
        return (n + d / 2) / d;
    }

    template<typename Nombre>
    constexpr Nombre plafond(Nombre n, Nombre d) // ceil
    {
        return (n + d - 1) / d;
    }

    template<typename Nombre, typename Conteneur>
    Nombre nombre_diviseurs(Nombre n, const Conteneur &premiers) {
        Nombre d = 1;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                size_t compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                d *= compteur + 1;
            }
        }
        if (n > 1)
            d *= 2;

        return d;
    }

    template<typename Nombre, typename Conteneur>
    Nombre somme_diviseurs(Nombre n, const Conteneur &premiers) {
        Nombre s = 1;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                size_t compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                s *= (puissance::puissance(p, compteur + 1) - 1) / (p - 1);
            }
        }
        if (n > 1)
            s *= (n + 1);

        return s;
    }

    template<typename Nombre, typename Conteneur, typename Dictionnaire>
    void decomposition(Nombre n, const Conteneur &premiers, Dictionnaire &sortie) {
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                size_t compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                sortie[p] = compteur;
            }
        }
        if (n > 1)
            sortie[n] = 1;
    }

    template<typename Nombre, typename Conteneur>
    Nombre radical(Nombre n, const Conteneur &premiers) {
        Nombre resultat = 1;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                while (n % p == 0)
                    n /= p;

                resultat *= p;
            }
        }
        if (n > 1)
            resultat *= n;

        return resultat;
    }

    template<typename Nombre1, typename Nombre2>
    Nombre1 nombre_facteur(Nombre1 n, Nombre2 d) {
        Nombre1 i = 0;
        while (n % d == 0) {
            n /= d;
            ++i;
        }

        return i;
    }

    template<typename Nombre, typename Conteneur>
    Nombre phi(Nombre n, const Conteneur &premiers) {
        Nombre resultat = n;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                resultat = resultat - resultat / p;
                while (n % p == 0)
                    n /= p;
            }
        }
        if (n > 1) {
            resultat = resultat - resultat / n;
        }
        return resultat;
    }

    template<typename Nombre, typename Conteneur>
    short moebius(Nombre n, const Conteneur &premiers) {
        Nombre facteurs = 0;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                Nombre compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                if (compteur > 1)
                    return 0;

                ++facteurs;
            }
        }
        if (n > 1)
            ++facteurs;

        return (facteurs % 2 == 0) ? 1 : -1;
    }

    template<typename Nombre>
    int jacobi(const Nombre &_n, const Nombre &_k) {
        Nombre n = _n;
        Nombre k = _k;
        k %= n;
        int jacobi = 1;
        while (k > 0) {
            while (k % 2 == 0) {
                k /= 2;
                Nombre r = n % 8;
                if (r == 3 || r == 5) {
                    jacobi = -jacobi;
                }
            }

            std::swap(n, k);
            if (k % 4 == 3 && n % 4 == 3) {
                jacobi = -jacobi;
            }
            k %= n;
        }
        if (n == 1) {
            return jacobi;
        }
        return 0;
    }

    template<>
    int jacobi(const mpz_nombre &n, const mpz_nombre &k);

    template<typename Nombre, typename Conteneur>
    bool facteur_carre(Nombre n, const Conteneur &premiers) {
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                Nombre compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                if (compteur > 1)
                    return true;
            }
        }
        return false;
    }

    template<typename Nombre, typename Conteneur>
    std::deque<Nombre> diviseurs(Nombre n, const Conteneur &premiers) {
        std::map<Nombre, size_t> d;
        decomposition<Nombre>(n, premiers, d);
        std::deque<Nombre> resultat{1};
        for (const auto &[p, exposant]: d) {
            std::deque<Nombre> r = resultat;
            Nombre f = p;
            for (size_t e = 0; e < exposant; ++e) {
                for (auto i: resultat)
                    r.push_back(i * f);
                f *= p;
            }

            resultat.swap(r);
        }

        std::sort(resultat.begin(), resultat.end());
        return resultat;
    }

    template<typename Nombre, typename Conteneur>
    std::deque<Nombre> facteurs_premiers(Nombre n, const Conteneur &premiers) {
        std::deque<Nombre> resultat;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                while (n % p == 0)
                    n /= p;
                resultat.push_back(p);
            }
        }
        if (n > 1)
            resultat.push_back(n);

        return resultat;
    }

    template<typename Nombre, typename Conteneur>
    Nombre derivee(Nombre n, const Conteneur &premiers) {
        Nombre resultat = 0;
        Nombre x = n;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                Nombre compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                resultat += x * compteur / p;
            }
        }
        if (n > 1)
            resultat += x / n;

        return resultat;
    }

    // https://fr.wikipedia.org/wiki/Racine_primitive_modulo_n
    template<typename Nombre, typename Conteneur>
    std::optional<Nombre> racine_primitive(Nombre p, const Conteneur &premiers) {
        Nombre phi = p - 1;
        auto facteurs = facteurs_premiers(phi, premiers);
        for (Nombre x = 1; x < p; ++x) {
            bool primitif = true;
            for (auto f: facteurs) {
                if (puissance::puissance_modulaire(x, phi / f, p) == 1) {
                    primitif = false;
                    break;
                }
            }
            if (primitif) {
                return x;
            }
        }

        return std::nullopt;
    }

    namespace repunit {
        template<typename Nombre>
        constexpr Nombre A(Nombre n, size_t base = 10) {
            Nombre k = 1;
            Nombre q = (base - 1) * n;
            for (Nombre p = base % q; p % q != 1; p = (base * p) % q) {
                ++k;
            }

            return k;
        }
    }

    template<typename Nombre>
    constexpr short signe(Nombre n) {
        if (n > 0)
            return 1;
        else if (n < 0)
            return -1;
        return 0;
    }
}
