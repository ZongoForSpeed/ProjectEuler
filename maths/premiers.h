#pragma once

#include <functional>
#include <vector>

#include <random>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include "puissance.h"

namespace premiers {
    void algorithme_crible2(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_crible23(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_crible235(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_super_crible(const std::size_t taille, const std::vector<std::size_t> &roue,
                                 std::function<void(const std::size_t &)> sortie);

    template<typename Nombre, class OutputIterator>
    OutputIterator crible2(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible2(taille,
                           [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator crible23(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible23(taille,
                            [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible235(taille,
                             [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator
    super_crible(const std::size_t &taille, const std::vector<std::size_t> &roue, OutputIterator sortie) {
        algorithme_super_crible(taille, roue,
                                [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    void crible_simple(size_t taille, std::vector<bool> &sortie);

    template<typename Nombre>
    bool temoin_miller(const Nombre &n, const Nombre &a, const Nombre &q, size_t k) {
        Nombre x = puissance::puissance_modulaire(a, q, n);
        if (x == 1 || x + 1 == n) {
            return false;
        }

        while (k > 1) {
            x = puissance::puissance_modulaire(x, 2, n);
            if (x + 1 == n) {
                return false;
            }
            --k;
        }

        return true;
    }

    // Test de primalité de Miller-Rabin
    // https://fr.wikipedia.org/wiki/Test_de_primalit%C3%A9_de_Miller-Rabin
    template<typename Nombre>
    bool miller_rabin(const Nombre &n, unsigned short reps = 25) {
        static std::random_device rd;   // Will be used to obtain a seed for the random number engine
        static std::mt19937 mt(rd());   // Standard mersenne_twister_engine seeded with rd()

        const static std::set<size_t> premiers100{2, 3, 5, 7, 11, 13, 17, 19, 23,
                                                  29, 31, 37, 41, 43, 47, 53, 59,
                                                  61, 67, 71, 73, 79, 83, 89, 97};

        if (n == 2) {
            return true;
        }

        if (n % 2 == 0) {
            return false;
        }

        if (n < 100 && premiers100.find(n) != premiers100.end()) {
            return true;
        }

        Nombre nm1 = n - 1u;

        // Test de primalité de Fermet avec 210
        // https://fr.wikipedia.org/wiki/Test_de_primalit%C3%A9_de_Fermat
        Nombre y = puissance::puissance_modulaire<Nombre>(210, nm1, n);
        if (y != 1) {
            return false;
        }

        Nombre q = nm1;
        size_t k = 0;
        while (q % 2 == 0) {
            ++k;
            q /= 2;
        }

        std::uniform_int_distribution<Nombre> distribution(2, n - 2);
        for (size_t r = 0; r < reps; ++r) {
            Nombre x = distribution(mt);
            if (temoin_miller(n, x, q, k)) {
                return false;
            }
        }
        return true;
    }

    template<>
    bool miller_rabin(const boost::multiprecision::cpp_int &n, unsigned short reps);

    template<typename Nombre>
    Nombre suivant(Nombre n) {
        // primes less than 212
        static std::vector<size_t> suivants{2, 2, 3, 5, 5, 7, 7, 11, 11, 11, 11, 13, 13, 17, 17, 17, 17, 19, 19, 23, 23,
                                            23, 23, 29, 29, 29, 29, 29, 29, 31, 31, 37, 37, 37, 37, 37, 37, 41, 41, 41,
                                            41, 43, 43, 47, 47, 47, 47, 53, 53, 53, 53, 53, 53, 59, 59, 59, 59, 59, 59,
                                            61, 61, 67, 67, 67, 67, 67, 67, 71, 71, 71, 71, 73, 73, 79, 79, 79, 79, 79,
                                            79, 83, 83, 83, 83, 89, 89, 89, 89, 89, 89, 97, 97, 97, 97, 97, 97, 97, 97,
                                            101, 101, 101, 101, 103, 103, 107, 107, 107, 107, 109, 109, 113, 113, 113,
                                            113, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
                                            131, 131, 131, 131, 137, 137, 137, 137, 137, 137, 139, 139, 149, 149, 149,
                                            149, 149, 149, 149, 149, 149, 149, 151, 151, 157, 157, 157, 157, 157, 157,
                                            163, 163, 163, 163, 163, 163, 167, 167, 167, 167, 173, 173, 173, 173, 173,
                                            173, 179, 179, 179, 179, 179, 179, 181, 181, 191, 191, 191, 191, 191, 191,
                                            191, 191, 191, 191, 193, 193, 197, 197, 197, 197, 199, 199, 211, 211, 211,
                                            211, 211, 211, 211, 211, 211, 211, 211};

        // pre-calced sieve of eratosthenes for n = 2, 3, 5, 7
        static std::vector<size_t> indices{
                1, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
                89, 97, 101, 103, 107, 109, 113, 121, 127, 131,
                137, 139, 143, 149, 151, 157, 163, 167, 169, 173,
                179, 181, 187, 191, 193, 197, 199, 209};

        // distances between sieve values
        static std::vector<size_t> offsets{
                10, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 6,
                6, 2, 6, 4, 2, 6, 4, 6, 8, 4, 2, 4,
                2, 4, 8, 6, 4, 6, 2, 4, 6, 2, 6, 6,
                4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 10, 2};

        if (n < 2) {
            return Nombre(2);
        }

        if (n < 210) {
            return suivants[static_cast<size_t>(n)];
        }

        n = (n + 1) | 1;

        Nombre x = n % 210;
        size_t s = 0;
        size_t e = 47;
        size_t m = 24;
        while (m != e) {
            if (indices[m] < x) {
                s = m;
                m = (s + e + 1) >> 1;
            } else {
                e = m;
                m = (s + e) >> 1;
            }
        }

        Nombre i = n + indices[m] - x;
        auto it = std::next(offsets.begin(), m);
        while (true) {
            if (it == offsets.end()) {
                it = offsets.begin();
            }

            if (premiers::miller_rabin<Nombre>(i, 25)) {
                return i;
            }

            i += (*it);
            ++it;
        }
    }
}
