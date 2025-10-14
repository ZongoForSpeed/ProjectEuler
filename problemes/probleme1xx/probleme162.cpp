#include "problemes.h"
#include "numerique.h"
#include "utilitaires.h"
#include "puissance.h"

#include <boost/algorithm/string.hpp>

ENREGISTRER_PROBLEME(162, "Hexadecimal numbers") {
    // In the hexadecimal number system numbers are represented using 16 different digits:
    //
    //                           0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
    //
    // The hexadecimal number AF when written in the decimal number system equals 10x16+15=175.
    //
    // In the 3-digit hexadecimal numbers 10A, 1A0, A10, and A01 the digits 0,1 and A are all present.
    // Like numbers written in base ten we write hexadecimal numbers without leading zeroes.
    //
    // How many hexadecimal numbers containing at most sixteen hexadecimal digits exist with all of the digits 0,1, and
    // A present at least once?
    // Give your answer as a hexadecimal number.
    //
    // (A,B,C,D,E and F in upper case, without any leading or trailing code that marks the number as hexadecimal and
    // without leading zeroes , e.g. 1A3F and not: 1a3f and not 0x1a3f and not $1A3F and not #1A3F and not 0000001A3F)
    uint128_t resultat = 0;
    for (size_t n = 3; n < 17; ++n) {
        resultat += 15 * puissance::puissance<uint128_t>(16, n - 1);
        resultat += 41 * puissance::puissance<uint128_t>(14, n - 1);
        resultat -= 43 * puissance::puissance<uint128_t>(15, n - 1);
        resultat -= puissance::puissance<uint128_t>(13, n);
    }

    std::ostringstream oss;
    oss << std::hex << resultat;

    std::string str = oss.str();
    boost::to_upper(str);

    return str;
}
