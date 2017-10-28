#include <gtest/gtest.h>

#include "fenwick.h"
#include "utilitaires.h"

    // TEST(test_fenwick, random_fenwick) {
    //     // Number of elements in the array
    //     const unsigned long N = 4 * 1024 * 1024;            // Elements in the array
    //     const unsigned long COUNTS = 1'024;                 // Size of values stored
    //     typedef unsigned long sum_t;                        // Should be able to hold N * (COUNTS - 1)

    //     // Number of queries to perform
    //     const size_t NQUERIES = 100;

    //     std::vector<std::pair<unsigned long, unsigned long>> queries;
    //     queries.reserve(NQUERIES);
    //     unsigned int seed = 329629153ul;

    //     // generate the bounds for all of the queries
    //     srandom(seed + 1);
    //     for (unsigned int i = 0; i < NQUERIES; ++i) {
    //         unsigned long a = static_cast<unsigned long>(random()) % N;
    //         unsigned long b = static_cast<unsigned long>(random()) % N;

    //         if (a > b) {
    //             std::swap(a, b);
    //         }

    //         queries.emplace_back(a, b);
    //     }

    //     /*****************************************************************/
    //     /*   FLAT ARRAY METHOD                                           */
    //     /*****************************************************************/
    //     //std::vector<sum_t> array(N, 0);
    //     //
    //     //time1 = clock();
    //     //// Store random numbers in a flat array
    //     //srandom(seed);
    //     //for (unsigned long i = 0; i < N; i++)
    //     //    array[i] = static_cast<unsigned long>(random()) % COUNTS;
    //     //time2 = clock();    // time2 - time1 = time for setup
    //     //// perform the queries
    //     //for (auto &t: queries) {
    //     //    sum_t asum = 0;
    //     //    for (unsigned long i = t.first; i < t.second; i++)
    //     //        asum += array[i];
    //     //    printf(" %lu", asum);
    //     //}
    //     //time3 = clock();    // time3 - time2 = time for queries
    //     //
    //     //printf("\nFlat Array:\n Build: %f\n Query: %f\n",
    //     //       (time2 - time1) * (1.0 / CLOCKS_PER_SEC),
    //     //       (time3 - time2) * (1.0 / CLOCKS_PER_SEC));

    //     /*****************************************************************/
    //     /*   FENWICK TREE METHOD                                         */
    //     /*****************************************************************/
    //     // Store the same random numbers in a Fenwick tree
    //     Fenwick<sum_t> fenwick(N);

    //     srandom(seed);
    //     for (unsigned int i = 0; i < N; i++)
    //         fenwick[i] = static_cast<unsigned long>(random()) % COUNTS;

    //     fenwick.initialisation();

    //     // perform the queries
    //     std::vector<sum_t> resultat;
    //     resultat.reserve(NQUERIES);
    //     for (auto &t: queries) {
    //         auto range = fenwick.range(t.first, t.second);
    //         resultat.push_back(range);
    //     }

    //     std::vector<sum_t> objectif{87981345, 1018050452, 37060257, 133931587, 2082302311, 127607876, 499939565,
    //                                 778250548, 1356376781, 1678639060, 576926234, 810701986, 1196425448, 118049060,
    //                                 310361498, 252146278, 218292164, 195436034, 297455402, 585469786, 220973193,
    //                                 1237649723, 1064127610, 897409608, 832488593, 98156557, 120598571, 177040996,
    //                                 755520873, 115287474, 776179383, 681649582, 738411683, 302101748, 156312892,
    //                                 206347412, 1404317992, 98847045, 901696409, 597436785, 214860533, 1147372135,
    //                                 1211863369, 1404996371, 762309048, 1258421637, 761969197, 49908239, 280576568,
    //                                 416977055, 30965878, 814448073, 408393725, 449595850, 236265833, 899265000,
    //                                 1498879619, 313451978, 573148765, 1680186637, 1093867521, 728110969, 627227586,
    //                                 1837301002, 930273713, 90125158, 797068335, 127038933, 327740170, 370749414,
    //                                 175262817, 585476664, 1123744044, 184901258, 1446844694, 785242039, 141349029,
    //                                 1418849924, 45188875, 1030374824, 385654707, 270975251, 120498130, 243466699,
    //                                 1678607648, 1012356787, 261411522, 170141557, 275803710, 210310589, 266128664,
    //                                 28014922, 362348117, 643862674, 1733566914, 1382944184, 638406591, 164758742,
    //                                 967673249, 938444584};

    //     BOOST_CHECK_EQUAL_COLLECTIONS(objectif.begin(), objectif.end(),
    //                                   resultat.begin(), resultat.end());
    // }

    TEST(test_fenwick, modulo_fenwick) {
        size_t taille = 100 + 1;
        std::vector<bool> crible(taille, true);
        std::vector<size_t> phi(taille, 0);

        std::iota(phi.begin(), phi.end(), 0ul);
        for (size_t i = 2; i < taille; ++i) {
            if (crible[i]) {
                for (size_t j = i; j < taille; j += i) {
                    crible[j] = false;
                    phi[j] /= i;
                    phi[j] *= i-1;
                }
            }
        }

        // std::cout << phi << std::endl;
        Fenwick<long long> fenwick(taille);
        std::vector<long long> f(taille, 0);
        for (size_t n = taille - 1; n > 5; --n) {
            size_t k = phi[n];
            f[n] = 1 + fenwick.range(k, n-1);
            fenwick.add(k, f[n]);
        }
        
        EXPECT_EQ(482073668, f[6]);
    }
