#pragma once

namespace puissance
{
	template<typename N>
	N puissance_modulaire(N base, N exposant, N modulo)
	{
		N resultat = 1;
		while (exposant > 0)
		{
			if (exposant%2)
				resultat = (base * resultat)%modulo;
			exposant /= 2;
			base = (base * base)%modulo;
		}

		return resultat;
	}

	template<typename N>
	N puissance(N base, N modulo)
	{
		N resultat = 1;
		while (modulo > 0)
		{
			if (modulo%2)
				resultat *= base;
			modulo /= 2;
			base *= base;
		}

		return resultat;
	}
}
