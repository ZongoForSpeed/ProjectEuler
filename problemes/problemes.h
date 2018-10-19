#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <boost/noncopyable.hpp>

class RegistreProbleme : private boost::noncopyable {
private:
    RegistreProbleme();

public:
    static RegistreProbleme &instance();

    void ajout(size_t numero, const std::string &nom, const std::function<std::string()> &fonction);

    int execute(int argc, char **argv);

    void executeProbleme(std::map<size_t, std::string>& solutions, size_t numero, const std::string &nom, const std::function<std::string()> &fonction);

private:
    std::map<size_t, std::pair<std::string, std::function<std::string()>>> _registre;
};

struct Probleme {
    Probleme(size_t numero, const std::string &nom, const std::function<std::string()> &fonction);
};

#define ENREGISTRER_PROBLEME(numero, nom) \
std::string probleme##numero(); \
static Probleme p##numero(numero, nom, probleme##numero); \
std::string probleme##numero()
