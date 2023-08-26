#include "utilitaires.h"
#include "numerique.h"

#include "chiffres.h"

#include <boost/multiprecision/integer.hpp>

namespace {
    unsigned short _base(std::ostream &os) {
        auto basefield = os.flags() & std::ios::basefield;
        if (basefield == std::ios::hex) {
            return 16;
        } else if (basefield == std::ios::oct) {
            return 8;
        }
        return 10;
    }
}

namespace std {
    ostream &operator<<(ostream &os, const uint128_t i) {
        std::ostream::sentry s(os);
        if (s) {
            const auto base = _base(os);
            if ((os.flags() & std::ios::showbase) == std::ios::showbase) {
                switch (base) {
                    case 16:
                        os << "0x";
                        break;
                    case 8:
                        os << '0';
                        break;
                    default:
                        break;
                }
            }
            if (i == 0) {
                os << '0';
                return os;
            }
            const char *bases = "0123456789abcdef";
            for (auto c: chiffres::extraire_chiffres(i, base)) {
                os << bases[c];
            }
        }
        return os;
    }

    ostream &operator<<(ostream &os, const int128_t i) {
        if ((os.flags() & ios::basefield) != ios::dec) {
            throw std::domain_error("base != 10");
        }

        if (i >= 0) {
            os << static_cast<uint128_t>(i);
        } else {
            os << '-' << static_cast<uint128_t>(-i);
        }

        return os;
    }

    istream &operator>>(istream &is, uint128_t &i) {
        if ((is.flags() & ios::basefield) != ios::dec) {
            throw std::domain_error("base != 10");
        }

        string s;
        is >> s;

        if (s.front() == '-') {
            throw std::domain_error("non negatif !");
        }

        i = 0;
        for (char chiffre: s) {
            i = 10 * i + static_cast<uint128_t>(chiffre - '0');
        }

        return is;
    }

    istream &operator>>(istream &is, int128_t &i) {
        if ((is.flags() & ios::basefield) != ios::dec) {
            throw std::domain_error("base != 10");
        }

        string s;
        is >> s;

        bool negatif = (s.front() == '-');

        i = 0;
        for (auto it = negatif ? s.begin() + 1 : s.begin(), en = s.end(); it != en; ++it) {
            i = 10 * i + static_cast<int128_t>(*it - '0');
        }

        if (negatif) {
            i *= -1;
        }

        return is;
    }

    string to_string(int128_t n) {
        ostringstream oss;
        oss << n;
        return oss.str();
    }

    string to_string(uint128_t n) {
        ostringstream oss;
        oss << n;
        return oss.str();
    }

    int128_t sqrt(int128_t n) {
        return boost::multiprecision::sqrt(n);
    }

    uint128_t sqrt(uint128_t n) {
        return boost::multiprecision::sqrt(n);
    }
}
