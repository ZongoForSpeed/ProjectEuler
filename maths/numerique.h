#pragma once

#include <type_traits>
#include <limits>

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
    struct is_arithmetic : public std::__or_<is_integral<T>, is_floating_point<T>>::type {
    };


}

/*
namespace std {
    template<>
    struct is_integral<int128_t> : public true_type {
    };

    template<>
    struct is_integral<uint128_t> : public true_type {
    };

    // template<>
    // class numeric_limits<uint128_t> : public numeric_limits<uint64_t> {
    // public:
    //     static constexpr int digits = 128;
    //     static constexpr int digits10 = 38;
    //     static constexpr bool is_specialized = true;
//
    //     static constexpr uint128_t max() {
    //         return min() - 1;
    //     }
//
    //     static constexpr uint128_t min() {
    //         return 0;
    //     }
//
    //     static constexpr uint128_t lowest() {
    //         return 0;
    //     }
    // };
//
    // template<>
    // class numeric_limits<int128_t> : public numeric_limits<int64_t> {
    // public:
    //     static constexpr int digits = 127;
    //     static constexpr int digits10 = 38;
    //     static constexpr bool is_specialized = true;
//
    //     static constexpr int128_t max() {
    //         return numeric_limits<uint128_t>::max() >> 1;
    //     }
//
    //     static constexpr int128_t min() {
    //         return -max() - 1;
    //     }
//
    //     static constexpr int128_t lowest() {
    //         return min();
    //     }
    // };
}
*/
