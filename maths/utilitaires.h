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
#include <iomanip>

#include <optional>
#include <boost/rational.hpp>

namespace std {
    template<typename T1, typename T2>
    constexpr std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t)
           << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4, T5> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t)
           << ", " << std::get<4>(t) << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4, T5, T6> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t)
           << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ", " << std::get<5>(t) << ")";
        return os;
    }

    template<class T, class Allocator = std::allocator<T> >
    std::ostream &operator<<(std::ostream &os, const std::vector<T, Allocator> &v) {
        os << "[";
        bool first = true;
        for (const T &n: v) {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "]";
        return os;
    }

    template<class T, class Allocator = std::allocator<T> >
    std::ostream &operator<<(std::ostream &os, const std::deque<T, Allocator> &v) {
        os << "[";
        bool first = true;
        for (const T &n: v) {
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
    std::ostream &operator<<(std::ostream &os, const std::set<Key, Compare, Allocator> &s) {
        os << "{";
        bool first = true;
        for (const Key &n: s) {
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
    std::ostream &operator<<(std::ostream &os, const std::map<Key, T, Compare, Allocator> &s) {
        os << "{" << std::endl;
        for (const auto &p: s) {
            os << "    " << p.first << " => " << p.second << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }

    template<class Iterator>
    constexpr Iterator next(Iterator it, size_t n) {
        advance(it, static_cast<typename std::iterator_traits<Iterator>::difference_type>(n));
        return it;
    }

    template<typename T>
    constexpr ostream &operator<<(ostream &os, std::optional<T> s) {
        if (s)
            os << *s;
        else
            os << "<none>";
        return os;
    }

    template<class InputIt1, class InputIt2, class BinaryOperation>
    constexpr void for_each2(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op) {
        while (first1 != last1) {
            binary_op(*first1++, *first2++);
        }
    }

    template<typename Nombre>
    std::string to_string(Nombre n, int p) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(p) << n;
        return oss.str();
    }

    template<typename Nombre>
    std::string to_string(const boost::rational<Nombre> &f) {
        std::ostringstream oss;
        oss << f;
        return oss.str();
    }

    unsigned short popcount(unsigned short S);

    unsigned long popcount(unsigned long S);

    unsigned long long popcount(unsigned long long S);
}

namespace utilitaires {
    template<typename InputIterator>
    inline size_t distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
        //__glibcxx_function_requires(_InputIteratorConcept < InputIterator > )
        size_t result = 0;
        while (first != last) {
            ++first;
            ++result;
        }

        return result;
    }

    template<typename RandomAccessIterator>
    inline size_t distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
        //__glibcxx_function_requires(_RandomAccessIteratorConcept < RandomAccessIterator > )
        return static_cast<size_t>(std::abs(last - first));
    }

    template<typename InputIterator>
    inline size_t distance(InputIterator first, InputIterator last) {
        return distance(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
    }

    template<typename T1, typename T2>
    std::string concatener(const T1 &t1, const T2 &t2) {
        std::ostringstream oss;
        oss << t1 << t2;
        return oss.str();
    }

    template<typename T1, typename T2, typename T3>
    std::string concatener(const T1 &t1, const T2 &t2, const T3 &t3) {
        std::ostringstream oss;
        oss << t1 << t2 << t3;
        return oss.str();
    }

    template<typename T1, typename T2, typename T3, typename T4>
    std::string concatener(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) {
        std::ostringstream oss;
        oss << t1 << t2 << t3 << t4;
        return oss.str();
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b, std::false_type /*is_floating_point*/) {
        return a == b;
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b, std::true_type /*is_floating_point*/) {
        return std::abs(b - a) < std::numeric_limits<Nombre>::epsilon();
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b) {
        return egal(a, b, std::is_floating_point<Nombre>());
    }
}
