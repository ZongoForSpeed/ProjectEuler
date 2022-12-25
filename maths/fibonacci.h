#pragma once

#include <optional>
#include <tuple>

template<typename T>
class IterateurFibonacci;

template<typename T>
class Fibonacci {
    std::optional<std::pair<T, T>> start;
    std::optional<T> limite;
public:
    Fibonacci() : start(std::nullopt), limite(std::nullopt) {}

    explicit Fibonacci(T l) : start(std::nullopt), limite(l) {}

    explicit Fibonacci(T f1, T f2, T l) : start(std::make_pair(f1, f2)), limite(l) {}

    [[nodiscard]] IterateurFibonacci<T> begin() const;

    [[nodiscard]] IterateurFibonacci<T> end() const;

    void suivant(IterateurFibonacci<T> &it) const;
};

template<typename T>
class IterateurFibonacci {
    const Fibonacci<T> &source;
public:
    IterateurFibonacci(const Fibonacci<T> &_source, T _p, T _q) : source(_source), p(_p),
                                                                  q(_q) {}

    bool operator!=(const IterateurFibonacci<T> &it) const {
        return p != it.p || q != it.q || &source != &(it.source);
    }

    T operator*() const {
        return q;
    }

    const IterateurFibonacci<T> &operator++() {
        source.suivant(*this);
        return *this;
    }

    T p;
    T q;
};

template<typename T>
IterateurFibonacci<T> Fibonacci<T>::begin() const {
    if (start) {
        return {*this, start.value().first, start.value().second};
    } else {
        return {*this, 0, 1};
    }
}

template<typename T>
IterateurFibonacci<T> Fibonacci<T>::end() const {
    return {*this, 0, 0};
}

template<typename T>
void Fibonacci<T>::suivant(IterateurFibonacci<T> &it) const {
    if (limite && it.p + it.q > limite.value()) {
        it.p = 0;
        it.q = 0;
    } else {
        std::tie(it.p, it.q) = std::make_pair(it.q, it.p + it.q);
    }
}
