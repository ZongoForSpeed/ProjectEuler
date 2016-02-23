#pragma once

namespace puissance
{
    template<typename Nombre1, typename Nombre2, typename Nombre3>
    Nombre1 puissance_modulaire(Nombre1 base, Nombre2 exposant, Nombre3 modulo)
    {
        Nombre1 resultat = 1;
        while (exposant > 0)
        {
            if (exposant%2)
                resultat = (base * resultat)%modulo;
            exposant /= 2;
            base = (base * base)%modulo;
        }
        return resultat;
    }
    template<typename Nombre1, typename Nombre2>
    Nombre1 puissance(Nombre1 base, Nombre2 exposant)
    {
        Nombre1 resultat = 1;
        while (exposant > 0)
        {
            if (exposant%2)
                resultat *= base;
            exposant /= 2;
            base *= base;
        }
        return resultat;
    }
}
