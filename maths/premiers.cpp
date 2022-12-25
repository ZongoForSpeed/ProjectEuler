#include <numeric>
#include "premiers.h"
#include "timer.h"
#include "racine.h"

namespace {
    // template<typename Nombre, class OutputIterator>
    // void crible_simple(const std::size_t taille, OutputIterator sortie) {
    //     std::vector<bool> test(taille, true);
    //     test.at(0) = false;
    //     test.at(1) = false;
    //     for (std::size_t p = 2; p * p < taille; ++p) {
    //         if (test.at(p)) {
    //             for (std::size_t k = p * p; k < taille; k += p)
    //                 test.at(k) = false;
    //         }
    //     }
    //     for (std::size_t p = 2; p < taille; ++p) {
    //         if (test.at(p)) {
    //             *sortie = Nombre(p);
    //             ++sortie;
    //         }
    //     }
    // }

    void set_test(std::vector<bool> &test, size_t start, size_t end, size_t p) {
        for (size_t t = start; t < end; t += p) {
            test[t] = false;
        }
    }

    void internal_crible2(const std::size_t &taille, std::vector<bool> &test) {
        test.assign(taille, true);
        test.at(0) = false;
        for (std::size_t p = 1; p * p < taille / 2; ++p) {
            if (test.at(p)) {
                set_test(test, 2 * (p * p + p), taille, 2 * p + 1);
            }
        }
    }

    void internal_crible23(const std::size_t &taille, std::vector<bool> &test1, std::vector<bool> &test5) {
        test1.assign(taille, true);
        test1.at(0) = false;
        test5.assign(taille, true);
        for (std::size_t k = 0; 6 * k * k < taille; ++k) {
            // Cas p = 6*k + 1
            if (test1.at(k)) {
                const std::size_t p = 6 * k + 1;
                set_test(test1, 6 * k * k + 2 * k, taille, p);
                set_test(test5, 6 * k * k + 6 * k, taille, p);
            }
            // Cas p = 6*k + 5
            if (test5.at(k)) {
                const std::size_t p = 6 * k + 5;
                set_test(test1, 6 * k * k + 10 * k + 4, taille, p);
                set_test(test5, 6 * k * k + 12 * k + 5, taille, p);
            }
        }
    }

