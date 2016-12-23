#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "polynome.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool pixel_noir(nombre x, nombre y, nombre N)
    {
        // (x - 2**N-1)² + (y - 2**N-1)² ≤ 2**(2N-2)
        const nombre centre = puissance::puissance<nombre>(2, static_cast<size_t>(N) - 1);
        bool r = (x - centre)*(x - centre) + (y - centre)*(y - centre) <= centre*centre;
        return r;
    }
    
    nombre algorithme(nombre x1, nombre y1, nombre x2, nombre y2, nombre N)
    {
        nombre test = 8 * pixel_noir(x1, y1, N) 
            + 4 * pixel_noir(x2 - 1, y1, N)
            + 2 * pixel_noir(x2-1, y2-1, N)
            + pixel_noir(x1, y2-1, N);
        
        if (test == 15 || test == 0) return 2;
        
        nombre xm = (x1 + x2)/2;
        nombre ym = (y1 + y2)/2;
        
        return 1 + algorithme(x1, y1, xm, ym, N) 
            + algorithme(xm, y1, x2, ym, N) 
            + algorithme(xm, ym, x2, y2, N) 
            + algorithme(x1, ym, xm, y2, N);
    }
}

ENREGISTRER_PROBLEME(287, "Quadtree encoding (a simple compression algorithm)")
{
    // The quadtree encoding allows us to describe a 2N×2N black and white image 
    // as a sequence of bits (0 and 1). Those sequences are to be read from left
    // to right like this:
    //
    //      - the first bit deals with the complete 2N×2N region;
    //      - "0" denotes a split: 
    //        the current 2n×2n region is divided into 4 sub-regions of dimension
    //        2n-1×2n-1,
    //        the next bits contains the description of the top left, top right,
    //        bottom left and bottom right sub-regions - in that order;
    //      - "10" indicates that the current region contains only black pixels;
    //      - "11" indicates that the current region contains only white pixels.
    //
    // Consider the following 4×4 image (colored marks denote places where a split
    // can occur):
    //                                  ■ ■ ■ □
    //                                  ■ ■ □ ■
    //                                  □ □ ■ ■
    //                                  □ □ ■ ■
    // 
    // This image can be described by several sequences, for example : 
    // "001010101001011111011010101010", of length 30, or "0100101111101110", 
    // of length 16, which is the minimal sequence for this image.
    //
    // For a positive integer N, define DN as the 2N×2N image with the following
    // coloring scheme:
    //
    // the pixel with coordinates x = 0, y = 0 corresponds to the bottom left
    // pixel, if (x - 2**(N-1))² + (y - 2**(N-1))² ≤ 2**(2N-2) then the pixel is black,
    // otherwise the pixel is white.
    // 
    // What is the length of the minimal sequence describing D24 ?
    nombre N = 24;
    nombre p2N = puissance::puissance<nombre, unsigned>(2, 24);
    nombre resultat = 1 
        + algorithme(0, 0, p2N/2, p2N/2, N) 
        + 2*algorithme(p2N/2, 0, p2N, p2N/2, N) 
        + algorithme(p2N/2, p2N/2, p2N, p2N, N);
    return std::to_string(resultat);
}
