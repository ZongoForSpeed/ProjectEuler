#pragma once

#include <cstdlib>

#include <algorithm>
#include <deque>
#include <map>

#include "puissance.h"
#include "utilitaires.h"
#include <boost/multiprecision/integer.hpp>

namespace arithmetiques {
    template<typename Nombre>
    constexpr Nombre PGCD(Nombre a, Nombre b) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        Nombre pgcd = 0;
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

    template<typename Nombre>
    constexpr Nombre PGCD(Nombre a, Nombre b, Nombre c) {
        return PGCD(a, PGCD(b, c));
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

    template<typename Nombre>
    constexpr Nombre racine_carre(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        return static_cast<Nombre>(std::sqrt(n));
    }

    template<typename Nombre>
    constexpr Nombre racine_cubique(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        return static_cast<Nombre>(std::cbrt(n));
    }

    template<typename Nombre>
    std::optional<Nombre> carre_parfait(Nombre x) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre s = racine_carre<Nombre>(x);
        if (s * s == x)
            return s;
        else
            return std::nullopt;
    }

    template<typename Nombre, typename Conteneur>
    Nombre nombre_diviseurs(Nombre n, const Conteneur &premiers) {
        Nombre d = 1;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                Nombre compteur = 0;
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
                Nombre compteur = 0;
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
        for (const auto &facteur: d) {
            std::deque<Nombre> r = resultat;
            Nombre p = facteur.first;
            for (size_t f = 0; f < facteur.second; ++f) {
                for (auto i: resultat)
                    r.push_back(i * p);
                p *= facteur.first;
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

    template<typename Nombre, typename Conteneur>
    Nombre inverse_modulaire(Nombre a, Nombre n, const Conteneur &premiers) {
        // https://fr.wikipedia.org/wiki/Inverse_modulaire
        // si PGCD(a, n) = 1
        // alors a**phi(n) mod n = 1
        //       a**-1 = a**(phi(n) - 1) mod n
        Nombre _phi = phi<Nombre>(n, premiers);
        return puissance::puissance_modulaire<Nombre>(a, _phi - 1, n);
    }

    template<typename Nombre>
    Nombre inverse_modulaire(Nombre a, Nombre n) {
        Nombre inverse, ignore;
        Bezout(a, n, inverse, ignore);

        if (inverse < 0)
            return inverse + n;
        else
            return inverse;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2, typename Conteneur3>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes, const Conteneur3 &premiers) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        std::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &premiers, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo, premiers) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        std::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }
}
