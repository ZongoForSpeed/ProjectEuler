#include "utilitaires.h"

namespace std {
#ifdef __GNUG__
    unsigned short popcount(unsigned short S) {
        return static_cast<unsigned short>(__builtin_popcount(S));
    }

    unsigned long popcount(unsigned long S) {
        return static_cast<unsigned long>(__builtin_popcountl(S));
    }

    unsigned long long popcount(unsigned long long S) {
        return static_cast<unsigned long long>(__builtin_popcountll(S));
    }

#endif

#ifdef _MSC_VER
    unsigned popcount(unsigned S) {
        return __popcnt16(S);
    }

    unsigned long popcount(unsigned long S) {
        return __popcnt(S);
    }

    unsigned long long popcount(unsigned long long S) {
        return __popcnt64(S);
    }
#endif
}
