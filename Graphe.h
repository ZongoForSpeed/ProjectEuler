#include <vector>
#include <map>
#include <limits>
#include <set>

#include <boost/optional.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::map<nombre, vecteur> graphe;

class Tarjan
{
    struct Sommet
    {
        nombre n;
        boost::optional<nombre> index;
        nombre lowlink;
        bool onStack;
        
        Sommet(nombre _n) : n(_n), lowlink(std::numeric_limits<nombre>::max()), onStack(false) {}
    };
    
    nombre index;
    
    std::vector<nombre> S;
    graphe G;
    
    std::map<nombre, Sommet> sommets;
    
    void strongconnect(Sommet & v);
public:
    std::vector<std::set<nombre>> resultat;

    Tarjan(const graphe & g);
    
    void algorithme();
};
