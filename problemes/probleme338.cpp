#include "problemes.h"
#include "arithmetiques.h"

typedef long long nombre;

namespace {
    nombre somme(nombre n, nombre x, nombre modulo) {
        nombre a = arithmetiques::racine_carre(n);
        if (a > n / x) {
            a = n / x;
        }
        nombre resultat = 0;;
        for (nombre k = x; k <= n / (a + 1); k++) {
            resultat += n / k;
        }
        for (nombre k = 1; k < a; k++) {
            resultat += (n / k - n / (k + 1)) * k;
        }
        resultat += a * (n / a - std::max(n / (a + 1), x - 1));
        return resultat % modulo;
    }

    nombre somme2(nombre n, nombre modulo) {
        nombre resultat = 0;
        nombre a = arithmetiques::racine_carre(n);
        for (nombre k = 1; k <= n / (a + 1); k++)
            resultat = (resultat + (n / k) % modulo * ((n / (k + 1) % modulo))) % modulo;
        for (nombre k = 1; k <= a; k++) {
            resultat = (resultat + (n / k - n / (k + 1) - 1) % modulo * k * k % modulo) % modulo;
            resultat = (resultat + k * (k - 1)) % modulo;
        }
        return resultat;
    }

    nombre g(nombre n, nombre modulo) {
        nombre s1 = somme2(n, modulo);
        nombre s2 = somme(n, 2, modulo);
        nombre s3 = 0, s4 = 0;
        for (nombre b = 2; b * b <= n; b++) {
            s3 = (s3 + somme(n / b, b, modulo)) % modulo;
        }

        for (nombre a = 2; a * a <= n; a++) {
            s4 = (s4 + n / a / a) % modulo;
        }

        nombre resultat = (s1 - s2 - 2 * s3 + s4) % modulo;
        if (resultat < 0) resultat += modulo;
        return resultat;
    }

}


ENREGISTRER_PROBLEME(338, "Cutting Rectangular Grid Paper") {
    // A rectangular sheet of grid paper with integer dimensions w × h is given. Its grid spacing is 1.
    // When we cut the sheet along the grid lines into two pieces and rearrange those pieces without overlap, we can make new rectangles with different dimensions.
    //
    // For example, from a sheet with dimensions 9 × 4 , we can make rectangles with dimensions 18 × 2, 12 × 3 and 6 × 6 by cutting and rearranging as below:
    //
    //p338_gridpaper.gif
    // Similarly, from a sheet with dimensions 9 × 8 , we can make rectangles with dimensions 18 × 4 and 12 × 6 .
    //
    // For a pair w and h, let F(w,h) be the number of distinct rectangles that can be made from a sheet with dimensions w × h .
    // For example, F(2,1) = 0, F(2,2) = 1, F(9,4) = 3 and F(9,8) = 2.
    // Note that rectangles congruent to the initial one are not counted in F(w,h).
    // Note also that rectangles with dimensions w × h and dimensions h × w are not considered distinct.
    //
    // For an integer N, let G(N) be the sum of F(w,h) for all pairs w and h which satisfy 0 < h ≤ w ≤ N.
    // We can verify that G(10) = 55, G(10^3) = 971745 and G(10^5) = 9992617687.
    //
    // Find G(10^12). Give your answer modulo 10^8.
    nombre limite = 1'000'000'000'000;
    nombre modulo = 100'000'000;

    nombre resultat = g(limite, modulo);
    return std::to_string(resultat);
}
