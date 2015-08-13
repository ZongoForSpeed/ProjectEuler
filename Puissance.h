#pragma once

namespace puissance
{
	template<typename N1, typename N2, typename N3>
	N1 puissance_modulaire(N1 base, N2 exposant, N3 modulo)
	{
		N1 resultat = 1;
		while (exposant > 0)
		{
			if (exposant%2)
				resultat = (base * resultat)%modulo;
			exposant /= 2;
			base = (base * base)%modulo;
		}

		return resultat;
	}

	template<typename N1, typename N2>
	N1 puissance(N1 base, N2 modulo)
	{
		N1 resultat = 1;
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
