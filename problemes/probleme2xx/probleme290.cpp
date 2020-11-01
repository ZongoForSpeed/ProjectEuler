#include "problemes.h"
#include "arithmetique.h"
#include "chiffres.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(290, "Digital Signature") {
    // How many integers 0 ≤ n < 10**18 have the property that the sum of the digits of n equals the sum of digits of 137n?
    const short taille = 18;

    typedef std::map<std::pair<nombre/*difference*/, nombre/*retenue*/>, size_t/*compteur*/> Table;

    Table table{{std::make_pair(0, 0), 1}};

    for (short c = 0; c < taille; ++c) {
        Table suivant;
        for (short d = 0; d < 10; ++d) {
            for (auto&[paire, compteur]: table) {
                // Pour tous les nombre x ayant une difference D et une retenue R
                // alors dx a une retenue de n / 10
                //            et une difference de difference + d - n%10
                // où 137*d + retenue
                auto &[difference, retenue] = paire;
                nombre n = 137 * d + retenue;
                suivant[std::make_pair(difference + d - n % 10, n / 10)] += compteur;
            }
        }
        std::swap(suivant, table);
    }

    size_t resultat = 0;
    for (auto&[paire, compteur]: table) {
        auto &[difference, retenue] = paire;
        if (chiffres::somme_chiffres(retenue) == difference)
            resultat += compteur;
    }

    return std::to_string(resultat);
}
