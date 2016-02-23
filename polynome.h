#pragma once

#include <vector>
#include <initializer_list>

#include <boost/range/adaptor/reversed.hpp>

template<typename Nombre>
class Polynome
{
	std::vector<Nombre> _polynome;
	
public: 
	Polynome() {}
	Polynome(Nombre n) : _polynome(1, n) {}
	Polynome(std::initializer_list<Nombre> polynome) : _polynome(polynome) {}
	
	size_t taille() const { return _polynome.size(); }
	Nombre valeur(Nombre x) const 
	{
		Nombre resultat = 0;
		Nombre px = 1;
		for (const auto & p: _polynome)
		{
			resultat += px * p;
			px *= x;
		}
		
		return resultat;
	}
	
	Polynome& operator*=(const Polynome& p) 
	{
		if (_polynome.size() == 0 || p._polynome.size() == 0)
		{
			_polynome.clear();
			return *this;
		}
		
		std::vector<Nombre> polynome ( _polynome.size() + p._polynome.size() - 1, 0);
		for (size_t i = 0; i < _polynome.size(); ++i)
		for (size_t j = 0; j < p._polynome.size(); ++j)
			polynome[i+j] += _polynome[i] * p._polynome[j];
			
		_polynome.swap(polynome);
		reduire();
		return *this;
    }
    
    Polynome& operator+=(const Polynome& p) 
	{
		if (p._polynome.size() > _polynome.size() )
			_polynome.resize(p._polynome.size());
		for (size_t i = 0; i < p._polynome.size(); ++i)
			_polynome[i] += p._polynome[i];
			
		reduire();
		return *this;
    }
    
    Polynome& operator-=(const Polynome& p) 
	{
		if (p._polynome.size() > _polynome.size() )
			_polynome.resize(p._polynome.size());
		for (size_t i = 0; i < p._polynome.size(); ++i)
			_polynome[i] -= p._polynome[i];
			
		reduire();
		return *this;
    } 
    
    bool operator==(const Polynome& p) const 
    {
        const size_t taille_ = taille();
        const size_t taille_p = p.taille();
        if (taille_ != taille_p)
            return false;
        for (size_t n = 0; n < taille_; ++n)
        {
            if (_polynome[n] != p._polynome[n])
                return false;
        }
        
        return true;
    }
    
    void reduire()
    {
    	size_t taille = _polynome.size();
    	while (_polynome[taille -1] == 0)
    		--taille;
    		
    	if (taille < _polynome.size())
    		_polynome.resize(taille);
    }
    
    void affiche(std::ostream& os) const
    {
        size_t degre = taille();
        bool first = true;
        for (const Nombre & c: boost::adaptors::reverse(_polynome))
        {
            --degre;
            if (c != 0)
            {
                bool signe = (c > 0);
                if (!first)
                    os << (signe ? " + " : " - ");
                else if (!signe)
                    os << "-";
                if ((c != 1 && c != -1) || degre == 0)
                    os << (signe ? c : -c);
                switch(degre)
                {
                    case 0:
                        break;
                    case 1:
                        os << "X";
                        break;
                    default:
                        os << "X^" << degre;
                        break;
                }
                
                first = false;
            }
        }
    }
    
    static void division_euclidienne(const Polynome & A, const Polynome & B, Polynome & quotient, Polynome & reste)
    {
        const size_t taille_a = A.taille();
        const size_t taille_b = B.taille();
        
        if (taille_a < taille_b)
        {
            quotient = { 0 };
            reste = A;
        }
        else
        {
            quotient._polynome.assign(taille_a - taille_b + 1, 0);
            quotient._polynome.back() = A._polynome.back() / B._polynome.back();
            reste = A - B * quotient;
            reste.reduire();
            
            if (reste.taille() >= taille_b)
            {
                Polynome quotient1;
                Polynome reste1;
                division_euclidienne(reste, B, quotient1, reste1);
                reste = reste1;
                quotient += quotient1;
            }
        }
    }
};

template<typename Nombre>
Polynome<Nombre> operator*(Polynome<Nombre> lhs, const Polynome<Nombre>& rhs)
{
    return lhs *= rhs;
}

template<typename Nombre>
Polynome<Nombre> operator+(Polynome<Nombre> lhs, const Polynome<Nombre>& rhs)
{
    return lhs += rhs;
}

template<typename Nombre>
Polynome<Nombre> operator-(Polynome<Nombre> lhs, const Polynome<Nombre>& rhs)
{
    return lhs -= rhs;
}

template<typename Nombre>
std::ostream& operator<<(std::ostream& os, const Polynome<Nombre>& p)
{
	p.affiche (os);
    return os;
}
