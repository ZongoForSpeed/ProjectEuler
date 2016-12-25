#pragma once
#include <boost/optional.hpp>
#include <tuple>

class Pythagoricien;

class IterateurPythagoricien
{
    const Pythagoricien & source;
public:
    IterateurPythagoricien (const Pythagoricien & _source, const size_t _p, const size_t _q);
    
    bool operator!= (const IterateurPythagoricien& it) const;
    std::tuple<size_t, size_t, size_t> operator* () const;
    const IterateurPythagoricien & operator++();
    
    size_t p;
    size_t q;
};

class Pythagoricien
{
    boost::optional<size_t> limite;
public:
    Pythagoricien();
    Pythagoricien(const size_t l);
    
    IterateurPythagoricien begin () const;
    IterateurPythagoricien end () const;
    
    void suivant(IterateurPythagoricien & it) const;
};
