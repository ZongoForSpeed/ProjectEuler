#include "problemes.h"
#include "arithmetiques.h"

#include <unordered_map>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::unordered_map<nombre, nombre> dictionnaire;

ENREGISTRER_PROBLEME(310, "Nim Square") {
    // Alice and Bob play the game Nim Square.
    // Nim Square is just like ordinary three-heap normal play Nim, but the players may only remove a square number of
    // stones from a heap. The number of stones in the three heaps is represented by the ordered triple (a,b,c).
    // If 0≤a≤b≤c≤29 then the number of losing positions for the next player is 1160.
    //
    // Find the number of losing positions for the next player if 0≤a≤b≤c≤100000.
    const nombre piles = 3;
    const nombre taille = 100000;

    vecteur etats(taille + 1);
    for (nombre i = 0; i <= taille; ++i) {
        nombre j = 0;
        while (true) {
            bool reachable = false;
            for (nombre k = 1; k * k <= i; ++k)
                if (etats[i - k * k] == j) reachable = true;

            if (!reachable) break;
            ++j;
        }
        etats[i] = j;
    }

    dictionnaire compteurs;
    for (nombre i = 0; i <= taille; ++i)
        ++compteurs[etats[i]];

    dictionnaire total{{0, 1}};
    for (nombre i = 0; i < piles; ++i) {
        dictionnaire nouveau_total;
        for (const auto &t: total)
            for (const auto &c: compteurs) {
                nouveau_total[t.first ^ c.first] += t.second * c.second;
            }
        std::swap(total, nouveau_total);
    }

    nombre resultat = 0;
    for (const auto &t: total) {
        if (t.first == 0) resultat += t.second;
    }

    for (const auto &c: compteurs) {
        if (c.first == 0) resultat += (3 * taille + 5) * c.second;
    }

    resultat = resultat / 6;
    return std::to_string(resultat);
}
