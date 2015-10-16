#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <boost/noncopyable.hpp>

class RegistreProbleme: private boost::noncopyable
{
private:
    RegistreProbleme();
    
public:
    static RegistreProbleme & instance();
    
    void ajout(const size_t numero, const std::string & nom, const std::function<void()> & fonction);
    
    int execute(int argc, char** argv);
    
private:
    std::map<size_t, std::pair<std::string, std::function<void()>>> _registre;
};

struct Probleme
{
    Probleme(const size_t numero, const std::string & nom, const std::function<void()> & fonction);
};

#define ENREGISTRER_PROBLEME(numero, nom) \
void probleme##numero(); \
static Probleme p##numero(numero, nom, probleme##numero); \
void probleme##numero()