    void internal_crible235(const std::size_t &taille, std::vector<bool> &test1, std::vector<bool> &test7,
                            std::vector<bool> &test11, std::vector<bool> &test13, std::vector<bool> &test17,
                            std::vector<bool> &test19, std::vector<bool> &test23, std::vector<bool> &test29) {
        test1.assign(taille, true);
        test1.at(0) = false;
        test7.assign(taille, true);
        test11.assign(taille, true);
        test13.assign(taille, true);
        test17.assign(taille, true);
        test19.assign(taille, true);
        test23.assign(taille, true);
        test29.assign(taille, true);
        for (std::size_t k = 0; 30 * k * k < taille; ++k) {
            if (test1.at(k)) {
                const std::size_t p = 30 * k + 1;
                set_test(test1, 30 * k * k + 2 * k + 0, taille, p);
                set_test(test7, 30 * k * k + 8 * k + 0, taille, p);
                set_test(test11, 30 * k * k + 12 * k + 0, taille, p);
                set_test(test13, 30 * k * k + 14 * k + 0, taille, p);
                set_test(test17, 30 * k * k + 18 * k + 0, taille, p);
                set_test(test19, 30 * k * k + 20 * k + 0, taille, p);
                set_test(test23, 30 * k * k + 24 * k + 0, taille, p);
                set_test(test29, 30 * k * k + 30 * k + 0, taille, p);
            }
            if (test7.at(k)) {
                const std::size_t p = 30 * k + 7;
                set_test(test19, 30 * k * k + 14 * k + 1, taille, p);
                set_test(test17, 30 * k * k + 18 * k + 2, taille, p);
                set_test(test1, 30 * k * k + 20 * k + 3, taille, p);
                set_test(test29, 30 * k * k + 24 * k + 3, taille, p);
                set_test(test13, 30 * k * k + 26 * k + 4, taille, p);
                set_test(test11, 30 * k * k + 30 * k + 5, taille, p);
                set_test(test23, 30 * k * k + 36 * k + 6, taille, p);
                set_test(test7, 30 * k * k + 38 * k + 7, taille, p);
            }
            if (test11.at(k)) {
                const std::size_t p = 30 * k + 11;
                set_test(test1, 30 * k * k + 22 * k + 4, taille, p);
                set_test(test23, 30 * k * k + 24 * k + 4, taille, p);
                set_test(test7, 30 * k * k + 28 * k + 6, taille, p);
                set_test(test29, 30 * k * k + 30 * k + 6, taille, p);
                set_test(test13, 30 * k * k + 34 * k + 8, taille, p);
                set_test(test19, 30 * k * k + 40 * k + 10, taille, p);
                set_test(test11, 30 * k * k + 42 * k + 11, taille, p);
                set_test(test17, 30 * k * k + 48 * k + 13, taille, p);
            }
            if (test13.at(k)) {
                const std::size_t p = 30 * k + 13;
                set_test(test19, 30 * k * k + 26 * k + 5, taille, p);
                set_test(test11, 30 * k * k + 30 * k + 7, taille, p);
                set_test(test7, 30 * k * k + 32 * k + 8, taille, p);
                set_test(test29, 30 * k * k + 36 * k + 9, taille, p);
                set_test(test17, 30 * k * k + 42 * k + 12, taille, p);
                set_test(test13, 30 * k * k + 44 * k + 13, taille, p);
                set_test(test1, 30 * k * k + 50 * k + 16, taille, p);
                set_test(test23, 30 * k * k + 54 * k + 17, taille, p);
            }
            if (test17.at(k)) {
                const std::size_t p = 30 * k + 17;
                set_test(test19, 30 * k * k + 34 * k + 9, taille, p);
                set_test(test23, 30 * k * k + 36 * k + 10, taille, p);
                set_test(test1, 30 * k * k + 40 * k + 13, taille, p);
                set_test(test13, 30 * k * k + 46 * k + 16, taille, p);
                set_test(test17, 30 * k * k + 48 * k + 17, taille, p);
                set_test(test29, 30 * k * k + 54 * k + 20, taille, p);
                set_test(test7, 30 * k * k + 58 * k + 23, taille, p);
                set_test(test11, 30 * k * k + 60 * k + 24, taille, p);
            }
            if (test19.at(k)) {
                const std::size_t p = 30 * k + 19;
                set_test(test1, 30 * k * k + 38 * k + 12, taille, p);
                set_test(test17, 30 * k * k + 42 * k + 14, taille, p);
                set_test(test11, 30 * k * k + 48 * k + 18, taille, p);
                set_test(test19, 30 * k * k + 50 * k + 19, taille, p);
                set_test(test13, 30 * k * k + 56 * k + 23, taille, p);
                set_test(test29, 30 * k * k + 60 * k + 25, taille, p);
                set_test(test7, 30 * k * k + 62 * k + 27, taille, p);
                set_test(test23, 30 * k * k + 66 * k + 29, taille, p);
            }
            if (test23.at(k)) {
                const std::size_t p = 30 * k + 23;
                set_test(test19, 30 * k * k + 46 * k + 17, taille, p);
                set_test(test7, 30 * k * k + 52 * k + 22, taille, p);
                set_test(test23, 30 * k * k + 54 * k + 23, taille, p);
                set_test(test11, 30 * k * k + 60 * k + 28, taille, p);
                set_test(test13, 30 * k * k + 64 * k + 31, taille, p);
                set_test(test29, 30 * k * k + 66 * k + 32, taille, p);
                set_test(test1, 30 * k * k + 70 * k + 36, taille, p);
                set_test(test17, 30 * k * k + 72 * k + 37, taille, p);
            }
            if (test29.at(k)) {
                const std::size_t p = 30 * k + 29;
                set_test(test1, 30 * k * k + 58 * k + 28, taille, p);
                set_test(test29, 30 * k * k + 60 * k + 29, taille, p);
                set_test(test23, 30 * k * k + 66 * k + 35, taille, p);
                set_test(test19, 30 * k * k + 70 * k + 39, taille, p);
                set_test(test17, 30 * k * k + 72 * k + 41, taille, p);
                set_test(test13, 30 * k * k + 76 * k + 45, taille, p);
                set_test(test11, 30 * k * k + 78 * k + 47, taille, p);
                set_test(test7, 30 * k * k + 82 * k + 51, taille, p);
                set_test(test1, 30 * k * k + 88 * k + 57, taille, p);
            }
        }
    }
}

