#pragma once

#define NDEBUG
#define BOOST_UBLAS_NDEBUG
#define BOOST_UBLAS_TYPE_CHECK 0

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/assignment.hpp>

namespace matrice {
    template<typename Nombre>
    using matrice = boost::numeric::ublas::matrix<Nombre>;

    template<typename Nombre>
    using vecteur = boost::numeric::ublas::vector<Nombre>;

    template<typename Nombre>
    matrice<Nombre> puissance_matrice(matrice<Nombre> base, size_t exposant) {
        matrice<Nombre> resultat(base.size1(), base.size2(), 0);
        for (size_t i = 0; i < base.size1(); ++i) resultat(i, i) = 1;

        while (exposant > 0) {
            if (exposant % 2)
                resultat = boost::numeric::ublas::prod(resultat, base);
            exposant /= 2;
            base = boost::numeric::ublas::prod(base, base);
        }
        return resultat;
    }

    template<typename Nombre>
    matrice<Nombre> puissance_matrice(matrice<Nombre> base, size_t exposant, Nombre modulo) {
        matrice<Nombre> resultat(base.size1(), base.size2(), 0);
        for (size_t i = 0; i < base.size1(); ++i) resultat(i, i) = 1;

        while (exposant > 0) {
            if (exposant % 2) {
                resultat = boost::numeric::ublas::prod(resultat, base);
                for (auto &m: resultat.data()) m %= modulo;
            }
            exposant /= 2;
            base = boost::numeric::ublas::prod(base, base);
            for (auto &m: base.data()) m %= modulo;
        }
        return resultat;
    }

    template<typename Nombre, typename Resultat>
    bool decompositionLU(const matrice<Nombre> &entree, Resultat &resultat) {
        // matrice de travail
        matrice<Nombre> m(entree);

        // matrice de permutation pour la factorisation LU
        boost::numeric::ublas::permutation_matrix<std::size_t> permutation(m.size1());

        // factorisation LU
        size_t res = boost::numeric::ublas::lu_factorize(m, permutation);
        if (res != 0)
            return false;

        // substitution du resultat
        boost::numeric::ublas::lu_substitute(m, permutation, resultat);

        return true;
    }

    template<typename Nombre>
    bool inversionLU(const matrice<Nombre> &entree, matrice<Nombre> &inverse) {
        if (entree.size1() != entree.size2())
            return false;

        // create identity matrix of "inverse"
        inverse.assign(boost::numeric::ublas::identity_matrix<Nombre>(entree.size1()));

        return decompositionLU(entree, inverse);
    }

    template<typename Nombre>
    bool resolutionLU(const matrice<Nombre> &A, const vecteur<Nombre> &b, vecteur<Nombre> &x) {
        // résolution vectorielle Ax = b
        x.assign(b);
        return decompositionLU(A, x);
    }

    template<typename Nombre>
    bool resolutionLU(const matrice<Nombre> &A, const matrice<Nombre> &B, matrice<Nombre> &X) {
        // résolution matricielle A.X = B
        X.assign(B);
        return decompositionLU(A, X);
    }
}
