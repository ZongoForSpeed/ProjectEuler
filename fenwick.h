#pragma once

#include <deque>

template<typename ValueType>
class Fenwick {
    std::deque<ValueType> arbre;
    size_t taille;

    static size_t LSB(size_t x) {
        return ((x ^ x - 1) + 1) >> 1;
    }

public:
    explicit Fenwick(size_t t) : arbre(t, 0), taille(t) {
    }

    ValueType &
    operator[](size_t n) { return this->arbre[n]; }

    const ValueType &
    operator[](size_t n) const { return this->arbre[n]; }

    // Fen_sum: return the sum of the first i elements, 0 through i-1.
    ValueType somme(size_t i) {
        ValueType sum = 0;
        while (i) {
            sum += arbre[i];
            i -= LSB(i);
        }
        return sum;
    }

    ValueType somme(size_t i, const ValueType &modulo) {
        ValueType sum = 0;
        while (i) {
            sum += arbre[i];
            sum %= modulo;
            i -= LSB(i);
        }
        return sum;
    }

    // Fen_add: add k to element i (and thus Fen_sum(a, j) for all j > i)
    void add(size_t i, ValueType delta) {
        while (i < taille) {
            arbre[i] += delta;
            i += LSB(i);
        }
    }

    void add(size_t i, ValueType delta, const ValueType &modulo) {
        while (i < taille) {
            arbre[i] += delta;
            arbre[i] %= modulo;
            i += LSB(i);
        }
    }

    // Fen_range: Returns the sum of the elements [i..j-1]
    // This could be written as "Fen_sum(a, j) - Fen_sum(a, i)",
    // but it is possible to do it in less time (particularly for
    // small ranges) by avoiding the terms that the two sums have
    // in common.
    ValueType range(size_t i, size_t j) {
        ValueType sum = 0;

        while (j > i) {
            sum += arbre[j];
            j -= LSB(j);
        }

        while (i > j) {
            sum -= arbre[i];
            i -= LSB(i);
        }
        return sum;
    }

    ValueType range(size_t i, size_t j, const ValueType &modulo) {
        ValueType sum = 0;

        while (j > i) {
            sum += arbre[j];
            sum %= modulo;
            j -= LSB(j);
        }

        while (i > j) {
            sum += modulo - arbre[i];
            i -= LSB(i);
        }
        return sum % modulo;
    }

    // Fen_get: Returns the value of the element at index i
    // (The time is proportional to the number of trailing 1 bits
    // in i.  So even numbers are fast, and i = 0xffff takes 16 steps.)
    ValueType get(size_t i) {
        return range(i, i + 1);
    }

    ValueType get(size_t i, const ValueType &modulo) {
        return range(i, i + 1, modulo);
    }

    // Fen_set: sets the value of the element at index i
    void set(size_t i, ValueType value) {
        add(value - get(i), i);
    }

    void set(size_t i, ValueType value, const ValueType &modulo) {
        add(modulo + value - get(i), i, modulo);
    }

    // It's possible to initialize a Fenwick tree using Fen_add or
    // Fen_set (you can even do the latter in-place if you go backward
    // through the array), but for bulk initialization, this is faster.
    void initialisation() {
        for (size_t i = 0; i < taille; i++) {
            size_t j = i + LSB(i);
            if (j < taille)
                arbre[j] += arbre[i];
        }
    }
};
