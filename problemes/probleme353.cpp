#include "problemes.h"
#include "format.h"
#include "multidimension.h"
#include "premiers.h"
#include "racine.h"
#include "timer.h"
#include "utilitaires.h"

#include <set>
#include <tuple>


namespace {
    double distance(const std::tuple<long, long, long> &a, const std::tuple<long, long, long> &b, long r) {
        // https://en.wikipedia.org/wiki/Great-circle_distance#From_chord_length
        if (a == b) {
            return 0.0;
        }

        auto &[xa, ya, za] = a;
        auto &[xb, yb, zb] = b;

        double const C = std::hypot(xa - xb, ya - yb, za - zb) / static_cast<double>(r);

        return static_cast<double>(2 * r) * std::asin(C / 2);
    }

    double cout(const std::tuple<long, long, long> &a, const std::tuple<long, long, long> &b, long r) {
        double d = distance(a, b, r);
        d /= M_PI * static_cast<double>(r);
        return d * d;
    }

    void permutation(std::set<std::tuple<long, long, long>> &bases, long x, long y, long z) {
        // x, y, z
        bases.emplace(x, y, z);
        // z, x, y
        bases.emplace(z, x, y);
        // y, z, x
        bases.emplace(y, z, x);

        // x, z, y
        bases.emplace(x, z, y);
        // y, x, z
        bases.emplace(y, x, z);
        // z, y, x
        bases.emplace(z, y, x);

        // x, y, -z
        bases.emplace(x, y, -z);
        // z, x, -y
        bases.emplace(z, x, -y);
        // y, z, -x
        bases.emplace(y, z, -x);

        // x, z, -y
        bases.emplace(x, z, -y);
        // y, x, -z
        bases.emplace(y, x, -z);
        // z, y, -x
        bases.emplace(z, y, -x);
    }

    double
    algorithme_dijkstra(const std::vector<std::tuple<long, long, long>> &noeuds, size_t debut, size_t fin, long r) {
        std::vector<double> distance(noeuds.size(), std::numeric_limits<double>::max());
        std::vector<double> precedent(noeuds.size(), static_cast<double>(debut));

        distance[debut] = 0;
        std::set<size_t> Q;
        for (size_t n = 0; n < noeuds.size(); ++n) {
            Q.insert(n);
        }

        while (!Q.empty()) {
            size_t suivant = 0;
            double minimum = std::numeric_limits<double>::max();
            for (const size_t n: Q) {
                if (distance[n] < minimum) {
                    suivant = n;
                    minimum = distance[n];
                }
            }

            if (suivant == fin) {
                break;
            }

            Q.erase(suivant);
            auto &courant = noeuds[suivant];
            for (const size_t n: Q) {
                const double C = distance[suivant] + cout(courant, noeuds[n], r);
                if (distance[n] > C) {
                    distance[n] = C;
                    precedent[n] = static_cast<double>(suivant);
                }
            }
        }

        // nombre n = fin;
        // while (n != debut) {
        //    resultat.push_back(n);
        //    n = precedent[n];
        // }
        //
        //resultat.push_back(debut);
        //
        // resultat = vecteur(resultat.rbegin(), resultat.rend());
        return distance[fin];
    }

    double M(long r) {
        Timer t("Calcul M");
        std::set<std::tuple<long, long, long>> bases;
        for (long x = 0; x <= r; ++x) {
            for (long y = x; y <= r; ++y) {
                long const Z = r * r - x * x - y * y;
                if (auto dz = racine::carre_parfait(Z)) {
                    long const z = dz.value();
                    permutation(bases, x, y, z);
                }
            }
        }

        std::tuple<long, long, long> const NorthPole{0, 0, r};
        std::tuple<long, long, long> const SouthPole{0, 0, -r};

        std::cout << bases.size() << std::endl;
        std::cout << "NorthPole = " << NorthPole << std::endl;
        std::cout << "SouthPole = " << SouthPole << std::endl;

        // std::cout << ::distance(NorthPole, SouthPole, r) << std::endl;
        // std::cout << cout(NorthPole, SouthPole, r) << std::endl;

        std::vector<std::tuple<long, long, long>> noeuds(bases.begin(), bases.end());
        size_t indiceNP = static_cast<size_t>(std::distance(bases.begin(), bases.find(NorthPole)));
        size_t indiceSP = static_cast<size_t>(std::distance(bases.begin(), bases.find(SouthPole)));

        double distance_min = algorithme_dijkstra(noeuds, indiceNP, indiceSP, r);
        std::cout << "M(" << r << ") = " << format::to_fixed(distance_min, 10) << std::endl;
        return distance_min;
    }
}

ENREGISTRER_PROBLEME(353, "Risky moon") {
    // A moon could be described by the sphere C(r) with centre (0,0,0) and radius r.
    //
    // There are stations on the moon at the points on the surface of C(r) with integer coordinates.
    // The station at (0,0,r) is called North Pole station, the station at (0,0,-r) is called South Pole station.
    //
    // All stations are connected with each other via the shortest road on the great arc through the stations.
    // A journey between two stations is risky. If d is the length of the road between two stations, (d/πr)² is a
    // measure for the risk of the journey (let us call it the risk of the road).
    // If the journey includes more than two stations, the risk of the journey is the sum of risks of the used roads.
    //
    //A direct journey from the North Pole station to the South Pole station has the length πr and risk 1.
    // The journey from the North Pole station to the South Pole station via (0,r,0) has the same length, but a smaller risk:
    //
    // (½πr / πr)² + (½πr / πr)² = 0.5
    //
    // The minimal risk of a journey from the North Pole station to the South Pole station on C(r) is M(r).
    //
    // You are given that M(7) = 0.1784943998 rounded to 10 digits behind the decimal point.
    //
    // Find Sum n=1...15 M(2^n - 1).
    //
    // Give your answer rounded to 10 digits behind the decimal point in the form a.bcdefghijk.
    M(1);
    M(7);
    double resultat = 0.0;
    for (size_t n = 1; n <= 15; ++n) {
        resultat += M((1u << n) - 1u);
    }
    return format::to_fixed(resultat, 10);
}
