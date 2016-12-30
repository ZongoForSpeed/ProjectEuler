#include "problemes.h"
#include "timer.h"
#include "utilitaires.h"

#include <boost/algorithm/string.hpp>
#include <fstream>

namespace
{
    const std::string getEnvironnement(const std::string & variable)
    {
        std::string resultat;
        if (const char * env = std::getenv(variable.c_str()))
            resultat.assign(env);
        
        return resultat;
    }
}

RegistreProbleme::RegistreProbleme() 
{
    
}

RegistreProbleme & RegistreProbleme::instance()
{
    static RegistreProbleme _instance_;
    return _instance_;
}

void RegistreProbleme::ajout(const size_t numero, const std::string & nom, const std::function<std::string()> & fonction)
{
    _registre.insert(std::make_pair(numero, std::make_pair(nom, fonction)));
}

int RegistreProbleme::execute(int argc, char** argv)
{
    std::map<size_t /*numero*/, std::string/*solution*/> solutions;
    {
        std::ifstream ifs("data/solutions.txt");
        if (ifs)
        {
            size_t numero;
            std::string solution;
            
            while (ifs >> numero >> solution)
            {
                solutions[numero] = solution;
            }
        }          
    }
  
    std::vector<std::string> arguments(argv + 1, argv+argc);
    if (arguments.empty())
    {
        std::string argument;
        std::cout << "Argument : ";
        std::cin >> argument;
        arguments.push_back(argument);
    }
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
        std::cout << std::endl;
        auto it = _registre.find(n);
        if (it != _registre.end())
        {
            const std::string & solution = solutions[it->first];
            std::ostringstream oss;
            oss << "probleme " << it->first << ": " << it->second.first;
            Timer t(oss.str());
            const std::string resultat = it->second.second();
            if (resultat == solution)
            {
                std::cout << "\033[1;32m" << "Solution : " << resultat << "\033[0m" << std::endl;
            }
            else
            {
                std::cout << "\033[1;31m" << "ERREUR !" << std::endl;
                std::cout << "Resultat : " << resultat << std::endl;
                std::cout << "Solution : " << solution << std::endl;
                std::cout << "\033[0m";
            }
        }
        else
            std::cout << "Le probleme " << n << " n'existe pas !" << std::endl;
    }

    return 0;
}

Probleme::Probleme(const size_t numero, const std::string & nom, const std::function<std::string()> & fonction)
{
    RegistreProbleme::instance().ajout(numero, nom, fonction);
}