namespace premiers {
    void algorithme_crible2(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie) {
        std::size_t taille_crible = taille / 2;
        std::vector<bool> test;
        internal_crible2(taille_crible, test);

        sortie(2);
        for (std::size_t p = 1; p < taille_crible; ++p) {
            if (test.at(p)) {
                sortie(2 * p + 1);
            }
        }
    }

    void algorithme_crible23(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie) {
        std::size_t taille_crible = taille / 6;
        std::vector<bool> test1;
        std::vector<bool> test5;
        internal_crible23(taille_crible, test1, test5);
        sortie(2);
        sortie(3);
        for (std::size_t p = 0; p < taille_crible; ++p) {
            if (test1.at(p)) {
                sortie(6 * p + 1);
            }
            if (test5.at(p)) {
                sortie(6 * p + 5);
            }
        }
    }

    void algorithme_crible235(const std::size_t &taille, const std::function<void(const std::size_t &)> &sortie) {
        std::size_t taille_crible = taille / 30 + 1;
        std::vector<bool> test1, test7, test11, test13, test17, test19, test23, test29;
        internal_crible235(taille_crible, test1, test7, test11, test13, test17, test19, test23, test29);
        sortie(2);
        sortie(3);
        sortie(5);
        for (std::size_t p = 0; p < taille_crible; ++p) {
            if (test1.at(p)) { sortie(30 * p + 1); }
            if (test7.at(p)) { sortie(30 * p + 7); }
            if (test11.at(p)) { sortie(30 * p + 11); }
            if (test13.at(p)) { sortie(30 * p + 13); }
            if (test17.at(p)) { sortie(30 * p + 17); }
            if (test19.at(p)) { sortie(30 * p + 19); }
            if (test23.at(p)) { sortie(30 * p + 23); }
            if (test29.at(p)) { sortie(30 * p + 29); }
        }
    }

    void crible_simple(size_t taille, std::vector<bool> &test) {
        test.assign(taille, true);
        test.at(0) = false;
        test.at(1) = false;
        for (std::size_t p = 2; p * p < taille; ++p) {
            if (test.at(p)) {
                for (std::size_t k = p * p; k < taille; k += p)
                    test.at(k) = false;
            }
        }
    }

