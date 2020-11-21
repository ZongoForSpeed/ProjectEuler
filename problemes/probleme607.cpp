#include <maths/premiers.h>
#include <maths/arithmetique.h>
#include "problemes.h"
#include "utilitaires.h"

typedef long double nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre calcul_decalage(nombre init_theta, const vecteur &n, const vecteur &epaisseurs) {
        nombre decalage = epaisseurs.front() * std::tan(init_theta);
        nombre courant = init_theta;
        for (size_t i = 1; i < epaisseurs.size(); ++i) {
            nombre n_1 = n[i - 1];
            nombre n_2 = n[i];
            nombre suivant = std::asin(std::sin(courant) * n_1 / n_2);
            decalage += epaisseurs[i] * std::tan(suivant);
            courant = suivant;
        }

        return decalage;
    }
}

ENREGISTRER_PROBLEME(607, "Divisibility streaks") {
    // Frodo and Sam need to travel 100 leagues due East from point A to point B. On normal terrain, they can cover 10
    // leagues per day, and so the journey would take 10 days. However, their path is crossed by a long marsh which runs
    // exactly South-West to North-East, and walking through the marsh will slow them down. The marsh is 50 leagues wide
    // at all points, and the mid-point of AB is located in the middle of the marsh. A map of the region is shown in the
    // diagram below:
    // p607_marsh.png
    //
    // The marsh consists of 5 distinct regions, each 10 leagues across, as shown by the shading in the map. The strip
    // closest to point A is relatively light marsh, and can be crossed at a speed of 9 leagues per day. However, each
    // strip becomes progressively harder to navigate, the speeds going down to 8, 7, 6 and finally 5 leagues per day
    // for the final region of marsh, before it ends and the terrain becomes easier again, with the speed going back to
    // 10 leagues per day.
    //
    // If Frodo and Sam were to head directly East for point B, they would travel exactly 100 leagues, and the journey
    // would take approximately 13.4738 days. However, this time can be shortened if they deviate from the direct path.
    //
    // Find the shortest possible time required to travel from point A to B, and give your answer in days, rounded to
    // 10 decimal places.
    const vecteur n{1.0L, 10.0L / 9.0L, 10.0L / 8.0L, 10.0L / 7.0L, 10.0L / 6.0L, 10.0L / 5.0L, 1.0L};
    const vecteur vitesses{10.0L, 9.0L, 8.0L, 7.0L, 6.0L, 5.0L, 10.0L};

    nombre normal_terrain = (100.0L / std::sqrt(2.0L) - 50.0L) / 2.0L;
    nombre marsh = 10.0L;

    const vecteur epaisseurs{normal_terrain, marsh, marsh, marsh, marsh, marsh, normal_terrain};

    nombre gauche = M_PIl / 3;
    nombre droite = M_PIl / 6;
    while (std::abs(gauche - droite) > 1.0e-15L) {
        nombre milieu = (gauche + droite) / 2;
        nombre delta = 50.0L * std::sqrt(2.0L) - calcul_decalage(milieu, n, epaisseurs);
        if (delta < 0) {
            gauche = milieu;
        } else {
            droite = milieu;
        }
    }

    nombre angle_courant = (gauche + droite) / 2;
    nombre resultat = epaisseurs.front() / std::cos(angle_courant) / vitesses.front();

    for (size_t i = 1; i < epaisseurs.size(); ++i) {
        nombre n_1 = n[i - 1];
        nombre n_2 = n[i];
        nombre angle_suivant = std::asin(std::sin(angle_courant) * n_1 / n_2);
        resultat += (epaisseurs[i] / std::cos(angle_suivant)) / vitesses[i];
        angle_courant = angle_suivant;
    }

    return std::to_fixed(resultat, 10);
}
