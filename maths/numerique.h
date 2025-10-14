#pragma once

#include <type_traits>

typedef __int128_t int128_t;
typedef __uint128_t uint128_t;

class mpz_nombre;

class mpf_nombre;

namespace numeric {
    template<typename T>
    struct is_integral : public std::is_integral<T> {
    };

    template<>
    struct is_integral<int128_t> : public std::true_type {
    };

    template<>
    struct is_integral<uint128_t> : public std::true_type {
    };

    template<>
    struct is_integral<mpz_nombre> : public std::true_type {
    };

    template<typename T>
    struct is_floating_point : public std::is_floating_point<T> {
    };

    template<>
    struct is_floating_point<mpf_nombre> : public std::true_type {
    };

    template<typename T>
    struct is_arithmetic : public std::__or_<is_integral<T>, is_floating_point<T> >::type {
    };
}
