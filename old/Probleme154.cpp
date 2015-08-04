#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <map>

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, paire> dico;

class Problem154
{
  nombre limite;
  dico facteurs;
public:
  Problem154(nombre limite_) : limite(limite_) {}
  ~Problem154() {}
  void algorithme()
  {
    facteurs[0] = std::make_pair(0, 0);
    for (nombre n = 1; n < limite + 1; ++n) facteurs[n] = std::make_pair(compte(n, 2), compte(n, 5));
    
    nombre compteur = 0;
    
    paire facteur = std::make_pair(0, 0);
    for (nombre p = 0; p < limite + 1; ++p)
    {
      if (facteur.second > 11 && facteur.first > 11)
        compteur++;
      // std::cout << "(" << facteur.first << ", " << facteur.second << ")" << '\t';
      paire facteur_p = facteur;
      for (nombre q = 0; p + q < limite; ++q)
      {
        suivant(facteur_p, limite - q - p, q + 1);
        if (facteur_p.second > 11 && facteur_p.first > 11)
          compteur++;
        // std::cout << "(" << facteur_p.first << ", " << facteur_p.second << ")" << '\t';
      }
      // std::cout << std::endl;
      suivant(facteur, limite - p, p + 1);
    }
    
    std::cout << "Compteur : " << compteur << std::endl;
  }
private:
  nombre compte( nombre n, nombre d )
  {
    nombre resultat = 0;
    while (n%d == 0)
    {
      ++resultat;
      n = n/d;
    }
    return resultat;
  }
  
  void suivant(paire & facteur, nombre n, nombre q)
  {
    dico::const_iterator it = facteurs.find(n);
    if (it != facteurs.end())
    {
      facteur.first += it->second.first;
      facteur.second += it->second.second;
    }
    
    it = facteurs.find(q);
    if (it != facteurs.end())
    {
      facteur.first -= it->second.first;
      facteur.second -= it->second.second;
    }
  }
};

int main(int argc, char** argv)
{
  nombre limite = 0;
  if (argc == 2)
  {
    limite = atol(argv[1]);
  }
  else
  {
	  std::cout << "Limite : ";
    std::cin >> limite;
  }
  Problem154 p(limite);
  p.algorithme();
	return 0;
}
