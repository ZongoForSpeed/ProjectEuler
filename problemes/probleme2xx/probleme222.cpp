#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <random>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    // const long double L = 100.0;
    long double hauteur(const long double r1, const long double r2) {
        return 2.0L * std::sqrt(r1 + r2 - 1.0L);
    }

    long double hauteur(const std::deque<long double> &empilement) {
        long double resultat = empilement.front() + empilement.back();
        for (size_t n = 1; n < empilement.size(); ++n) {
            resultat += hauteur(empilement[n - 1], empilement[n]);
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(222, "Sphere Packing") {
    // What is the length of the shortest pipe, of internal radius 50mm, that can fully contain 21 balls of radii 30mm,
    // 31mm, ..., 50mm?
    //
    // Give your answer in micrometres (10^-6 m) rounded to the nearest integer.
    const long double R = 50.0L;
    const nombre taille = 21;
    std::deque<long double> rayons;
    for (size_t n = 0; n < taille; ++n)
        rayons.push_back((30.0L + n) / R);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(rayons.begin(), rayons.end(), g);

    long double optimum = hauteur(rayons);
    long double optimum_local = optimum;

    nombre iteration = 0;
    nombre retour = 0;
    while (true) {
        long double minimum = optimum_local;
        size_t m_i = taille;
        size_t m_j = taille;
        for (size_t i = 0; i < taille - 1; ++i)
            for (size_t j = i + 1; j < taille; ++j) {
                std::swap(rayons[i], rayons[j]);
                long double h = hauteur(rayons);
                if (h < minimum) {
                    minimum = h;
                    m_i = i;
                    m_j = j;
                }
                std::swap(rayons[i], rayons[j]);
            }

        if (minimum < optimum_local) {
            std::swap(rayons[m_i], rayons[m_j]);
            optimum_local = minimum;
        } else {
            optimum = std::min(optimum_local, optimum);
            ++retour;
            std::shuffle(rayons.begin(), rayons.end(), g);
            optimum_local = hauteur(rayons);
        }

        ++iteration;
        if (iteration % 100000 == 0)
            break;
    }

    std::cout << "Retour = " << retour << std::endl;

    auto resultat = static_cast<nombre>(optimum * R * 1000);
    return std::to_string(resultat);
}
