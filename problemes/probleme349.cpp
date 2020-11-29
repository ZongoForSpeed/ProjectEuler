#include "problemes.h"
#include "numerique.h"
#include "multidimension.h"

namespace {
    enum Direction {
        NORD,
        OUEST,
        SUD,
        EST
    };

    Direction tourne(Direction d, bool gauche) {
        switch (d) {
            case NORD:
                return gauche ? OUEST : EST;
            case OUEST:
                return gauche ? SUD : NORD;
            case SUD:
                return gauche ? EST : OUEST;
            case EST:
                return gauche ? NORD : SUD;
        }
    }

    struct Position {
        unsigned long x;
        unsigned long y;

        void avance(Direction d) {
            switch (d) {
                case NORD:
                    ++y;
                    break;
                case OUEST:
                    ++x;
                    break;
                case SUD:
                    --y;
                    break;
                case EST:
                    --x;
                    break;
            }
        }
    };
}

ENREGISTRER_PROBLEME(349, "Langton's ant") {
    // An ant moves on a regular grid of squares that are coloured either black or white.
    // The ant is always oriented in one of the cardinal directions (left, right, up or down) and moves from square to
    // adjacent square according to the following rules:
    //  - if it is on a black square, it flips the colour of the square to white, rotates 90 degrees counterclockwise
    //  and moves forward one square.
    //  - if it is on a white square, it flips the colour of the square to black, rotates 90 degrees clockwise and moves
    //  forward one square.
    //
    // Starting with a grid that is entirely white, how many squares are black after 10^18 moves of the ant?
    long long limite = 1'000'000'000'000'000'000LL;

    const unsigned int taille = 128;
    multidimension<bool, 2> grille(taille, taille, false);

    Position p{taille / 2, taille / 2};
    Direction direction = NORD;

    // Le cycle de Langton's_ant est de 104 (cf https://en.wikipedia.org/wiki/Langton%27s_ant)
    const long long cycle = 104;
    const long long reste = limite % cycle; // = 40

    long long compteur = 0LL;
    long long dernier = compteur;

    std::vector<int> deltas = {0};
    const unsigned int etatStable = 10;

    long long etapes = 0;
    while (etapes < limite) {
        if (etapes % cycle == reste) {
            // Nombre de cases noires par rapport au dernier cycle
            auto delta = int(compteur - dernier);
            deltas.push_back(delta);
            dernier = compteur;

            if (deltas.size() >= etatStable) {
                // Recherche d'un état stable dans les derniers deltas ?
                auto it = std::find_if_not(deltas.rbegin(), deltas.rend(),
                                           [&delta](const int &d) { return d == delta; });

                if (std::distance(deltas.rbegin(), it) >= etatStable) {
                    compteur += (limite - etapes) / cycle * delta;
                    break;
                }
            }
        }

        if (!grille[p.x][p.y]) {
            // Case blanche
            grille[p.x][p.y] = true;
            compteur++;

            direction = tourne(direction, true);
        } else {
            // Case noire
            grille[p.x][p.y] = false;
            compteur--;

            direction = tourne(direction, false);
        }

        p.avance(direction);
        etapes++;
    }

    return std::to_string(compteur);
}
