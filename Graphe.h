#include <vector>
#include <map>
#include <limits>
#include <set>
#include <boost/optional.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

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
    
    void strongconnect(Sommet & v);
public:
    typedef std::map<nombre, vecteur> graphe;
    std::vector<std::set<nombre>> resultat;
    Tarjan(const graphe & g);
    
    void algorithme();
    
private:
    nombre index;
    graphe G;
    std::vector<nombre> S;
    std::map<nombre, Sommet> sommets;
};

class Dijkstra
{
public:
    typedef std::pair<nombre, nombre> paire;
    typedef std::map<nombre, std::vector<paire>> graphe;
    
    vecteur resultat;
    Dijkstra(const graphe & _G, const nombre _debut, const nombre _fin);
    nombre algorithme();
private:
    graphe G;
    nombre debut;
    nombre fin;
};

class Kruskal
{
public:
    typedef std::tuple<nombre, nombre, nombre> arete;
    typedef std::vector<arete> aretes;
    
    Kruskal(const aretes & _A);
    
    aretes algorithme();
private:
    aretes A;
};
