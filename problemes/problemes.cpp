#include "problemes.h"
#include "timer.h"
#include "utilitaires.h"

#include <boost/algorithm/string.hpp>
#include <fstream>

RegistreProbleme::RegistreProbleme() = default;

RegistreProbleme &RegistreProbleme::instance() {
    static RegistreProbleme _instance_;
    return _instance_;
}

void
RegistreProbleme::ajout(const size_t numero, const std::string &nom, const std::function<std::string()> &fonction) {
    _registre.emplace(numero, std::make_pair(nom, fonction));
}

void
RegistreProbleme::executeProbleme(std::map<size_t, std::string> &solutions, size_t numero, const std::string &nom,
                                  const std::function<std::string()> &fonction) {
    const std::string &solution = solutions[numero];
    std::ostringstream oss;
    oss << "probleme " << numero << ": " << nom;
    Timer t(oss.str());
    const std::string resultat = fonction();
#ifndef WIN32
    if (resultat == solution) {
        std::cout << "\033[1;32m" << "Solution : " << resultat << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[1;31m" << "ERREUR !" << std::endl;
        std::cout << "Resultat : " << resultat << std::endl;
        std::cout << "Solution : " << solution << std::endl;
        std::cout << "\033[0m";
    }
#else
    if (resultat == solution)
            {
                std::cout << "Solution : " << resultat << std::endl;
            }
            else
            {
                std::cout << "ERREUR !" << std::endl;
                std::cout << "Resultat : " << resultat << std::endl;
                std::cout << "Solution : " << solution << std::endl;
            }
#endif
    if (t.timestamp() > 60.0) {
        std::cout << "\033[1;31m" << "ERREUR RESOLUTION TROP LONGUE !" << "\033[0m" << std::endl;
    }
}

int RegistreProbleme::execute(int argc, char **argv) {
    std::map<size_t /*numero*/, std::string/*solution*/> solutions;
    {
        std::ifstream ifs("data/solutions.txt");
        if (ifs) {
            size_t numero;
            std::string solution;

            while (ifs >> numero >> solution) {
                solutions[numero] = solution;
            }
        }
    }

    std::vector<std::string> arguments(argv + 1, argv + argc);
    if (arguments.empty()) {
        std::cout << "Argument : ";
        std::string argument;
        std::cin >> argument;
        if (argument == "all") {
            for (const auto &p: _registre) {
                executeProbleme(solutions, p.first, p.second.first, p.second.second);
            }
            return 0;
        }

        std::vector<std::string> s;
        boost::split(s, argument, boost::is_any_of(","));
        arguments.insert(arguments.end(), s.begin(), s.end());
        // arguments.push_back(argument);
    }

    std::vector<size_t> problemes;
    for (auto p: arguments) {
        std::vector<std::string> s;
        boost::split(s, p, boost::is_any_of(":-"));
        if (s.size() == 1) {
            problemes.push_back(std::stoull(p));
        } else if (s.size() > 1) {
            const size_t debut = std::stoull(s[0]);
            const size_t fin = std::stoull(s[1]);
            for (size_t i = debut; i < fin + 1; ++i) {
                problemes.push_back(i);
            }
        }
    }

    for (auto n: problemes) {
        std::cout << std::endl;
        auto it = _registre.find(n);
        if (it != _registre.end()) {
            executeProbleme(solutions, n, it->second.first, it->second.second);
        } else
            std::cout << "Le probleme " << n << " n'existe pas !" << std::endl;
    }

    return 0;
}

Probleme::Probleme(const size_t numero, const std::string &nom, const std::function<std::string()> &fonction) {
    RegistreProbleme::instance().ajout(numero, nom, fonction);
}
