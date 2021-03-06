#include "problemes.h"
#include "utilitaires.h"
#include "multidimension.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(345, "Matrix Sum") {
    // We define the Matrix Sum of a matrix as the maximum sum of matrix elements with each element being the only one
    // in his row and column. For example, the Matrix Sum of the matrix below equals 3315
    // ( = 863 + 383 + 343 + 959 + 767):
    //
    // multidimension<nombre, 2> matrice {
    //     {  7,  53, 183, 439, 863},
    //     {497, 383, 563,  79, 973},
    //     {287,  63, 343, 169, 583},
    //     {627, 343, 773, 959, 943},
    //     {767, 473, 103, 699, 303}
    // };
    // 
    // Find the Matrix Sum of:
    //
    multidimension<nombre, 2> matrice{
            {7,   53,  183, 439, 863, 497, 383, 563, 79,  973, 287, 63,  343, 169, 583},
            {627, 343, 773, 959, 943, 767, 473, 103, 699, 303, 957, 703, 583, 639, 913},
            {447, 283, 463, 29,  23,  487, 463, 993, 119, 883, 327, 493, 423, 159, 743},
            {217, 623, 3,   399, 853, 407, 103, 983, 89,  463, 290, 516, 212, 462, 350},
            {960, 376, 682, 962, 300, 780, 486, 502, 912, 800, 250, 346, 172, 812, 350},
            {870, 456, 192, 162, 593, 473, 915, 45,  989, 873, 823, 965, 425, 329, 803},
            {973, 965, 905, 919, 133, 673, 665, 235, 509, 613, 673, 815, 165, 992, 326},
            {322, 148, 972, 962, 286, 255, 941, 541, 265, 323, 925, 281, 601, 95,  973},
            {445, 721, 11,  525, 473, 65,  511, 164, 138, 672, 18,  428, 154, 448, 848},
            {414, 456, 310, 312, 798, 104, 566, 520, 302, 248, 694, 976, 430, 392, 198},
            {184, 829, 373, 181, 631, 101, 969, 613, 840, 740, 778, 458, 284, 760, 390},
            {821, 461, 843, 513, 17,  901, 711, 993, 293, 157, 274, 94,  192, 156, 574},
            {34,  124, 4,   878, 450, 476, 712, 914, 838, 669, 875, 299, 823, 329, 699},
            {815, 559, 813, 459, 522, 788, 168, 586, 966, 232, 308, 833, 251, 631, 107},
            {813, 883, 451, 509, 615, 77,  281, 613, 459, 205, 380, 274, 302, 35,  805}
    };

    nombre taille = matrice.size();
    nombre limite = (1ul << taille);

    std::vector<nombre> dp(limite, 0);
    std::vector<nombre> colonnes(limite, 0);

    for (size_t i = 1; i < limite; ++i)
        colonnes[i] = (i & 1) + colonnes[i >> 1];

    for (size_t i = 0; i < limite; i++)
        for (size_t k = 0; k < taille; k++) {
            if (i & (1 << k))
                continue;

            nombre somme = dp[i] + matrice[colonnes[i]][k];
            if (dp[i + (1 << k)] < somme)
                dp[i + (1 << k)] = somme;
        }

    nombre resultat = dp[limite - 1];
    return std::to_string(resultat);
}
