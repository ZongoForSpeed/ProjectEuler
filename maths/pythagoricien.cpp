#include "pythagoricien.h"
#include "arithmetique.h"

IterateurPythagoricien::IterateurPythagoricien(const Pythagoricien &_source, const size_t _p, const size_t _q)
        : source(_source), p(_p), q(_q) {}

bool IterateurPythagoricien::operator!=(const IterateurPythagoricien &it) const {
    return p != it.p || q != it.q || &source != &(it.source);
}

std::tuple<size_t, size_t, size_t> IterateurPythagoricien::operator*() const {
    auto triplet = std::make_tuple(p * p - q * q, 2 * p * q, p * p + q * q);
    if (std::get<0>(triplet) > std::get<1>(triplet))
        std::swap(std::get<0>(triplet), std::get<1>(triplet));

    return triplet;
}

const IterateurPythagoricien &IterateurPythagoricien::operator++() {
    source.suivant(*this);
    return *this;
}

Pythagoricien::Pythagoricien() : limite(std::nullopt) {}

Pythagoricien::Pythagoricien(const size_t l) : limite(l) {}

IterateurPythagoricien Pythagoricien::begin() const {
    return IterateurPythagoricien(*this, 2, 1);
}

IterateurPythagoricien Pythagoricien::end() const {
    return IterateurPythagoricien(*this, 0, 0);
}

void Pythagoricien::suivant(IterateurPythagoricien &it) const {
    if (limite) {
        const size_t &l = limite.value();
        do {
            it.q += 2;
            if (it.q > it.p || it.p * it.p + it.q * it.q >= l) {
                it.p++;
                it.q = it.p % 2 + 1;
                if (it.p * it.p >= l) {
                    it.p = 0;
                    it.q = 0;
                }
                break;
            }
        } while (arithmetique::PGCD(it.p, it.q) != 1);
    } else {
        do {
            it.q += 2;
            if (it.q > it.p) {
                it.p++;
                it.q = it.p % 2 + 1;
                break;
            }
        } while (arithmetique::PGCD(it.p, it.q) != 1);
    }
}
