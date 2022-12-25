#include "random.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"

namespace utilitaires {
    std::mt19937 &generator() {
        static std::random_device rd;   // Will be used to obtain a seed for the random number engine
        static std::mt19937 mt(rd());   // Standard mersenne_twister_engine seeded with rd()
        return mt;
    }
}

#pragma clang diagnostic pop
