#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>
#include <boost/algorithm/string.hpp>

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef boost::rational<nombre> fraction;
typedef std::pair<nombre, nombre> paire;

namespace {
    fraction aire(const paire &A, const paire &B, const paire &C) {
        nombre abc = (B.first - A.first) * (C.second - A.second) - (C.first - A.first) * (B.second - A.second);
        if (abc < 0)
            abc = -abc;
        return fraction(abc, 2);
    }

    bool contient(const paire &A, const paire &B, const paire &C) {
        static const paire O = std::make_pair(0, 0);
        const fraction ABC = aire(A, B, C);
        const fraction OBC = aire(O, B, C);
        const fraction AOC = aire(A, O, C);
        const fraction ABO = aire(A, B, O);

        return (ABC == OBC + AOC + ABO);
    }
}

ENREGISTRER_PROBLEME(102, "Triangle containment") {
    // Three distinct points are plotted at random on a Cartesian plane, for which -1000 ≤ x, y ≤ 1000, such that a
    // triangle is formed.
    //
    // Consider the following two triangles:
    // 
    //                                  A(-340,495), B(-153,-910), C(835,-947)
    //
    //                                  X(-175,41), Y(-421,-714), Z(574,-645)
    // 
    // It can be verified that triangle ABC contains the origin, whereas triangle XYZ does not.
    // 
    // Using triangles.txt (right click and 'Save Link/Target As...'), a 27K text file containing the co-ordinates of
    // one thousand "random" triangles, find the number of triangles for which the interior contains the origin.
    // 
    // NOTE: The first two examples in the file represent the triangles in the example given above.
    std::ifstream ifs("data/p102_triangles.txt");
    nombre resultat = 0;
    std::string ligne;
    while (ifs >> ligne) {
        std::vector<std::string> v;
        boost::split(v, ligne, boost::is_any_of(","));
        const paire A(stoll(v[0]), stoll(v[1]));
        const paire B(stoll(v[2]), stoll(v[3]));
        const paire C(stoll(v[4]), stoll(v[5]));
        if (contient(A, B, C))
            ++resultat;
    }
    return std::to_string(resultat);
}
