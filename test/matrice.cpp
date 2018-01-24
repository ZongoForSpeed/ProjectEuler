#include <gtest/gtest.h>

#include "matrice.h"
#include "test.h"

#include <boost/numeric/ublas/assignment.hpp> 
#include <boost/rational.hpp>

    TEST(test_matrice, puissance)
    {
        matrice::matrice<long long> A(2, 2);
        A <<= 1, 1,
              1, 0;
        
        auto F = matrice::puissance_matrice(A, 40);
        
        const std::vector<long long> resultat { 165580141, 102334155, 
                                                102334155, 63245986 };
        
        EXPECT_EQ(F.size1(), 2);
        EXPECT_EQ(F.size2(), 2);
        EXPECT_EQ(F(0, 0), 165580141);
        EXPECT_EQ(F(1, 0), 102334155);
        EXPECT_EQ(F(0, 1), 102334155);
        EXPECT_EQ(F(1, 1), 63245986);
        
        EXPECT_EQ_COLLECTIONS(resultat.begin(), resultat.end(), 
                                      F.data().begin(), F.data().end());
    }
    
    TEST(test_matrice, puissance_modulaire)
    {
        matrice::matrice<long long> A(2, 2);
        A <<= 1, 1,
              1, 0;
        
        auto F = matrice::puissance_matrice<long long>(A, 100, 1000000000);
        
        const std::vector<long long> resultat { 817084101, 261915075, 
                                                261915075, 555169026 };
        
        EXPECT_EQ(F.size1(), 2);
        EXPECT_EQ(F.size2(), 2);
        EXPECT_EQ(F(0, 0), 817084101);
        EXPECT_EQ(F(1, 0), 261915075);
        EXPECT_EQ(F(0, 1), 261915075);
        EXPECT_EQ(F(1, 1), 555169026);
        
        EXPECT_EQ_COLLECTIONS(resultat.begin(), resultat.end(), 
                                      F.data().begin(), F.data().end());
    }
    
    TEST(test_matrice, inversion1)
    {
        typedef boost::rational<long long> fraction;
        
        matrice::matrice<fraction> A(3, 3);
        A <<=  2, -1,  0,
              -1,  2, -1,
               0, -1,  2;
               
        matrice::matrice<fraction> resultat(3, 3);
        resultat <<= 3, 2, 1,
                     2, 4, 2,
                     1, 2, 3;
        resultat /= 4;
        
        matrice::matrice<fraction> inverse(3, 3);
        
        bool inversible = matrice::inversionLU(A, inverse);
        
        EXPECT_EQ(inversible, true);
        EXPECT_EQ_COLLECTIONS(resultat.data().begin(), resultat.data().end(), 
                                      inverse.data().begin(), inverse.data().end());
        
        matrice::matrice<fraction> identite(3, 3);
        identite <<= 1, 0, 0,
                     0, 1, 0,
                     0, 0, 1;
        
        matrice::matrice<fraction> produit = boost::numeric::ublas::prod(A, inverse);        

        EXPECT_EQ_COLLECTIONS(produit.data().begin(), produit.data().end(), 
                                      identite.data().begin(), identite.data().end());
    }
    
    TEST(test_matrice, inversion2)
    {
        typedef boost::rational<long long> fraction;
        
        matrice::matrice<fraction> A(4, 4);
        A <<= 1,  1,  1, -1, 
              1,  2,  6,  7,
              1,  2,  9,  0, 
              2,  5,  9, 15;
               
        matrice::matrice<fraction> resultat(4, 4);
        resultat <<= 99, 132, -44, -55,
                    -18,-129,  29,  59,
                     -7,  14,   7,  -7,
                     -3,  17,  -8,  -3;
        resultat /= 77;
        
        matrice::matrice<fraction> inverse(4, 4);
        
        bool inversible = matrice::inversionLU(A, inverse);
        
        EXPECT_EQ(inversible, true);
        EXPECT_EQ_COLLECTIONS(resultat.data().begin(), resultat.data().end(), 
                                      inverse.data().begin(), inverse.data().end());
        
        matrice::matrice<fraction> identite(4, 4);
        identite <<= 1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1;
        
        matrice::matrice<fraction> produit = boost::numeric::ublas::prod(A, inverse);        

        EXPECT_EQ_COLLECTIONS(produit.data().begin(), produit.data().end(), 
                                      identite.data().begin(), identite.data().end());
    }
    
    TEST(test_matrice, resolution_vecteur)
    {
        typedef boost::rational<long long> fraction;
        
        matrice::matrice<fraction> A(3, 3);
        A <<=  1, -1,  2,
               3,  2,  1,
               2, -3, -2;
               
        matrice::vecteur<fraction> b(3);
        b <<=  5, 10, -10;
        
        matrice::vecteur<fraction> resultat(3);
        resultat <<= 1, 2, 3;
        
        matrice::vecteur<fraction> x(3);
        bool solution = matrice::resolutionLU(A, b, x);
        
        EXPECT_EQ(solution, true);
        EXPECT_EQ_COLLECTIONS(x.data().begin(), x.data().end(), 
                                      resultat.data().begin(), resultat.data().end());
                                      
        matrice::vecteur<fraction> produit = boost::numeric::ublas::prod(A, x);        

        EXPECT_EQ_COLLECTIONS(produit.data().begin(), produit.data().end(), 
                                      b.data().begin(), b.data().end());
    }
    
    TEST(test_matrice, resolution_matrice)
    {
        typedef boost::rational<long long> fraction;
        
        matrice::matrice<fraction> A(3, 3);
        A <<=  1, -1,  2,
               3,  2,  1,
               2, -3, -2;
               
        matrice::matrice<fraction> B(3, 3);
        B <<=   5,  1,  1,
               10,  1,  2,
              -10,  6,  0;
        
        matrice::matrice<fraction> resultat(3, 3);
        resultat <<= 35,  39, 17,
                     70, -32,  4,
                    105, -18, 11;
        resultat /= 35;
        
        matrice::matrice<fraction> X(3, 3);
        bool solution = matrice::resolutionLU(A, B, X);
        
        EXPECT_EQ(solution, true);
        EXPECT_EQ_COLLECTIONS(X.data().begin(), X.data().end(), 
                                      resultat.data().begin(), resultat.data().end());
                                      
        matrice::matrice<fraction> produit = boost::numeric::ublas::prod(A, X);        

        EXPECT_EQ_COLLECTIONS(produit.data().begin(), produit.data().end(), 
                                      B.data().begin(), B.data().end());
    }
