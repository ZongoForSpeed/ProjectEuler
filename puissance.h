#pragma once

namespace puissance
{
    template<typename Nombre1, typename Nombre2>
    Nombre1 puissance_modulaire(Nombre1 base, size_t exposant, Nombre2 modulo)
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
    template<typename Nombre>
    Nombre puissance(Nombre base, size_t exposant)
    {
        Nombre resultat = 1;
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
