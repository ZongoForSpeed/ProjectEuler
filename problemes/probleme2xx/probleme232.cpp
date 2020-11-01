#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double TheGame(std::map<std::pair<nombre, nombre>, long double> &cache, nombre n, nombre k) {
        if (k <= 0)
            return 1.0L;
        if (k > 0 && n <= 0)
            return 0.0L;

        if (const auto it = cache.find(std::make_pair(n, k));it != cache.end())
            return it->second;

        vecteur strategies{2};
        while (strategies.back() < 2 * k) {
            strategies.push_back(2 * strategies.back());
        }

        long double probabilite = 0.0L;
        for (auto t: strategies) {
            long double p1_reussi = 1.0L / 2;
            long double p2_reussi = 1.0L / t;
            long double p1_rate = 1.0L - p1_reussi;
            long double p2_rate = 1.0L - p2_reussi;

            nombre gain = t / 2;

            probabilite = std::max(probabilite, (p1_reussi * p2_reussi * TheGame(cache, n - 1, k - gain)
                                                 + p1_reussi * p2_rate * TheGame(cache, n - 1, k)
                                                 + p1_rate * p2_reussi * TheGame(cache, n, k - gain)) /
                                                (1 - p1_rate * p2_rate));
        }

        cache[std::make_pair(n, k)] = probabilite;
        return probabilite;
    }
}

ENREGISTRER_PROBLEME(232, "The Race") {
    // Two players share an unbiased coin and take it in turns to play "The Race". On Player 1's turn, he tosses the
    // coin once: if it comes up Heads, he scores one point; if it comes up Tails, he scores nothing. On Player 2's
    // turn, she chooses a positive integer T and tosses the coin T times: if it comes up all Heads, she scores 2T-1
    // points; otherwise, she scores nothing. Player 1 goes first. The winner is the first to 100 or more points.
    //
    // On each turn Player 2 selects the number, T, of coin tosses that maximises the probability of her winning.
    //
    // What is the probability that Player 2 wins?
    //
    // Give your answer rounded to eight decimal places in the form 0.abcdefgh .
    std::map<std::pair<nombre, nombre>, long double> cache;
    long double resultat = 0.5L * TheGame(cache, 100, 100) + 0.5L * TheGame(cache, 99, 100);

    return std::to_string(resultat, 8);
}

