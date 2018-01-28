#pragma once

#include "utilitaires.h"

#include <boost/range/join.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <algorithm>

namespace permutation {
    template<typename T>
    bool arrangement_suivant(const std::vector<T> &source, std::vector<bool> &indices, std::vector<T> &subSource) {
        while (std::prev_permutation(indices.begin(), indices.end())) {
            std::vector<T> resultat;
            std::for_each2(source.begin(), source.end(), indices.begin(),
                           [&resultat](T value, bool test) {
                               if (test) {
                                   resultat.push_back(value);
                               }
                           });
            if (!std::equal(resultat.begin(), resultat.end(), subSource.begin())) {
                std::swap(resultat, subSource);
                return true;
            }
        }
        return false;
    }

    template<typename T>
    class Permutation {
        T source;
    public:
        explicit Permutation(const T &v) : source(v) {}

        ~Permutation() = default;

        class Iterateur : public boost::iterator_facade<Iterateur, const T, boost::forward_traversal_tag> {
            T _source;
            size_t _index;
        public:
            Iterateur(T &s, size_t index) : _source(s), _index(index) {}

            // What we implement is determined by the boost::forward_traversal_tag
            // template parameter
        private:
            friend class boost::iterator_core_access;

            friend class MyContainer;

            void increment() {
                if (_index == std::string::npos) {
                    return;
                }

                if (std::next_permutation(_source.begin(), _source.end())) {
                    ++_index;
                } else {
                    _index = std::string::npos;
                }
            }

            bool equal(Iterateur const &other) const {
                return this->_index == other._index;
            }

            const T &dereference() const {
                return _source;
            }
        };

        Iterateur begin() {
            return Iterateur(source, 0);
        }

        Iterateur end() {
            return Iterateur(source, std::string::npos);
        }
    };

    template<typename T>
    class Combinaisons {
        std::vector<T> source;
        size_t taille;

    public:
        Combinaisons(const std::vector<T> &v, size_t t) : source(v), taille(t) {}

        ~Combinaisons() = default;

        class Iterateur : public boost::iterator_facade<Iterateur, const std::vector<T>, boost::forward_traversal_tag> {
            const std::vector<T> &_source;
            size_t _taille;
            size_t _index;

            std::vector<bool> _indices;
            std::vector<T> _courant;
        public:
            Iterateur(const std::vector<T> &s, size_t t, size_t index) : _source(s), _taille(t), _index(index) {
                size_t n = utilitaires::distance(_source.begin(), _source.end());
                _indices.assign(n, false);
                for (size_t i = 0; i < t; ++i) {
                    _indices[i] = true;
                }

                _courant.assign(_source.begin(), std::next(_source.begin(), _taille));
            }

        private:
            friend class boost::iterator_core_access;

            void increment() {
                if (_index == std::string::npos) {
                    return;
                }


                if (arrangement_suivant(_source, _indices, _courant)) {
                    ++_index;
                } else {
                    _index = std::string::npos;
                }
            }

            bool equal(Iterateur const &other) const {
                return this->_index == other._index;
            }

            const std::vector<T> &dereference() const {
                return _courant;
            }
        };

        Iterateur begin() {
            if (taille > source.size()) {
                return end();
            } else {
                return Iterateur(source, taille, 0);
            }
        }

        Iterateur end() {
            return Iterateur(source, taille, std::string::npos);
        }
    };

    template<typename T>
    class Arrangements {
        std::vector<T> source;
        size_t taille;

    public:
        Arrangements(const std::vector<T> &v, size_t t) : source(v), taille(t) {}

        ~Arrangements() = default;

        class Iterateur : public boost::iterator_facade<Iterateur, const std::vector<T>, boost::forward_traversal_tag> {
            const std::vector<T> &_source;
            size_t _taille;
            size_t _index;

            std::vector<bool> _indices;
            std::vector<T> _courant;
        public:
            Iterateur(const std::vector<T> &s, size_t t, size_t index) : _source(s), _taille(t), _index(index) {
                size_t n = utilitaires::distance(_source.begin(), _source.end());
                _indices.assign(n, false);
                for (size_t i = 0; i < t; ++i) {
                    _indices[i] = true;
                }

                _courant.assign(_source.begin(), std::next(_source.begin(), _taille));
            }

        private:
            friend class boost::iterator_core_access;

            void increment() {
                if (_index == std::string::npos) {
                    return;
                }

                if (std::next_permutation(_courant.begin(), _courant.end())) {
                    ++_index;
                } else {
                    if (arrangement_suivant(_source, _indices, _courant)) {
                        ++_index;
                    } else {
                        _index = std::string::npos;
                    }
                }
            }

            bool equal(Iterateur const &other) const {
                return this->_index == other._index;
            }

            const std::vector<T> &dereference() const {
                return _courant;
            }
        };

        Iterateur begin() {
            if (taille > source.size()) {
                return end();
            } else {
                return Iterateur(source, taille, 0);
            }
        }

        Iterateur end() {
            return Iterateur(source, taille, std::string::npos);
        }
    };
}
