#pragma once

#include <type_traits>
#include <iostream>

typedef __int128_t int128_t;
typedef __uint128_t uint128_t;

namespace std {
    template<>
    struct is_integral<int128_t> : public true_type {
    };

    template<>
    struct is_integral<uint128_t> : public true_type {
    };

    template<>
    class numeric_limits<uint128_t> : public numeric_limits<uint64_t> {
    public:
        static constexpr int digits = 128;
        static constexpr int digits10 = 38;

        static constexpr uint128_t max() {
            return min() - 1;
        }

        static constexpr uint128_t min() {
            return 0;
        }

        static constexpr uint128_t lowest() {
            return 0;
        }
    };

    template<>
    class numeric_limits<int128_t> : public numeric_limits<int64_t> {
    public:
        static constexpr int digits = 127;
        static constexpr int digits10 = 38;

        static constexpr int128_t max() {
            return numeric_limits<uint128_t>::max() >> 1;
        }

        static constexpr int128_t min() {
            return -max() - 1;
        }

        static constexpr int128_t lowest() {
            return min();
        }
    };

    ostream &operator<<(ostream &os, uint128_t i);

    ostream &operator<<(ostream &os, int128_t i);

    istream &operator>>(istream &is, uint128_t &i);

    istream &operator>>(istream &is, int128_t &i);

    string to_string(int128_t n);

    string to_string(uint128_t n);

    int128_t sqrt(int128_t n);

    uint128_t sqrt(uint128_t n);
}
