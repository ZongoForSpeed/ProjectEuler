#include <cmath>
#include <mpf_nombre.h>
#include "problemes.h"
#include "numerique.h"
#include "timer.h"
#include "chiffres.h"

namespace {
    std::pair<long, mpf_nombre> suivant(const mpf_nombre &b) {
        mpf_nombre fb = b.floor();
        mpf_nombre bn = fb * (b - fb + 1);
        long an = bn.floor().get_signed_long();
        return std::make_pair(an, bn);
    }

    mpf_nombre tau(const mpf_nombre &theta) {
        std::vector<long> decimal;
        mpf_nombre bn = theta;
        long an = 0;
        while (decimal.size() < 25) {
            std::tie(an, bn) = suivant(bn);
            // std::cout << "an = " << an << ", bn = " << bn << std::endl;
            auto d = chiffres::extraire_chiffres(an);
            // std::cout << d << std::endl;
            decimal.insert(decimal.end(), d.begin(), d.end());
        }

        mpf_nombre tau = theta.floor();
        // std::cout << tau.to_string(25) << std::endl;
        // std::cout << decimal << std::endl;
        mpf_nombre p10 = 1;
        p10 /= 10;
        for (auto d: decimal) {
            tau += p10 * d;
            // std::cout << tau.to_string(25) << std::endl;
            p10 /= 10;
        }

        std::cout << "tau(" << theta.to_string(25) << ") = " << tau.to_string(25) << std::endl;
        return tau;
    }

}

ENREGISTRER_PROBLEME(751, "Concatenation Coincidence") {
    // A non-decreasing sequence of integers $a_n$ can be generated from any positive real value $\theta$ by the
    // following procedure:
    //          b1 = θ
    //          bn = |bn-1|.(bn-1 - |bn-1| + 1)
    //          an = |bn|
    //
    // Where | . | is the floor function.
    //
    // For example, θ = 2.956938891377988... generates the Fibonacci sequence: 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
    //
    // The <i>concatenation</i> of a sequence of positive integers a_n is a real value denoted τ constructed by
    // concatenating the elements of the sequence after the decimal point, starting at a_1: a_1.a_2a_3a_4...
    //
    // For example, the Fibonacci sequence constructed from $\theta=2.956938891377988...$ yields the concatenation
    // tau = 2.3581321345589... Clearly, $\tau \neq \theta$ for this value of $\theta$.</p>
    //
    // Find the only value of $\theta$ for which the generated sequence starts at $a_1=2$ and the concatenation of
    // the generated sequence equals the original value: $\tau = \theta$. Give your answer rounded to 24 places after
    // the decimal point.
    mpf_nombre::setPrecision(512);

    tau(2.956938891377988L);
    tau(mpf_nombre("2.9"));
    tau(mpf_nombre("2.1"));
    tau(mpf_nombre("2.2"));
    tau(mpf_nombre("2.3"));

    mpf_nombre theta("2");
    std::string last_theta = theta.to_string(25);
    while (true) {
        theta = tau(theta);
        std::string suivant = theta.to_string(25);
        if (last_theta == suivant)
            break;
        last_theta = suivant;
    }
    
    return theta.to_string(25);
}
