#pragma once

#include "utilitaires.h"
#include "arithmetiques.h"

#include <cmath>

namespace polygonal {
    template<typename Nombre>
    constexpr bool est_carre(Nombre n) {
        Nombre racine = arithmetiques::racine_carre(n);
        return racine * racine == n;
    }

    template<typename Nombre>
    constexpr bool est_cubique(Nombre n) {
        Nombre racine = arithmetiques::racine_cubique(n);
        return racine * racine * racine == n;
    }

    template<typename Nombre>
    constexpr Nombre triangulaire(Nombre n) {
        return n * (n + 1) / 2;
    }

    template<typename Nombre>
    constexpr bool est_triangulaire(Nombre n) {
        Nombre delta = 1 + 8 * n;
        Nombre racine_delta = arithmetiques::racine_carre(delta);
        if (racine_delta * racine_delta != delta)
            return false;
        return (racine_delta - 1) % 2 == 0;
    }

    template<typename Nombre>
    constexpr Nombre pentagonal(Nombre n) {
        return n * (3 * n - 1) / 2;
    }

    template<typename Nombre>
    constexpr bool est_pentagonal(Nombre n) {
        Nombre delta = 1 + 24 * n;
        Nombre racine_delta = arithmetiques::racine_carre(delta);
        if (racine_delta * racine_delta != delta)
            return false;
        return (1 + racine_delta) % 6 == 0;
    }

    template<typename Nombre>
    constexpr Nombre hexagonal(Nombre n) {
        return n * (2 * n - 1);
    }

    template<typename Nombre>
    constexpr bool est_hexagonal(Nombre n) {
        Nombre delta = 1 + 8 * n;
        Nombre racine_delta = arithmetiques::racine_carre(delta);
        if (racine_delta * racine_delta != delta)
            return false;
        return (1 + racine_delta) % 4 == 0;
    }

    template<typename Nombre>
    constexpr Nombre heptagonal(Nombre n) {
        return n * (5 * n - 3) / 2;
    }

    template<typename Nombre>
    constexpr bool est_heptagonal(Nombre n) {
        Nombre delta = 9 + 40 * n;
        Nombre racine_delta = arithmetiques::racine_carre(delta);
        if (racine_delta * racine_delta != delta)
            return false;
        return (3 + racine_delta) % 10 == 0;
    }

    template<typename Nombre>
    constexpr Nombre octagonal(Nombre n) {
        return n * (3 * n - 2);
    }

    template<typename Nombre>
    constexpr bool est_octagonal(Nombre n) {
        Nombre delta = 4 + 12 * n;
        Nombre racine_delta = arithmetiques::racine_carre(delta);
        if (racine_delta * racine_delta != delta)
            return false;
        return (2 + racine_delta) % 6 == 0;
    }

    template<typename Nombre>
    constexpr Nombre polygonal(Nombre n, unsigned short type) {
        switch (type) {
            case 3:
                return triangulaire(n);
            case 4:
                return n * n;
            case 5:
                return pentagonal(n);
            case 6:
                return hexagonal(n);
            case 7:
                return heptagonal(n);
            case 8:
                return octagonal(n);
            default:
                return 0;
        }
    }

    template<typename Nombre>
    constexpr Nombre est_polygonal(Nombre n, unsigned short type) {
        switch (type) {
            case 3:
                return est_triangulaire(n);
            case 4:
                return est_carre(n);
            case 5:
                return est_pentagonal(n);
            case 6:
                return est_hexagonal(n);
            case 7:
                return est_heptagonal(n);
            case 8:
                return est_octagonal(n);
            default:
                return false;
        }
    }
    
    template<typename Nombre>
    constexpr Nombre somme_carres(Nombre n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    template<typename Nombre>
    constexpr Nombre somme_cubes(Nombre n) {
        Nombre t = triangulaire(n);
        return t*t;
    }
}
