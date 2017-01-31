#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "mp_nombre.h"

BOOST_AUTO_TEST_SUITE(test_mp_nombre)
    BOOST_AUTO_TEST_CASE(test_constructeur)
    {
        mp_nombre n1;
        mp_nombre n2(42);
        mp_nombre n3(-666);
        mp_nombre n4(3.14158);
        mp_nombre n5(22801763489LL);
        mp_nombre n7("22801763489");
        
        BOOST_CHECK_EQUAL(n1.get_signed_long(), 0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "101010");
        BOOST_CHECK_EQUAL(n3.to_string(6), "-3030");
        BOOST_CHECK_EQUAL(n4.get_signed_long(), 3);
        BOOST_CHECK_EQUAL(n5.to_string(), "22801763489");
        BOOST_CHECK_EQUAL(n7, 22801763489);
    }
    
    BOOST_AUTO_TEST_CASE(test_assignation)
    {
        mp_nombre n;
        BOOST_CHECK_EQUAL(n, 0);

        n.set(42);
        BOOST_CHECK_EQUAL(n.to_string(2), "101010");
        
        n.set(-666);
        BOOST_CHECK_EQUAL(n.to_string(6), "-3030");
        
        n.set(3.14158);
        BOOST_CHECK_EQUAL(n.to_string(), "3");
        
        n.set(-22801763489LL);
        BOOST_CHECK_EQUAL(n, -22801763489);
        
        n.set("228017634890", 10);
        BOOST_CHECK_EQUAL(n, 228017634890);
        
        mp_nombre m(-22632576532575);
        std::swap(n, m);
        BOOST_CHECK_EQUAL(m.to_string(), "228017634890");
        BOOST_CHECK_EQUAL(n.to_string(), "-22632576532575");
        
        n.swap(m);
        BOOST_CHECK_EQUAL(m.to_string(), "-22632576532575");
        BOOST_CHECK_EQUAL(n.to_string(), "228017634890");
    }
    
    BOOST_AUTO_TEST_CASE(test_addition)
    {
        mp_nombre n(22801763489LL);
        mp_nombre m(22632576532575LL);
        n += m;

        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296064);

        n += 100;
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296164);

        n += m;
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 45287954828739);

        mp_nombre p = n + m;
        BOOST_CHECK_EQUAL(p.get_unsigned_long_long(), 67920531361314);

        mp_nombre q = 42ul + m;
        BOOST_CHECK_EQUAL(q.get_unsigned_long_long(), 22632576532617);

        mp_nombre r = n + 666ul;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 45287954829405);

        r += 400000000000000ull;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 445287954829405);
    }

    BOOST_AUTO_TEST_CASE(test_negation)
    {
        mp_nombre n(22632576532575LL);
        mp_nombre m = -n;
        BOOST_CHECK_EQUAL(m, -22632576532575);

        m.negation();
        BOOST_CHECK_EQUAL(m, 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_comparaison)
    {
        mp_nombre n (25413164);
        mp_nombre m (22632576532575);

        BOOST_CHECK(n == 25413164);
        BOOST_CHECK(n != 2543164);
        BOOST_CHECK(n > 25164);
        BOOST_CHECK(n >= 25413164);
        BOOST_CHECK(n >= 2543164);
        BOOST_CHECK(n <= 25413164);
        BOOST_CHECK(!(n <= 2543164));
        BOOST_CHECK(n < 213421164);
        BOOST_CHECK(!(n == m));
        BOOST_CHECK(n < m);
        BOOST_CHECK(m > n);
        BOOST_CHECK(n <= m);
        BOOST_CHECK(m >= m);
    }

    BOOST_AUTO_TEST_CASE(test_abs)
    {
        mp_nombre n(-22632576532575LL);
        mp_nombre m = std::abs(n);
        BOOST_CHECK_EQUAL(m.get_unsigned_long_long(), 22632576532575);

        n = mp_nombre::abs(n);
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_soustraction)
    {
        mp_nombre n(22801763489LL);
        mp_nombre m(22632576532575LL);
        n -= m;

        BOOST_CHECK_EQUAL(n, -22609774769086);

        n -= 100;
        BOOST_CHECK_EQUAL(n, -22609774769186);

        n -= m;
        BOOST_CHECK_EQUAL(n, -45242351301761);

        mp_nombre p = n - m;
        BOOST_CHECK_EQUAL(p, -67874927834336);

        mp_nombre q = 42ul - m;
        BOOST_CHECK_EQUAL(q, -22632576532533);

        mp_nombre r = n - 666ul;
        BOOST_CHECK_EQUAL(r, -45242351302427);

        r -= 400000000000000ull;
        BOOST_CHECK_EQUAL(r, -445242351302427);
    }

    BOOST_AUTO_TEST_CASE(test_multiplication)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(22632572575LL);
        n *= m;

        BOOST_CHECK_EQUAL(n.to_string(), "5160625763047650425");

        n *= 100;
        BOOST_CHECK_EQUAL(n.to_string(), "516062576304765042500");

        n *= m;
        BOOST_CHECK_EQUAL(n.to_string(), "11679823711459070142704209437500");

        mp_nombre p = n * m;
        BOOST_CHECK_EQUAL(p.to_string(), "264344457812803264146768626852218676562500");

        mp_nombre q = 42ul * m;
        BOOST_CHECK_EQUAL(q.to_string(), "950568048150");

        mp_nombre r = n * 666ul;
        BOOST_CHECK_EQUAL(r.to_string(), "7778762591831740715041003485375000");

        r *= 4;
        BOOST_CHECK_EQUAL(r.to_string(), "31115050367326962860164013941500000");
    }

    BOOST_AUTO_TEST_CASE(test_shift)
    {
        mp_nombre n(228);

        mp_nombre m = n << 10;
        BOOST_CHECK_EQUAL(m, 233472);

        mp_nombre p = n >> 5;
        BOOST_CHECK_EQUAL(p, 7);
    }

    BOOST_AUTO_TEST_CASE(test_division)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(275LL);
        n /= m;

        BOOST_CHECK_EQUAL(n, 829155);

        n /= 100;
        BOOST_CHECK_EQUAL(n, 8291);

        n/=m;
        BOOST_CHECK_EQUAL(n, 30);

        n.set(2280176);
        mp_nombre p = n / m;
        BOOST_CHECK_EQUAL(p, 8291);

        mp_nombre q = 42000000000000ul / m;
        BOOST_CHECK_EQUAL(q, 152727272727);

        mp_nombre r = n / 666ul;
        BOOST_CHECK_EQUAL(r, 3423);

        r /= 4;
        BOOST_CHECK_EQUAL(r, 855);
    }

    BOOST_AUTO_TEST_CASE(test_modulo)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(275LL);
        n %= m;

        BOOST_CHECK_EQUAL(n, 14);

        n %= 10;
        BOOST_CHECK_EQUAL(n, 4);

        n.set(2280176);
        n %= m;
        BOOST_CHECK_EQUAL(n, 151);

        n.set(2280176);
        mp_nombre p = n % m;
        BOOST_CHECK_EQUAL(p, 151);

        mp_nombre q = 42000000000000ul % m;
        BOOST_CHECK_EQUAL(q, 75);

        unsigned long r = n % 666ul;
        BOOST_CHECK_EQUAL(r, 458);

        r %= 4;
        BOOST_CHECK_EQUAL(r, 2);
    }

    BOOST_AUTO_TEST_CASE(test_divisible)
    {
        mp_nombre n(228017635LL);
        mp_nombre m(275LL);

        BOOST_CHECK_EQUAL(mp_nombre::divisible(n, m), false);
        BOOST_CHECK_EQUAL(mp_nombre::divisible(n, 5), true);
        BOOST_CHECK_EQUAL(mp_nombre::divisible(2750000, m), true);
    }

    BOOST_AUTO_TEST_CASE(test_puissance)
    {
        mp_nombre n(24);
        n = mp_nombre::puissance(n, 10);

        BOOST_CHECK_EQUAL(n, 63403380965376);

        n = mp_nombre::puissance_modulaire(n, 5, 1000);
        BOOST_CHECK_EQUAL(n, 376);

        mp_nombre m = mp_nombre::puissance(9, 10);
        BOOST_CHECK_EQUAL(m, 3486784401);

        mp_nombre p = mp_nombre::puissance_modulaire(m, 100000, 1024);
        BOOST_CHECK_EQUAL(p, 513);
    }

    BOOST_AUTO_TEST_CASE(test_racine)
    {
        mp_nombre n(63403380965376);
        BOOST_CHECK_EQUAL(mp_nombre::carre_parfait(n), true);

        mp_nombre m = mp_nombre::racine_carre(n);
        BOOST_CHECK_EQUAL(m, 7962624);
        BOOST_CHECK_EQUAL(mp_nombre::carre_parfait(m), false);

        mp_nombre p = mp_nombre::racine(n, 10);
        BOOST_CHECK_EQUAL(p, 24);

        mp_nombre q = std::sqrt(n);
        BOOST_CHECK_EQUAL(q, 7962624);

        mp_nombre r = std::cbrt(n);
        BOOST_CHECK_EQUAL(r, 39875);
    }

    BOOST_AUTO_TEST_CASE(test_premier)
    {
        mp_nombre n(22801763489);
        BOOST_CHECK(mp_nombre::premier(n));

        n *= 10;
        BOOST_CHECK(!mp_nombre::premier(n));

        mp_nombre m = mp_nombre::premier_suivant(n);
        BOOST_CHECK_EQUAL(m, 228017634893);
        BOOST_CHECK(mp_nombre::premier(m));
    }

    BOOST_AUTO_TEST_CASE(test_stream)
    {
        std::ostringstream oss;
        mp_nombre n(22801763489);
        oss << n;

        std::istringstream iss(oss.str());
        mp_nombre m;
        iss >> m;

        BOOST_CHECK_EQUAL(n, m);
    }

    BOOST_AUTO_TEST_CASE(test_logique)
    {
        mp_nombre n("10110000111000101", 2);
        mp_nombre m("10111110001010000", 2);

        mp_nombre n_and = n & m;
        mp_nombre n_or = n | m;
        mp_nombre n_xor = n ^ m;
        mp_nombre n_not = ~n;

        BOOST_CHECK_EQUAL(n_and.to_string(2), "10110000001000000");
        BOOST_CHECK_EQUAL(n_or.to_string(2), "10111110111010101");
        BOOST_CHECK_EQUAL(n_xor.to_string(2), "1110110010101");
        BOOST_CHECK_EQUAL(n_not.to_string(2), "-10110000111000110");
    }

    BOOST_AUTO_TEST_CASE(test_pgcd)
    {
        mp_nombre n(456753);
        mp_nombre m(97643);
        mp_nombre p(158665);

        BOOST_CHECK_EQUAL(mp_nombre::PGCD(n, m), 1);
        BOOST_CHECK_EQUAL(mp_nombre::PGCD(p, 456755), 65);
    }

    BOOST_AUTO_TEST_CASE(test_ppcm)
    {
        mp_nombre n(456753u);
        mp_nombre m(97643u);
        mp_nombre p(158665u);

        BOOST_CHECK_EQUAL(mp_nombre::PPCM(n, m), 44598733179);
        BOOST_CHECK_EQUAL(mp_nombre::PPCM(p, 456755), 1114938955);
    }

    BOOST_AUTO_TEST_CASE(test_chiffres)
    {
        mp_nombre n("31115050367326962860164013941500001");

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
        mp_nombre m("89123457675432198");
        BOOST_CHECK(m.palindrome());
    }
BOOST_AUTO_TEST_SUITE_END()
