#include <boost/test/unit_test.hpp>

#include "matrice.h"

BOOST_AUTO_TEST_SUITE(test_matrice)
    BOOST_AUTO_TEST_CASE(puissance)
    {
        matrice::matrice<long long> A(2, 2);
        A(0, 0) = A(1, 0) = A(0, 1) = 1;
        A(1, 1) = 0;
        
        auto F = matrice::puissance_matrice(A, 40);
        
        const std::vector<long long> resultat { 165580141, 102334155, 
                                                102334155, 63245986 };
        
        BOOST_CHECK_EQUAL(F.size1(), 2);
        BOOST_CHECK_EQUAL(F.size2(), 2);
        BOOST_CHECK_EQUAL(F(0, 0), 165580141);
        BOOST_CHECK_EQUAL(F(1, 0), 102334155);
        BOOST_CHECK_EQUAL(F(0, 1), 102334155);
        BOOST_CHECK_EQUAL(F(1, 1), 63245986);
        
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), 
                                      F.data().begin(), F.data().end());
    }
    
    BOOST_AUTO_TEST_CASE(puissance_modulaire)
    {
        matrice::matrice<long long> A(2, 2);
        A(0, 0) = A(1, 0) = A(0, 1) = 1;
        A(1, 1) = 0;
        
        auto F = matrice::puissance_matrice<long long>(A, 100, 1000000000);
        
        const std::vector<long long> resultat { 817084101, 261915075, 
                                                261915075, 555169026 };
        
        BOOST_CHECK_EQUAL(F.size1(), 2);
        BOOST_CHECK_EQUAL(F.size2(), 2);
        BOOST_CHECK_EQUAL(F(0, 0), 817084101);
        BOOST_CHECK_EQUAL(F(1, 0), 261915075);
        BOOST_CHECK_EQUAL(F(0, 1), 261915075);
        BOOST_CHECK_EQUAL(F(1, 1), 555169026);
        
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), 
                                      F.data().begin(), F.data().end());
    }
BOOST_AUTO_TEST_SUITE_END()
