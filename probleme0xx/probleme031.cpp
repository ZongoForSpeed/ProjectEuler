#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(31, "Coin sums")
{
    // In England the currency is made up of pound, £, and pence, p, and there are eight 
    // coins in general circulation:
    //
    // 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
    // It is possible to make £2 in the following way:
    // 
    // 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
    // How many different ways can £2 be made using any number of coins?
    nombre resultat = 0;
    for (nombre p200 = 0; p200 <= 200; p200 += 200)
    for (nombre p100 = 0; p100 <= 200 - p200; p100 += 100)
    for (nombre p50 = 0; p50 <= 200 - p200 - p100; p50 += 50)
    for (nombre p20 = 0; p20 <= 200 - p200 - p100 - p50; p20 += 20)
    for (nombre p10 = 0; p10 <= 200 - p200 - p100 - p50 - p20; p10 += 10)
    for (nombre p5 = 0; p5 <= 200 - p200 - p100 - p50 - p20 - p10; p5 += 5)
    for (nombre p2 = 0; p2 <= 200 - p200 - p100 - p50 - p20 - p10 - p5; p2 += 2)
        ++resultat;
        
    std::cout << "Solution: " << resultat << std::endl;
}
