#include "problemes.h"
#include "numerique.h"
#include "utilitaires.h"
#include "premiers.h"

typedef unsigned long long int nombre;
typedef boost::rational<int128_t> fraction;

namespace {
    fraction probabilite(std::map<std::pair<nombre, std::string>, fraction> &d, nombre i, const std::string &s) {
        auto it = d.find(std::make_pair(i, s));
        if (it != d.end()) {
            return it->second;
        }

        std::string s0 = s.substr(0, 1);
        std::string s1 = s.substr(1);

        fraction q = d[std::make_pair(i, s.substr(0, 1))];
        fraction p;
        if (i == 1) {
            p = q * probabilite(d, i + 1, s1);
        } else if (i == 500) {
            p = q * probabilite(d, i - 1, s1);
        } else {
            p = q * (probabilite(d, i - 1, s1) + probabilite(d, i + 1, s1)) / 2;
        }

        d.emplace(std::make_pair(i, s), p);
        return p;
    }
}

ENREGISTRER_PROBLEME(329, "Prime Frog") {
    // Susan has a prime frog.
    // Her frog is jumping around over 500 squares numbered 1 to 500. He can only jump one square to the left or to the
    // right, with equal probability, and he cannot jump outside the range [1;500]. (if it lands at either end, it
    // automatically jumps to the only available square on the next move.)
    //
    // When he is on a square with a prime number on it, he croaks 'P' (PRIME) with probability 2/3 or 'N' (NOT PRIME)
    // with probability 1/3 just before jumping to the next square.
    // When he is on a square with a number on it that is not a prime he croaks 'P' with probability 1/3 or 'N' with
    // probability 2/3 just before jumping to the next square.
    //
    // Given that the frog's starting position is random with the same probability for every square, and given that she
    // listens to his first 15 croaks, what is the probability that she hears the sequence PPPPNNPPPNPPNPN?
    //
    // Give your answer as a fraction p/q in reduced form.
    const std::string pattern("PPPPNNPPPNPPNPN");
    std::set<nombre> premiers;
    premiers::crible2<nombre>(500, std::inserter(premiers, premiers.begin()));
    // std::cout << premiers << std::endl;

    std::map<std::pair<nombre, std::string>, fraction> d;
    for (nombre i = 1; i < 501; ++i) {
        if (premiers.find(i) != premiers.end()) {
            d.emplace(std::make_pair(i, "P"), fraction(2, 3));
            d.emplace(std::make_pair(i, "N"), fraction(1, 3));
        } else {
            d.emplace(std::make_pair(i, "N"), fraction(2, 3));
            d.emplace(std::make_pair(i, "P"), fraction(1, 3));
        }
    }
    // std::cout << d << std::endl;

    fraction resultat(0, 1);
    for (nombre i = 1; i < 501; ++i) {
        resultat += probabilite(d, i, pattern);
    }

    resultat /= 500;
    return std::to_string(resultat);
}
