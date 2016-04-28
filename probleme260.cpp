#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "chiffres.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    std::tuple<nombre, nombre, nombre> tri(nombre x, nombre y, nombre z)
    {
        vecteur v { x, y, z };
        std::sort(v.begin(), v.end());
        return std::make_tuple(v[0], v[1], v[2]);
    }
}

ENREGISTRER_PROBLEME(260, "Stone Game")
{
    // A game is played with three piles of stones and two players.
    // At her turn, a player removes one or more stones from the piles. However,
    // if she takes stones from more than one pile, she must remove the same 
    // number of stones from each of the selected piles.
    //
    // In other words, the player chooses some N>0 and removes:
    // 
    //      N stones from any single pile; or
    //      N stones from each of any two piles (2N total); or
    //      N stones from each of the three piles (3N total).
    //
    // The player taking the last stone(s) wins the game.
    // A winning configuration is one where the first player can force a win.
    // For example, (0,0,13), (0,11,11) and (5,5,5) are winning configurations 
    // because the first player can immediately remove all stones.
    // 
    // A losing configuration is one where the second player can force a win, no
    // matter what the first player does.
    // For example, (0,1,2) and (1,3,3) are losing configurations: any legal move
    // leaves a winning configuration for the second player.
    // 
    // Consider all losing configurations (xi,yi,zi) where xi ≤ yi ≤ zi ≤ 100.
    // We can verify that Σ(xi+yi+zi) = 173895 for these.
    //
    // Find Σ(xi+yi+zi) where (xi,yi,zi) ranges over the losing configurations
    // with xi ≤ yi ≤ zi ≤ 1000.
    nombre limite = 1000;
    nombre resultat = 0;
    
    multidimension<bool, 3> victoire(limite + 1, limite + 1, limite + 1, false);
    
    for (nombre x = 0; x < limite + 1; ++x)
    for (nombre y = x; y < limite + 1; ++y)
    for (nombre z = y; z < limite + 1; ++z)
    {
        if (victoire[x][y][z])
            continue;
        
        resultat += x + y + z;
        
        nombre xi = 0;
        nombre yi = 0;
        nombre zi = 0;
        for (nombre i = 1; i < limite - x + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x + i, y, z);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - y + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x, y + i, z);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - z + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x, y, z + i);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - y + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x + i, y + i, z);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - z + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x, y + i, z + i);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - z + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x + i, y, z + i);
            victoire[xi][yi][zi] = true;
        }
        
        for (nombre i = 1; i < limite - z + 1; ++i)
        {
            std::tie(xi, yi, zi) = tri(x + i, y + i, z + i);
            victoire[xi][yi][zi] = true;
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
