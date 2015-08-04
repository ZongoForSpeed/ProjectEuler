#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <ctime>

typedef size_t nombre;
typedef std::set<nombre> ensemble;

struct resultat
{
public:
    nombre frequence;
    ensemble premiers;

    resultat()
    {
        init();
    }

    void init()
    {
        frequence = 0;
        premiers.clear();
    }
};

typedef std::vector<unsigned short> chiffres;
typedef std::vector<resultat> resultats;

class Timer
{
private:
    time_t debut;
    std::string titre;

public:
    Timer(const std::string &t) : titre(t)
    {
        debut = time(NULL);
        std::cout << "Debut " << titre << " ..." << std::endl;
    }

    virtual ~Timer()
    {
        std::cout << "Fin " << titre << " en " << time(NULL) - debut << " secondes " << std::endl;
    }
};



void crible(nombre taille, std::vector<bool>& premiers)
{
    premiers.assign(taille, true);
    premiers.at(0) = false;
    premiers.at(1) = false;

    for (nombre n = 2; n * n < taille; ++n)
    {
        if (premiers.at(n))
        {
            for (nombre k = n * n; k < taille; k+=n)
            {
                premiers.at(k) = false;
            }
        }
    }
}

void analyse(nombre n, chiffres& r)
{
    r.assign(10, 0);
    while(n != 0)
    {
        r.at(n%10)++;
        n /= 10;
    }
}

template<class T>
void affiche( T debut, T fin )
{
    while (debut != fin)
    {
        std::cout << *debut << " ";
        ++debut;
    }
    std::cout << std::endl;
}

template<class T>
nombre somme( T debut, T fin )
{
    nombre s = 0;

    while (debut != fin)
    {
        s += *debut;
        ++debut;
    }
    return s;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << argv[0] << " taille_du_crible" << std::endl;
        return 1;
    }

    nombre taille = atol(argv[1]);

    std::cout << "Taille crible : " << taille << std::endl;

    std::vector<bool> premiers;
    {
        Timer t("crible");
        crible(taille, premiers);
    }

    resultats r(10, resultat());
    {
        Timer t("algorithme");
        for (nombre n = 0; n < taille; ++n)
        {
            if (premiers.at(n))
            {
                chiffres c;
                analyse(n, c);
                // std::cout << n << " : ";
                // affiche(c.begin(), c.end());
                for (unsigned short i = 0; i < 10; ++i)
                {
                    resultat& ri = r.at(i);

                    if (ri.frequence == c.at(i))
                    {
                        ri.premiers.insert(n);
                    }
                    else if (ri.frequence < c.at(i))
                    {
                        ri.init();
                        ri.frequence = c.at(i);
                        ri.premiers.insert(n);
                    }

                }
               
            }
        }
    }

    nombre solution = 0;

    for (unsigned short i = 0; i < 10; ++i)
    {
        resultat& ri = r.at(i);
        nombre s = somme(ri.premiers.begin(), ri.premiers.end());
        solution += s;
        std::cout << i << "\t" << ri.frequence << "\t" << ri.premiers.size() << "\t" << s << std::endl;
    }

    std::cout << std::endl << "*********** SOLUTION **********" << std::endl << solution << std::endl;
   
    // system("PAUSE");
    return 0;
}

