#pragma once

#include <functional>
#include <vector>

namespace premiers {
    void algorithme_crible2(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_crible23(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_crible235(const std::size_t &taille, std::function<void(const std::size_t &)> sortie);

    void algorithme_super_crible(const std::size_t taille, const std::vector<std::size_t> &roue, std::function<void(const std::size_t &)> sortie);

    template<typename Nombre, class OutputIterator>
    OutputIterator crible2(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible2(taille,
                           [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator crible23(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible23(taille,
                            [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(const std::size_t &taille, OutputIterator sortie) {
        algorithme_crible235(taille,
                             [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }

    template<typename Nombre, class OutputIterator>
    OutputIterator super_crible(const std::size_t &taille, const std::vector<std::size_t> &roue, OutputIterator sortie) {
        algorithme_super_crible(taille, roue,
                                [&sortie](const std::size_t &p) { *sortie++ = Nombre(p); });
        return sortie;
    }
    
    void crible_simple(size_t taille, std::vector<bool> & sortie);
}
