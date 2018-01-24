#include "diophantienne.h"

namespace diophantienne {
    IterateurEquationLineaire::IterateurEquationLineaire(const GenerateurEquationLineaire &_source) : source(_source),
                                                                                                      t(0) {
    }

    bool IterateurEquationLineaire::operator!=(const IterateurEquationLineaire &it) const {
        return t != it.t;
    }

    std::pair<long long int, long long int> IterateurEquationLineaire::operator*() const {
        return source.solution(t);
    }

    const IterateurEquationLineaire &IterateurEquationLineaire::operator++() {
        source.suivant(*this);
        return *this;
    }

    GenerateurEquationLineaire::GenerateurEquationLineaire(long long int A, long long int B, long long int C) {
        // Ax + By + C = 0
        long long int g = arithmetiques::PGCD(A, B);
        if (C % g != 0) {
            // Pas de solution
            return;
        }

        d = A / g;
        e = B / g;
        long long int f = C / g;

        long long int u;
        long long int v;
        arithmetiques::Bezout(d, e, u, v);

        primitives.push_back(std::make_pair(-f * u, -f * v));

        // x = et ± fu'
        // y = -dt ± fv'
        // t = any integer
    }

    IterateurEquationLineaire GenerateurEquationLineaire::begin() const {
        if (primitives.empty())
            return end();

        return IterateurEquationLineaire(*this);
    }

    IterateurEquationLineaire GenerateurEquationLineaire::end() const {
        IterateurEquationLineaire it(*this);
        it.t = std::string::npos;
        return it;
    }

    void GenerateurEquationLineaire::suivant(IterateurEquationLineaire &it) const {
        ++it.t;
    }

    std::pair<long long int, long long int> GenerateurEquationLineaire::solution(size_t t) const {
        size_t taille = primitives.size();
        auto ordre = static_cast<long long int>(t / taille);

        auto &primitive = primitives[t % taille];

        return std::make_pair(primitive.first + e * ordre, primitive.second - d * ordre);
    }

    GenerateurEquationLineaire equation_lineaire(long long int A, long long int B, long long int C) {
        return GenerateurEquationLineaire(A, B, C);
    }
}
