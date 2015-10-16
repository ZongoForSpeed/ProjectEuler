#include "Problemes.h"
#include "Utilitaires.h"

#include <vector>

RegistreProbleme::RegistreProbleme() 
{
    
}

RegistreProbleme & RegistreProbleme::instance()
{
    static RegistreProbleme _instance_;
    return _instance_;
}

void RegistreProbleme::ajout(const size_t numero, const std::function<void()> & fonction)
{
    _registre.insert(std::make_pair(numero, fonction));
}

int RegistreProbleme::execute(int argc, char** argv)
{
    std::vector<std::string> arguments(argv + 1, argv+argc);
    std::cout << arguments << std::endl;
    for (auto p: arguments)
    {
        size_t n = stoull(p);
        auto it = _registre.find(n);
        if (it != _registre.end())
            it->second();
        else
            std::cout << "Le probleme " << n << " n'existe pas !" << std::endl;
    }
    return 0;
}

Probleme::Probleme(const size_t numero, const std::function<void()> & fonction)
{
    RegistreProbleme::instance().ajout(numero, fonction);
}
