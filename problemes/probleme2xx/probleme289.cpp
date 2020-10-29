#include "problemes.h"
#include "arithmetique.h"
#include "polynome.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    class Position {
    public:
        size_t nbColonnes;
        size_t nbLignes;

        size_t nbLignesRemplies;
        size_t positionLigne;
        std::vector<size_t> connectedID; //id numbers of connected components of each of the blocks along the growing edge
        std::vector<bool> merged;// true if outer edge merged together

    public:
        Position(size_t _nbColonnes, size_t _nbLignes)
                : nbColonnes(_nbColonnes), nbLignes(_nbLignes), nbLignesRemplies(0), positionLigne(0),
                  connectedID(nbColonnes + 1, 0), merged(nbColonnes, false) {}

        size_t maximum() const {
            return *std::max_element(connectedID.begin(), connectedID.end());
        }

        bool operator<(const Position &p) const {
            if (nbLignesRemplies != p.nbLignesRemplies)
                return nbLignesRemplies < p.nbLignesRemplies;

            if (positionLigne != p.positionLigne)
                return positionLigne < p.positionLigne;

            for (size_t i = 0; i < connectedID.size(); ++i) {
                if (connectedID[i] != p.connectedID[i])
                    return connectedID[i] < p.connectedID[i];
            }

            for (size_t i = 0; i < merged.size(); ++i) {
                if (merged[i] != p.merged[i])
                    return merged[i] < p.merged[i];
            }

            return false;
        }

        [[nodiscard]] std::optional<Position> deplacer(unsigned short m) const {
            Position p(*this);
            if (p.ajouter(m >= 12, m % 4, (m / 4) % 3))
                return std::move(p);
            else
                return std::nullopt;
        }

    private:
        bool ajouter(bool mergetopleft, size_t mergebotleft, size_t mergebotright) {
            if (positionLigne == 0 && (mergetopleft || mergebotleft == 1 || mergebotleft == 2))
                return false;

            if (mergebotleft == 1 && merged[positionLigne - 1])
                return false;

            if (mergebotleft == 2 && merged[positionLigne])
                return false;

            if (mergebotright == 2 && (positionLigne == nbColonnes - 1 || merged[positionLigne + 1]))
                return false;

            if (mergetopleft && mergebotleft == 1)
                return false;

            if (mergebotright == 1 && mergebotleft == 3)
                return false;

            size_t id = 0;

            // merge with square to the left
            if (mergetopleft || mergebotleft == 1) {
                if (connectedID[positionLigne - 1] == 0)
                    return false;

                id = connectedID[positionLigne - 1];
            }

            if (positionLigne > 0)
                merged[positionLigne - 1] = mergetopleft;

            // merge with square to the bottom left
            if (mergebotleft == 2) {
                if (connectedID[positionLigne] == 0 || connectedID[positionLigne] == id)
                    return false;

                if (id != 0)
                    merge(id, connectedID[positionLigne]);

                id = connectedID[positionLigne];
            }

            // merge with square to the bottom
            if (mergebotleft == 3 || mergebotright == 1) {
                if (connectedID[positionLigne + 1] == 0 || connectedID[positionLigne + 1] == id)
                    return false;

                if (id != 0)
                    merge(id, connectedID[positionLigne + 1]);

                id = connectedID[positionLigne + 1];
            }

            merged[positionLigne] = mergebotright != 0;

            // merge with square to the bottom right
            if (mergebotright == 2) {
                if (connectedID[positionLigne + 2] == 0 || connectedID[positionLigne + 2] == id)
                    return false;

                if (id != 0)
                    merge(id, connectedID[positionLigne + 2]);

                if (id != connectedID[positionLigne + 1]
                    && connectedID[positionLigne + 1] != 0
                    && count(connectedID[positionLigne + 1]) == 1)
                    return false;

                id = connectedID[positionLigne + 2];
                connectedID[positionLigne + 1] = connectedID[positionLigne + 2];

                if (positionLigne + 1 < nbColonnes)
                    merged[positionLigne + 1] = true;
            }

            if (id == 0)
                id = 1 + maximum();

            nombre oldId = connectedID[positionLigne];
            connectedID[positionLigne] = id;

            positionLigne++;

            // check if made an inaccessible component
            if (oldId != 0 && count(oldId) == 0)
                return false;

            normalise();

            // reset to next row if row is full
            if (positionLigne == nbColonnes) {
                if (connectedID[nbColonnes] != 0 && count(connectedID[nbColonnes]) == 1)
                    return false;

                nbLignesRemplies++;
                positionLigne = 0;

                for (size_t i = connectedID.size() - 1; i > 0; i--)
                    connectedID[i] = connectedID[i - 1];

                for (size_t i = merged.size() - 1; i > 0; i--)
                    merged[i] = merged[i - 1];

                connectedID[0] = 0;
                merged[0] = false;
            }

            return true;
        }

        void merge(size_t nouveau, size_t ancien) {
            std::replace(connectedID.begin(), connectedID.end(), ancien, nouveau);
        }

        size_t count(size_t id) const {
            return static_cast<size_t>(std::count(connectedID.begin(), connectedID.end(), id));
        }

        void swap(size_t id1, size_t id2) {
            for (size_t &id: connectedID) {
                if (id == id2)
                    id = id1;
                else if (id == id1)
                    id = id2;
            }
        }

        void normalise() {
            size_t suivant = 1;
            for (size_t &id: connectedID) {
                if (id > suivant)
                    swap(id, suivant);
                if (id == suivant)
                    ++suivant;
            }
        }
    };
}


ENREGISTRER_PROBLEME(289, "Eulerian Cycles") {
    // Let C(x,y) be a circle passing through the points (x, y), (x, y+1), (x+1, y) and (x+1, y+1).
    //
    // For positive integers m and n, let E(m,n) be a configuration which consists of the m·n circles:
    // { C(x,y): 0 ≤ x < m, 0 ≤ y < n, x and y are integers }
    // 
    // An Eulerian cycle on E(m,n) is a closed path that passes through each arc exactly once.
    // Many such paths are possible on E(m,n), but we are only interested in those which are not self-crossing: A
    // non-crossing path just touches itself at lattice points, but it never crosses itself.
    //
    // The image below shows E(3,3) and an example of an Eulerian non-crossing path.
    //
    // p289_euler.gif
    //
    // Let L(m,n) be the number of Eulerian non-crossing paths on E(m,n).
    // For example, L(1,2) = 2, L(2,2) = 37 and L(3,3) = 104290.
    //
    // Find L(6,10) mod 10**10.
    nombre modulo = 10000000000ULL;
    nombre nbColonnes = 6;
    nombre nbLignes = 10;

    std::map<Position, nombre> cache{{Position(nbColonnes, nbLignes), 1}};

    while (true) {
        auto it = cache.begin();
        Position p = it->first;
        nombre num = it->second;

        if (p.nbLignesRemplies == nbLignes)
            break;

        cache.erase(it);

        for (unsigned short m = 0; m < 24; m++) {
            if (auto p2 = p.deplacer(m)) {
                cache[*p2] += num;
                cache[*p2] %= modulo;
            }
        }

    }

    nombre resultat = 0;
    for (auto p: cache) {
        if (p.first.maximum() == 1) {
            resultat += p.second;
            resultat %= modulo;
        }
    }

    return std::to_string(resultat);
}
