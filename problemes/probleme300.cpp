#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<signed char, signed char> Point;
typedef std::vector<Point> Chemin;

namespace {
    void generer(const Point &p, const Chemin &chemin, std::set<Chemin> &resultat, size_t profondeur) {
        static std::set<std::pair<Point, Chemin>> cache;
        if (cache.find(std::make_pair(p, chemin)) != cache.end())
            return;

        cache.emplace(p, chemin);

        if (profondeur == chemin.size()) {
            resultat.insert(chemin);
            return;
        }

        signed char x, y;
        std::tie(x, y) = p;
        std::deque<Point> suivants{Point(x + 1, y), Point(x - 1, y), Point(x, y + 1), Point(x, y - 1)};
        for (auto suivant: suivants) {
            if (std::find(chemin.rbegin(), chemin.rend(), suivant) == chemin.rend()) {
                Chemin c = chemin;
                c.push_back(suivant);
                generer(suivant, c, resultat, profondeur);
            }
        }
    }

    bool voisin(const Point &p1, const Point &p2) {
        if (p1.first == p2.first) {
            return p1.second == p2.second + 1 || p1.second + 1 == p2.second;
        } else if (p1.second == p2.second) {
            return p1.first == p2.first + 1 || p1.first + 1 == p2.first;
        }

        return false;
    }
}

ENREGISTRER_PROBLEME(300, "Protein folding") {
    // In a very simplified form, we can consider proteins as strings consisting of hydrophobic (H) and polar (P)
    // elements, e.g. HHPPHHHPHHPH.
    // For this problem, the orientation of a protein is important; e.g. HPP is considered distinct from PPH. Thus,
    // there are 2n distinct proteins consisting of n elements.
    //
    // When one encounters these strings in nature, they are always folded in such a way that the number of H-H contact
    // points is as large as possible, since this is energetically advantageous.
    // As a result, the H-elements tend to accumulate in the inner part, with the P-elements on the outside.
    // Natural proteins are folded in three dimensions of course, but we will only consider protein folding in two
    // dimensions.
    //
    // The figure below shows two possible ways that our example protein could be folded (H-H contact points are shown
    // with red dots).
    //
    // p300_protein.gif
    // The folding on the left has only six H-H contact points, thus it would never occur naturally.
    // On the other hand, the folding on the right has nine H-H contact points, which is optimal for this string.
    //
    // Assuming that H and P elements are equally likely to occur in any position along the string, the average number
    // of H-H contact points in an optimal folding of a random protein string of length 8 turns out to be
    // 850 / 2**8=3.3203125.
    //
    // What is the average number of H-H contact points in an optimal folding of a random protein string of length 15?
    // Give your answer using as many decimal places as necessary for an exact 
    // result.
    nombre longueur = 15;
    nombre nombre_proteines = 1UL << longueur;

    std::set<Chemin> chemins;
    {
        const Point debut(0, 0);
        const Chemin c{debut};

        generer(debut, c, chemins, longueur);
    }

    std::set<std::vector<size_t>> voisinages;
    for (auto c: chemins) {
        std::vector<size_t> voisins;
        for (size_t n = 0; n < c.size(); ++n)
            for (size_t m = n + 1; m < c.size(); ++m) {
                if (voisin(c[n], c[m])) {
                    size_t masque = (1ULL << n) + (1ULL << m);
                    voisins.push_back(masque);
                }
            }

        voisinages.insert(voisins);
    }

    nombre somme = 0;
    for (size_t proteine = 0; proteine < nombre_proteines; ++proteine) {
        nombre max_compteur = 0;
        for (auto voisins: voisinages) {
            nombre compteur = 0;
            for (size_t masque: voisins) {
                if ((proteine & masque) == masque)
                    ++compteur;
            }
            max_compteur = std::max(max_compteur, compteur);
        }

        somme += max_compteur;
    }

    long double resultat = static_cast<long double>(somme) / nombre_proteines;
    std::cout << std::setprecision(20);
    std::cout << "Solution: " << somme << " / " << nombre_proteines << " = " << resultat << std::endl;

    return std::to_string(resultat, 13);
}
