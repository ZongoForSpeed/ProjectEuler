#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "grand_nombre.h"

BOOST_AUTO_TEST_SUITE(test_grand_nombre)
    BOOST_AUTO_TEST_CASE(test_constructeur)
    {
        grand_nombre n1;
        grand_nombre n2(42);
        grand_nombre n3(-666);
        grand_nombre n4(3.14158);
        grand_nombre n5(22801763489LL);
        grand_nombre n6(2.71828182846L);
        grand_nombre n7("22801763489");
        
        BOOST_CHECK_EQUAL(n1.get_signed_long(), 0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "101010");
        BOOST_CHECK_EQUAL(n3.to_string(6), "-3030");
        BOOST_CHECK_EQUAL(n4.get_signed_long(), 3);
        BOOST_CHECK_EQUAL(n5.to_string(), "22801763489");
        BOOST_CHECK_EQUAL(n6.get_signed_long(), 3);
        BOOST_CHECK_EQUAL(n7, 22801763489);
    }
    
    BOOST_AUTO_TEST_CASE(test_assignation)
    {
        grand_nombre n;
        BOOST_CHECK_EQUAL(n, 0);

        n.set(42);
        BOOST_CHECK_EQUAL(n.to_string(2), "101010");
        
        n.set(-666);
        BOOST_CHECK_EQUAL(n.to_string(6), "-3030");
        
        n.set(3.14158);
        BOOST_CHECK_EQUAL(n.to_string(), "3");
        
        n.set(-22801763489LL);
        BOOST_CHECK_EQUAL(n, -22801763489);
        
        n.set(2.71828182846L);
        BOOST_CHECK_EQUAL(n, 3);
        
        n.set("228017634890", 10);
        BOOST_CHECK_EQUAL(n, 228017634890);
        
        grand_nombre m(-22632576532575);
        std::swap(n, m);
        BOOST_CHECK_EQUAL(m.to_string(), "228017634890");
        BOOST_CHECK_EQUAL(n.to_string(), "-22632576532575");
        
        n.swap(m);
        BOOST_CHECK_EQUAL(m.to_string(), "-22632576532575");
        BOOST_CHECK_EQUAL(n.to_string(), "228017634890");

    }
    
    BOOST_AUTO_TEST_CASE(test_addition)
    {
        grand_nombre n(22801763489LL);
        grand_nombre m(22632576532575LL);
        n.addition(m);
        
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296064);
        
        n.addition(100);
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296164);
        
        n+=m;
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 45287954828739);
        
        grand_nombre p = n + m;
        BOOST_CHECK_EQUAL(p.get_unsigned_long_long(), 67920531361314);
        
        grand_nombre q = 42ul + m;
        BOOST_CHECK_EQUAL(q.get_unsigned_long_long(), 22632576532617);
        
        grand_nombre r = n + 666ul;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 45287954829405);
        
        r += 400000000000000ull;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 445287954829405);
    }
    
    BOOST_AUTO_TEST_CASE(test_negation)
    {
        grand_nombre n(22632576532575LL);
        grand_nombre m = -n;
        BOOST_CHECK_EQUAL(m, -22632576532575);

        m.negation();
        BOOST_CHECK_EQUAL(m, 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_abs)
    {
        grand_nombre n(-22632576532575LL);
        grand_nombre m = std::abs(n);
        BOOST_CHECK_EQUAL(m.get_unsigned_long_long(), 22632576532575);

        n.abs();
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22632576532575);  
    }
    
    BOOST_AUTO_TEST_CASE(test_soustraction)
    {
        grand_nombre n(22801763489LL);
        grand_nombre m(22632576532575LL);
        n.soustraction(m);
        
        BOOST_CHECK_EQUAL(n, -22609774769086);
        
        n.soustraction(100);
        BOOST_CHECK_EQUAL(n, -22609774769186);
        
        n-=m;
        BOOST_CHECK_EQUAL(n, -45242351301761);
        
        grand_nombre p = n - m;
        BOOST_CHECK_EQUAL(p, -67874927834336);
        
        grand_nombre q = 42ul - m;
        BOOST_CHECK_EQUAL(q, -22632576532533);
        
        grand_nombre r = n - 666ul;
        BOOST_CHECK_EQUAL(r, -45242351302427);
        
        r -= 400000000000000ull;
        BOOST_CHECK_EQUAL(r, -445242351302427);
    }
    
    BOOST_AUTO_TEST_CASE(test_multiplication)
    {
        grand_nombre n(228017639LL);
        grand_nombre m(22632572575LL);
        n.multiplication(m);
        
        BOOST_CHECK_EQUAL(n.to_string(), "5160625763047650425");
        
        n.multiplication(100);
        BOOST_CHECK_EQUAL(n.to_string(), "516062576304765042500");
        
        n*=m;
        BOOST_CHECK_EQUAL(n.to_string(), "11679823711459070142704209437500");
        
        grand_nombre p = n * m;
        BOOST_CHECK_EQUAL(p.to_string(), "264344457812803264146768626852218676562500");
        
        grand_nombre q = 42ul * m;
        BOOST_CHECK_EQUAL(q.to_string(), "950568048150");
        
        grand_nombre r = n * 666ul;
        BOOST_CHECK_EQUAL(r.to_string(), "7778762591831740715041003485375000");
        
        r *= 4;
        BOOST_CHECK_EQUAL(r.to_string(), "31115050367326962860164013941500000");
    }
    
    BOOST_AUTO_TEST_CASE(test_shift)
    {
        grand_nombre n(228);
        
        grand_nombre m = n << 10;
        BOOST_CHECK_EQUAL(m, 233472);
        
        grand_nombre p = n >> 5;
        BOOST_CHECK_EQUAL(p, 7);
    }
    
    BOOST_AUTO_TEST_CASE(test_division)
    {
        grand_nombre n(228017639LL);
        grand_nombre m(275LL);
        n.division(m);
        
        BOOST_CHECK_EQUAL(n, 829155);
        
        n.division(100);
        BOOST_CHECK_EQUAL(n, 8291);
        
        n/=m;
        BOOST_CHECK_EQUAL(n, 30);
        
        n.set(2280176);
        grand_nombre p = n / m;
        BOOST_CHECK_EQUAL(p, 8291);
        
        grand_nombre q = 42000000000000ul / m;
        BOOST_CHECK_EQUAL(q, 152727272727);
        
        grand_nombre r = n / 666ul;
        BOOST_CHECK_EQUAL(r, 3423);
        
        r /= 4;
        BOOST_CHECK_EQUAL(r, 855);
    }
    
    BOOST_AUTO_TEST_CASE(test_modulo)
    {
        grand_nombre n(228017639LL);
        grand_nombre m(275LL);
        n.modulo(m);
        
        BOOST_CHECK_EQUAL(n, 14);
        
        n.modulo(100);
        BOOST_CHECK_EQUAL(n, 14);
        
        n.set(2280176);
        n%=m;
        BOOST_CHECK_EQUAL(n, 151);
        
        n.set(2280176);
        grand_nombre p = n % m;
        BOOST_CHECK_EQUAL(p, 151);
        
        grand_nombre q = 42000000000000ul % m;
        BOOST_CHECK_EQUAL(q, 75);
        
        grand_nombre r = n % 666ul;
        BOOST_CHECK_EQUAL(r, 458);
        
        r %= 4;
        BOOST_CHECK_EQUAL(r, 2);
    }
    
    BOOST_AUTO_TEST_CASE(test_divisible)
    {
        grand_nombre n(228017635LL);
        grand_nombre m(275LL);
        
        BOOST_CHECK_EQUAL(n.divisible(m), false);
        BOOST_CHECK_EQUAL(n.divisible(5), true);
        
        BOOST_CHECK_EQUAL(grand_nombre::divise(n, m), false);
        BOOST_CHECK_EQUAL(grand_nombre::divise(n, 5), true);
        BOOST_CHECK_EQUAL(grand_nombre::divise(2750000, m), true);
    }

    BOOST_AUTO_TEST_CASE(test_puissance)
    {
        grand_nombre n(24);
        n.puissance(10);
        
        BOOST_CHECK_EQUAL(n, 63403380965376);
        
        n.puissance_modulaire(5, 1000);
        BOOST_CHECK_EQUAL(n, 376);
        
        grand_nombre m = grand_nombre::puissance(9, 10);
        BOOST_CHECK_EQUAL(m, 3486784401);
        
        grand_nombre p = grand_nombre::puissance_modulaire(m, 100000, 1024);
        BOOST_CHECK_EQUAL(p, 513);
    }
    
    BOOST_AUTO_TEST_CASE(test_racine)
    {
        grand_nombre n(63403380965376LL);
        BOOST_CHECK_EQUAL(n.carre_parfait(), true);

        grand_nombre m = n.racine_carre();
        BOOST_CHECK_EQUAL(m, 7962624);
        BOOST_CHECK_EQUAL(m.carre_parfait(), false);

        grand_nombre p = n.racine(10);
        BOOST_CHECK_EQUAL(p, 24);
        
        grand_nombre q = std::sqrt(n);
        BOOST_CHECK_EQUAL(q, 7962624);
        
        grand_nombre r = std::cbrt(n);
        BOOST_CHECK_EQUAL(r, 39875);
    }
    
    BOOST_AUTO_TEST_CASE(test_premier)
    {
        grand_nombre n(22801763489);
        BOOST_CHECK_EQUAL(n.premier(), true);
        
        n *= 10;
        BOOST_CHECK_EQUAL(n.premier(), false);
        
        grand_nombre m = n.premier_suivant();
        BOOST_CHECK_EQUAL(m, 228017634893);
    }
    
    BOOST_AUTO_TEST_CASE(test_stream)
    {
        std::ostringstream oss;
        grand_nombre n(22801763489);
        oss << n;
        
        std::istringstream iss(oss.str());
        grand_nombre m;
        iss >> m;
        
        BOOST_CHECK_EQUAL(n, m);
    }
    
    BOOST_AUTO_TEST_CASE(test_logique)
    {
        grand_nombre n("10110000111000101", 2);
        grand_nombre m("10111110001010000", 2);
        
        grand_nombre n_and = n & m;
        grand_nombre n_or = n | m;
        grand_nombre n_xor = n ^ m;
        grand_nombre n_not = ~n;
        
        BOOST_CHECK_EQUAL(n_and.to_string(2), "10110000001000000");
        BOOST_CHECK_EQUAL(n_or.to_string(2), "10111110111010101");
        BOOST_CHECK_EQUAL(n_xor.to_string(2), "1110110010101");
        BOOST_CHECK_EQUAL(n_not.to_string(2), "-10110000111000110");
    }
    
    BOOST_AUTO_TEST_CASE(test_pgcd)
    {
        grand_nombre n(456753);
        grand_nombre m(97643);
        grand_nombre p(158665);
        
        BOOST_CHECK_EQUAL(grand_nombre::PGCD(n, m), 1);
        BOOST_CHECK_EQUAL(grand_nombre::PGCD(p, 456755), 65);
    }

    BOOST_AUTO_TEST_CASE(test_ppcm)
    {
        grand_nombre n(456753u);
        grand_nombre m(97643u);
        grand_nombre p(158665u);
        
        BOOST_CHECK_EQUAL(grand_nombre::PPCM(n, m), 44598733179);
        BOOST_CHECK_EQUAL(grand_nombre::PPCM(p, 456755), 1114938955);
    }

    BOOST_AUTO_TEST_CASE(test_chiffres)
    {
        grand_nombre n("31115050367326962860164013941500001");

        std::deque<unsigned long int> chiffres;
        n.boucle_chiffre([&chiffres] (unsigned long int d) { chiffres.push_front(d); });

        const std::vector<unsigned long int> resultat {
                3,1,1,1,5,0,5,0,3,6,7,3,2,6,9,6,2,8,6,0,1,6,4,0,1,3,9,4,1,5,0,0,0,0,1
        };

        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), chiffres.begin(), chiffres.end());

        BOOST_CHECK_EQUAL(n.nombre_chiffres(), 35);
        BOOST_CHECK_EQUAL(n.somme_chiffres(14), 198);

        auto ec = n.extraire_chiffres();
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), ec.begin(), ec.end());

        BOOST_CHECK_EQUAL(n.inverser_nombre(), "10000514931046106826962376305051113");
        BOOST_CHECK(!n.palindrome());
        grand_nombre m("89123457675432198");
        BOOST_CHECK(m.palindrome());
    }
BOOST_AUTO_TEST_SUITE_END()