    void algorithme_super_crible(std::size_t taille, const std::vector<std::size_t> &roue,
                                 const std::function<void(const std::size_t &)> &sortie) {
        typedef std::vector<bool> Crible;
        typedef std::pair<std::size_t, std::size_t> Paire;
        typedef std::vector<Paire> VecteurPaire;
        typedef std::vector<VecteurPaire> MatricePaire;
        typedef std::vector<std::size_t> Vecteur;

        const std::size_t produit = std::reduce(roue.begin(), roue.end(), 1ULL, std::multiplies<>());
        const std::size_t taille_crible = taille / produit + 1;

        Crible masque(produit, true);
        masque.at(0) = false;

        for (const std::size_t p: roue)
            for (std::size_t q = p; q < produit; q += p)
                masque.at(q) = false;

        Vecteur restes;
        for (std::size_t p = 0; p < produit; ++p)
            if (masque.at(p)) restes.push_back(p);

        const std::size_t profondeur = restes.size();
        std::deque<Crible> test;
        const VecteurPaire ligne(profondeur, std::make_pair(0, 0));
        MatricePaire matrice(profondeur, ligne);

        for (std::size_t i = 0; i < profondeur; ++i) {
            const std::size_t reste = restes.at(i);
            test.emplace_back(taille_crible, true);
            // std::cout << "p = " << produit << ".k + " << reste << std::endl;

            for (std::size_t n = 0; n < produit; n += 2) {
                const std::size_t rrnr = reste * reste + n * reste;
                const auto it = std::find(restes.begin(), restes.end(), rrnr % produit);
                if (it != restes.end()) {
                    // std::cout << "n = " << n << "\t";
                    // std::cout << produit << ".[ " << produit << ".k² + " << 2*reste + n << ".k + " << rrnr/produit << " ] + " << rrnr%produit << std::endl;
                    matrice[i][utilitaires::distance(restes.begin(), it)] = std::make_pair(2 * reste + n,
                                                                                           rrnr / produit);
                }
            }
        }

        test[0][0] = false;
        for (std::size_t k = 0; produit * k * k < taille_crible; ++k) {
            for (std::size_t i = 0; i < profondeur; ++i) {
                if (test[i][k]) // Cas où p = produit*k + restes[i]
                {
                    const std::size_t p = produit * k + restes[i];
                    for (std::size_t j = 0; j < profondeur; ++j) {
                        const auto &debut = matrice[i][j];
                        for (std::size_t l = produit * k * k + debut.first * k + debut.second;
                             l < taille_crible; l += p)
                            test[j][l] = false;
                    }
                }
            }
        }

        for (const auto p: roue) {
            sortie(p);
        }

        for (std::size_t k = 0; k < taille_crible; ++k) {
            for (std::size_t i = 0; i < profondeur; ++i) {
                if (test[i][k]) {
                    sortie(produit * k + restes[i]);
                }
            }
        }
    }

    template<>
    bool miller_rabin(const mpz_nombre &n, unsigned short reps) {
        return n.premier(reps);
    }

    MeisselLehmer::MeisselLehmer(const std::vector<size_t> &_premiers) : premiers(_premiers) {
        std::size_t dernier = 0;
        std::size_t compteur = 0;
        cachePi.reserve(premiers.back());
        for (const auto &p: premiers) {
            std::fill_n(std::back_inserter(cachePi), p - dernier, compteur);
            ++compteur;
            dernier = p;
        }
    }

    size_t MeisselLehmer::P2(size_t m, size_t n) {
        size_t resultat = 0;

        auto m2 = racine::racine_carre(m);
        for (size_t i = n;; ++i) {
            auto pi = premiers.at(i);
            if (pi > m2)
                break;

            resultat += cachePi.at(m / pi) - cachePi.at(pi) + 1;
        }

        return resultat;
    }

    size_t MeisselLehmer::Phi(size_t m, size_t n) {
        if (n == 0)
            return m;
        if (m == 0)
            return 0;

        size_t pn = premiers.at(n - 1);

        if (m < cachePi.size() && pn <= racine::racine_carre(m) && pn >= racine::racine_cubique(m))
            return cachePi.at(m) - n + 1 + P2(m, n);
        return Phi(m, n - 1) - Phi(m / pn, n - 1);
    }

    size_t MeisselLehmer::pi(size_t m) {
        if (m < cachePi.size())
            return cachePi.at(m);

        auto m3 = racine::racine_cubique(m);
        auto n = cachePi.at(m3);

        size_t resultat = 0;
        resultat += Phi(m, n);
        resultat += n - 1;
        resultat -= P2(m, n);
        return resultat;
    }

    size_t MeisselLehmer::pi(size_t m, size_t n) {
        return pi(n) - pi(m);
    }

}
