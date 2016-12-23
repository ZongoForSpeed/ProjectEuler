#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <iterator>
#include <tuple>
#include <cmath>

#include "puissance.h"
#include "chiffres.h"

#include <boost/optional.hpp>
#include <boost/multiprecision/gmp.hpp>

namespace std
{
    long double sqrt(boost::multiprecision::mpz_int n);
    
    template<typename T1, typename T2>
    constexpr std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> & p)
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3>
    constexpr std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4>
    constexpr std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    constexpr std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4, T5> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    constexpr std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4, T5, T6> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) 
           << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ", " << std::get<5>(t) << ")";
        return os;
    }
    
    template< class T, class Allocator = std::allocator<T> >
    std::ostream& operator<<(std::ostream& os, const std::vector<T, Allocator> & v)
    {
        os << "[";
        bool first = true;
        for (const T & n: v)
        {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "]";
        return os;
    }
    
    template< class T, class Allocator = std::allocator<T> >
    std::ostream& operator<<(std::ostream& os, const std::deque<T, Allocator> & v)
    {
        os << "[";
        bool first = true;
        for (const T & n: v)
        {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "]";
        return os;
    }
    
    template<
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    >
    std::ostream& operator<<(std::ostream& os, const std::set<Key, Compare, Allocator> & s)
    {
        os << "{";
        bool first = true;
        for (const Key & n: s)
        {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "}";
        return os;
    }
    
    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T> >
    >
    std::ostream& operator<<(std::ostream& os, const std::map<Key, T, Compare, Allocator> & s)
    {
        os << "{" << std::endl;
        for (const auto & p: s)
        {
            os << "    " << p.first << " => " << p.second << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
    
    template< class Iterator >
    constexpr Iterator next( Iterator it, size_t n) 
    {
        advance(it, static_cast<typename std::iterator_traits<Iterator>::difference_type>(n));
        return it;    
    }
    
    template<typename T>
    constexpr ostream & operator<<(ostream & os, boost::optional<T> s)
    {
        if (s)
            os << *s;
        else
            os << "<none>";
        return os;
    }
    
    template<class InputIt1, class InputIt2, class BinaryOperation>
    constexpr void for_each2(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)
    {
        while (first1 != last1) {
            binary_op(*first1++, *first2++);
        }
    }
    
    std::string to_string(const boost::multiprecision::mpz_int & n);
    
    template<typename Nombre>
    std::string to_string(Nombre n, int p)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(p) << n;
        return oss.str();
    }
}

template<typename Nombre>
constexpr Nombre racine_carre(Nombre n)
{
    return static_cast<Nombre>(std::sqrt(n));
}

boost::multiprecision::mpz_int racine_carre(boost::multiprecision::mpz_int n);

template<typename Nombre, typename = typename std::enable_if<std::is_integral<Nombre>::value, Nombre>::type>
constexpr Nombre racine_cubique(Nombre n)
{
	return static_cast<Nombre>(std::cbrt(n));
}

template<typename Nombre>
boost::optional<Nombre> carre_parfait(Nombre x)
{
    Nombre s = racine_carre<Nombre>(x);
    if (s * s == x)
        return s;
    else
        return boost::none;
}

template<typename Nombre> 
constexpr typename std::enable_if<std::is_integral<Nombre>::value, bool>::type egal(const Nombre & a, const Nombre & b)
{ 
    return a == b;
}

template<typename Nombre> 
constexpr typename std::enable_if<std::is_class<Nombre>::value, bool>::type egal(const Nombre & a, const Nombre & b)
{ 
    return a == b;
}

template<typename Nombre>
constexpr typename std::enable_if<std::is_floating_point<Nombre>::value, bool>::type egal(const Nombre & a, const Nombre & b)
{ 
    return std::abs(b - a) < std::numeric_limits<Nombre>::epsilon();
}

long double operator+(const boost::multiprecision::mpz_int & n, const long double d);
long double operator+(const long double d, const boost::multiprecision::mpz_int & n);

long double operator-(const boost::multiprecision::mpz_int & n, const long double d);
long double operator-(const long double d, const boost::multiprecision::mpz_int & n);

long double operator/(const boost::multiprecision::mpz_int & n, const long double d);
long double operator/(const long double d, const boost::multiprecision::mpz_int & n);

long double operator*(const boost::multiprecision::mpz_int & n, const long double d);
long double operator*(const long double d, const boost::multiprecision::mpz_int & n);

template<typename T1, typename T2>
std::string concatener(const T1 & t1, const T2 & t2)
{
    std::ostringstream oss;
    oss << t1 << t2;
    return oss.str();
}

template<typename T1, typename T2, typename T3>
std::string concatener(const T1 & t1, const T2 & t2, const T3 & t3)
{
    std::ostringstream oss;
    oss << t1 << t2 << t3;
    return oss.str();
}

template<typename T1, typename T2, typename T3, typename T4>
std::string concatener(const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4)
{
    std::ostringstream oss;
    oss << t1 << t2 << t3 << t4;
    return oss.str();
}

namespace utilitaires
{
    template<typename InputIterator>
    inline size_t distance(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        __glibcxx_function_requires(_InputIteratorConcept<InputIterator>)
        
        size_t result = 0;
        while (first != last)
        {
            ++first;
            ++result;
        }
        
        return result;
    }

    template<typename RandomAccessIterator>
    inline size_t distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
    {
        __glibcxx_function_requires(_RandomAccessIteratorConcept<RandomAccessIterator>)
        return static_cast<size_t>(std::abs(last - first));     
    }

    template<typename InputIterator>
    inline size_t distance(InputIterator first, InputIterator last)
    {
        return distance(first, last, std::__iterator_category(first));
    }
}
