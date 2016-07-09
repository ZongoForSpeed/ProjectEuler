#include "problemes.h"
#include "timer.h"
#include "utilitaires.h"

#include <vector>
#include <boost/algorithm/string.hpp>
#include <gperftools/profiler.h>

RegistreProbleme::RegistreProbleme() 
{
    
}

RegistreProbleme & RegistreProbleme::instance()
{
    static RegistreProbleme _instance_;
    return _instance_;
}

void RegistreProbleme::ajout(const size_t numero, const std::string & nom, const std::function<void()> & fonction)
{
    _registre.insert(std::make_pair(numero, std::make_pair(nom, fonction)));
}

int RegistreProbleme::execute(int argc, char** argv)
{
    const std::string profile = std::getenv("CPUPROFILE");
    if (!profile.empty())
        ProfilerStart("Euler.log");
    std::vector<std::string> arguments(argv + 1, argv+argc);
    std::vector<size_t> problemes;
    for (auto p: arguments)
    {
        std::vector<std::string> s;
        boost::split(s, p, boost::is_any_of(":-"));
        if (s.size() == 1)
        {
            problemes.push_back(stoull(p));
        }
        else if (s.size() > 1)
        {
            const size_t debut = stoull(s[0]);
            const size_t fin = stoull(s[1]);
            for (size_t i = debut; i < fin + 1; ++i)
            {
                problemes.push_back(i);
            }
        }
        
    }
    
    for (auto n: problemes)
    {
        auto it = _registre.find(n);
        if (it != _registre.end())
        {
            std::ostringstream oss;
            oss << "probleme " << it->first << ": " << it->second.first;
            Timer t(oss.str());
            it->second.second();            
        }
        else
            std::cout << "Le probleme " << n << " n'existe pas !" << std::endl;
    }
    if (!profile.empty())
        ProfilerStop();
    return 0;
}

Probleme::Probleme(const size_t numero, const std::string & nom, const std::function<void()> & fonction)
{
    RegistreProbleme::instance().ajout(numero, nom, fonction);
}
