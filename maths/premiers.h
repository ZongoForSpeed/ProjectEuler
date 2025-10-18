#pragma once

#include <functional>
#include <vector>

#include "mpz_nombre.h"

namespace premiers {
    void algorithme_crible2(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie);

    void algorithme_crible23(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie);

    void algorithme_crible235(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie);

    void algorithme_super_crible(std::size_t taille, const std::vector<std::size_t> &roue,
                                 const std::function<void(const std::size_t &)> &sortie);

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

    // Test de primalité de Miller-Rabin
    // https://fr.wikipedia.org/wiki/Test_de_primalit%C3%A9_de_Miller-Rabin
    bool miller_rabin(unsigned long n, unsigned short reps = 25);

    bool miller_rabin(unsigned long long n, unsigned short reps = 25);

    bool miller_rabin(const mpz_nombre &n, unsigned short reps = 25);

    unsigned long suivant(unsigned long n);

    unsigned long long suivant(unsigned long long n);

    mpz_nombre suivant(const mpz_nombre &n);

    // https://en.wikipedia.org/wiki/Prime-counting_function#The_Meissel%E2%80%93Lehmer_algorithm
    class MeisselLehmer {
        const std::vector<size_t> &premiers;
        std::vector<size_t> cachePi;

        size_t P2(size_t m, size_t n);

    public:
        MeisselLehmer(const std::vector<size_t> &_premiers);

        size_t Phi(size_t m, size_t n);

        size_t pi(size_t m);

        size_t pi(size_t m, size_t n);
    };
}
