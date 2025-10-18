#include "problemes.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(692, "Siegbert and Jo") {
    // Siegbert and Jo take turns playing a game with a heap of N pebbles:
    //
    // 1. Siegbert is the first to take some pebbles. He can take as many pebbles as he wants. (Between 1 and N
    // inclusive.)
    //
    // 2. In each of the following turns the current player must take at least one pebble and at most twice the amount
    // of pebbles taken by the previous player.
    //
    // 3. The player who takes the last pebble wins.
    //
    // Although Siegbert can always win by taking all the pebbles on his first turn, to make the game more interesting
    // he chooses to take the smallest number of pebbles that guarantees he will still win (assuming both Siegbert and
    // Jo play optimally for the rest of the game).
    //
    // Let H(N) be that minimal amount for a heap of N pebbles.
    // H(1) = 1, H(4) = 1, H(17) = 1, H(8) = 8 and  H(18) = 5.
    //
    // Let G(n) be Sum_k=1..n H(k).
    // G(13) = 43.
    //
    // Find G(23416728348467685).
    std::vector<mpz_nombre> F{1, 1};
    std::vector<mpz_nombre> G{1, 1};

    for (size_t i = 2; i < 80; ++i) {
        F.emplace_back(F[i - 1] + F[i - 2]);
        G.emplace_back(G[i - 1] + G[i - 2] + F[i - 1]);
    }

    std::cout << "F(" << 80 << ") = " << F.back() << std::endl;
    std::cout << "G(" << F.back() << ") = " << G.back() << std::endl;

    return G.back().to_string();
}
