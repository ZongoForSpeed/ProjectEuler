#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <set>

typedef unsigned chiffre;

typedef std::pair<std::string, chiffre> paire;
typedef std::vector<paire> ensemble;

typedef std::vector< std::set<char> > solutions; 

bool comparer(const paire & p1, const paire & p2)
{
    if (p1.second != p2.second)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

class Probleme185
{
    ensemble e;
    unsigned taille;
public:
    Probleme185() {}
    
    void lire_fichier(const std::string & fichier)
    {
        std::ifstream infile(fichier.c_str());
        
        std::string pattern, correct, ignore;
        while (infile >> pattern >> correct >> ignore)
        {
            e.push_back(std::make_pair(pattern, correct[1] - '0'));
        }
        
        std::sort(e.begin(), e.end(), comparer);
        
        for (const paire & p: e)
        {
            std::cout << p.first << " : " << p.second << std::endl;
        }
        
        taille = e.front().first.size();
    }
    
    void cherche_solution(unsigned profondeur, solutions s)
    {
        const paire & p = e[profondeur];
        
        if (p.second == 0)
        {
            for (size_t n = 0; n < solutions.size(); ++n)
            {
                s[n].erase(p.first[n]);
            }
            
            cherche_solution(profondeur + 1, s);
        }
        else
        {
            
        }
    }
    
    void algorithme()
    {
        std::set<char> chiffres;
        chiffres.insert('0');
        chiffres.insert('1');
        chiffres.insert('2');
        chiffres.insert('3');
        chiffres.insert('4');
        chiffres.insert('5');
        chiffres.insert('6');
        chiffres.insert('7');
        chiffres.insert('8');
        chiffres.insert('9');
        
        solutions s;
        for (unsigned i = 0; i < taille; ++i)
        {
            s.push_back(chiffres);
        }
        
        
    }
};

int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;
    
    std::string fichier(argv[1]);
    
    Probleme185 p;
    p.lire_fichier(fichier);
    p.algorithme();
    return 0;
}