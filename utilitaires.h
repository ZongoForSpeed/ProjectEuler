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

namespace std
{
    template<typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> & p)
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3>
    std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4>
    std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4, T5> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ")";
        return os;
    }
    
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4, T5, T6> & t)
    {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) 
           << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ", " << std::get<5>(t) << ")";
        return os;
    }
    
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T> & v)
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
    
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::deque<T> & v)
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
    
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::set<T> & s)
    {
        os << "{";
        bool first = true;
        for (const T & n: s)
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
    
    template<typename K, typename V>
    std::ostream& operator<<(std::ostream& os, const std::map<K, V> & s)
    {
        os << "{" << std::endl;
        for (const auto & p: s)
        {
            os << "    " << p.first << " => " << p.second << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
}

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

template <typename T, std::size_t N>
class multidimension: public std::vector<multidimension<T, N-1>>
{
public:
    typedef typename std::vector<multidimension<T, N-1>> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::value_type value_type;
    
    explicit multidimension() {}
    explicit multidimension( size_type count, const value_type& value ) : super_type(count, value) {}
    explicit multidimension( size_type count ) : super_type(count) {}
    
    template<typename... Args>
    multidimension( size_type count, Args... args) : super_type(count, value_type(args...)) {}
    
    multidimension( std::initializer_list<value_type> init ) : super_type(init) {}
};
template <typename T>
class multidimension<T, 1>: public std::vector<T>
{
public:
    typedef typename std::vector<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::value_type value_type;
    
    explicit multidimension() {}
    explicit multidimension( size_type count, const value_type& value ) : super_type(count, value) {}
    explicit multidimension( size_type count ) : super_type(count) {}
    
    multidimension( std::initializer_list<value_type> init ) : super_type(init) {}
};

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

namespace std
{
    template< class Iterator >
    Iterator next( Iterator it, size_t n) 
    {
        advance(it, static_cast<typename std::iterator_traits<Iterator>::difference_type>(n));
        return it;    
    }
}

