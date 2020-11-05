#pragma once

#include <optional>
#include <tuple>

class Pythagoricien;

class IterateurPythagoricien {
    const Pythagoricien &source;
public:
    IterateurPythagoricien(const Pythagoricien &_source, size_t _p, size_t _q);

    bool operator!=(const IterateurPythagoricien &it) const;

    std::tuple<size_t, size_t, size_t> operator*() const;

    const IterateurPythagoricien &operator++();

    size_t p;
    size_t q;
};

class Pythagoricien {
    std::optional<size_t> limite;
public:
    Pythagoricien();

    explicit Pythagoricien(size_t l);

    [[nodiscard]] IterateurPythagoricien begin() const;

    [[nodiscard]] IterateurPythagoricien end() const;

    void suivant(IterateurPythagoricien &it) const;
};
