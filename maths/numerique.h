#pragma once

#include <type_traits>
#include <limits>

typedef __int128_t int128_t;
typedef __uint128_t uint128_t;

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
