#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(172)
{
    Timer timer("probleme 172");
    // How many 18-digit numbers n (without leading zeros) are there such that no digit occurs more 
    // than three times in n?
    nombre taille = 18;
    vecteur factorielle {1};
    for (nombre n = 1; n < taille + 1; ++n)
        factorielle.push_back(factorielle.back()*n);

    nombre resultat = 0;
        
    for(nombre i0=0; i0 < 4; ++i0)
    for(nombre i1=0; i1 < 4; ++i1)
    for(nombre i2=0; i2 < 4; ++i2)
    for(nombre i3=0; i3 < 4; ++i3)
    for(nombre i4=0; i4 < 4; ++i4)
    for(nombre i5=0; i5 < 4; ++i5)
    for(nombre i6=0; i6 < 4; ++i6)
    for(nombre i7=0; i7 < 4; ++i7)
    for(nombre i8=0; i8 < 4; ++i8)
    for(nombre i9=0; i9 < 4; ++i9)
	{
        if(i0+i1+i2+i3+i4+i5+i6+i7+i8+i9 == taille)
        {
            resultat += factorielle[taille] 
                / factorielle[i0] 
                / factorielle[i1] 
                / factorielle[i2] 
                / factorielle[i3] 
                / factorielle[i4]
                / factorielle[i5]
                / factorielle[i6]
                / factorielle[i7]
                / factorielle[i8]
                / factorielle[i9];
            if(i0>0)
                resultat -= factorielle[taille - 1] 
                    / factorielle[i0 - 1] 
                    / factorielle[i1] 
                    / factorielle[i2] 
                    / factorielle[i3] 
                    / factorielle[i4]
                    / factorielle[i5]
                    / factorielle[i6]
                    / factorielle[i7]
                    / factorielle[i8]
                    / factorielle[i9];
		}
	}

    std::cout << "Solution: " << resultat << std::endl;
}
