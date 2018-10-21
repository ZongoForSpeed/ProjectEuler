#pragma once

#include <vector>
#include <initializer_list>
#include <boost/functional/hash.hpp>

template<typename T, std::size_t N>
class multidimension : public std::vector<multidimension<T, N - 1>> {
public:
    typedef typename std::vector<multidimension<T, N - 1>> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::value_type value_type;

    explicit multidimension() = default;

    explicit multidimension(size_type count, const value_type &value) : super_type(count, value) {}

    explicit multidimension(size_type count) : super_type(count) {}

    template<typename... Args>
    multidimension(size_type count, Args... args) : super_type(count, value_type(args...)) {}

    multidimension(std::initializer_list<value_type> init) : super_type(init) {}
};

template<typename T>
class multidimension<T, 1> : public std::vector<T> {
public:
    typedef typename std::vector<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::value_type value_type;

    explicit multidimension() = default;

    explicit multidimension(size_type count, const value_type &value) : super_type(count, value) {}

    explicit multidimension(size_type count) : super_type(count) {}

    multidimension(std::initializer_list<value_type> init) : super_type(init) {}
};

namespace std {
    template<typename T, std::size_t N>
    struct hash<multidimension<T, N>> {
        std::size_t operator()(const multidimension<T, N> &k) const {
            return boost::hash_range(k.begin(), k.end());
        }
    };
}
