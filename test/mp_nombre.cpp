#include <gtest/gtest.h>

#include "utilitaires.h"
#include "mp_nombre.h"
#include "test.h"

TEST(test_mp_nombre, test_constructeur)
    {
        mp_nombre n1;
        mp_nombre n2(42);
        mp_nombre n3(-666);
        mp_nombre n4(3.14158);
        mp_nombre n5(22801763489LL);
        mp_nombre n7("22801763489");
        
        EXPECT_EQ(n1.get_signed_long(), 0);
        EXPECT_EQ(n2.to_string(2), "101010");
        EXPECT_EQ(n3.to_string(6), "-3030");
        EXPECT_EQ(n4.get_signed_long(), 3);
        EXPECT_EQ(n5.to_string(), "22801763489");
        EXPECT_EQ(n7, 22801763489);
    }
    
    TEST(test_mp_nombre, test_assignation)
    {
        mp_nombre n;
        EXPECT_EQ(n, 0);

        n.set(42);
        EXPECT_EQ(n.to_string(2), "101010");
        
        n.set(-666);
        EXPECT_EQ(n.to_string(6), "-3030");
        
        n.set(3.14158);
        EXPECT_EQ(n.to_string(), "3");
        
        n.set(-22801763489LL);
        EXPECT_EQ(n, -22801763489);
        
        n.set("228017634890", 10);
        EXPECT_EQ(n, 228017634890);
        
        mp_nombre m(-22632576532575);
        std::swap(n, m);
        EXPECT_EQ(m.to_string(), "228017634890");
        EXPECT_EQ(n.to_string(), "-22632576532575");
        
        n.swap(m);
        EXPECT_EQ(m.to_string(), "-22632576532575");
        EXPECT_EQ(n.to_string(), "228017634890");
    }
    
    TEST(test_mp_nombre, test_addition)
    {
        mp_nombre n(22801763489LL);
        mp_nombre m(22632576532575LL);
        n += m;

        EXPECT_EQ(n.get_unsigned_long_long(), 22655378296064);

        n += 100;
        EXPECT_EQ(n.get_unsigned_long_long(), 22655378296164);

        n += m;
        EXPECT_EQ(n.get_unsigned_long_long(), 45287954828739);

        mp_nombre p = n + m;
        EXPECT_EQ(p.get_unsigned_long_long(), 67920531361314);

        mp_nombre q = 42ul + m;
        EXPECT_EQ(q.get_unsigned_long_long(), 22632576532617);

        mp_nombre r = n + 666ul;
        EXPECT_EQ(r.get_unsigned_long_long(), 45287954829405);

        r += 400000000000000ull;
        EXPECT_EQ(r.get_unsigned_long_long(), 445287954829405);
    }

    TEST(test_mp_nombre, test_negation)
    {
        mp_nombre n(22632576532575LL);
        mp_nombre m = -n;
        EXPECT_EQ(m, -22632576532575);

        m.negation();
        EXPECT_EQ(m, 22632576532575);
    }

    TEST(test_mp_nombre, test_comparaison)
    {
        mp_nombre n (25413164);
        mp_nombre m (22632576532575);

        EXPECT_TRUE(n == 25413164);
        EXPECT_TRUE(n != 2543164);
        EXPECT_TRUE(n > 25164);
        EXPECT_TRUE(n >= 25413164);
        EXPECT_TRUE(n >= 2543164);
        EXPECT_TRUE(n <= 25413164);
        EXPECT_TRUE(!(n <= 2543164));
        EXPECT_TRUE(n < 213421164);
        EXPECT_TRUE(!(n == m));
        EXPECT_TRUE(n < m);
        EXPECT_TRUE(m > n);
        EXPECT_TRUE(n <= m);
        EXPECT_TRUE(m >= m);
    }

    TEST(test_mp_nombre, test_abs)
    {
        mp_nombre n(-22632576532575LL);
        mp_nombre m = std::abs(n);
        EXPECT_EQ(m.get_unsigned_long_long(), 22632576532575);

        n = mp_nombre::abs(n);
        EXPECT_EQ(n.get_unsigned_long_long(), 22632576532575);
    }

    TEST(test_mp_nombre, test_soustraction)
    {
        mp_nombre n(22801763489LL);
        mp_nombre m(22632576532575LL);
        n -= m;

        EXPECT_EQ(n, -22609774769086);

        n -= 100;
        EXPECT_EQ(n, -22609774769186);

        n -= m;
        EXPECT_EQ(n, -45242351301761);

        mp_nombre p = n - m;
        EXPECT_EQ(p, -67874927834336);

        mp_nombre q = 42ul - m;
        EXPECT_EQ(q, -22632576532533);

        mp_nombre r = n - 666ul;
        EXPECT_EQ(r, -45242351302427);

        r -= 400000000000000ull;
        EXPECT_EQ(r, -445242351302427);
    }

    TEST(test_mp_nombre, test_multiplication)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(22632572575LL);
        n *= m;

        EXPECT_EQ(n.to_string(), "5160625763047650425");

        n *= 100;
        EXPECT_EQ(n.to_string(), "516062576304765042500");

        n *= m;
        EXPECT_EQ(n.to_string(), "11679823711459070142704209437500");

        mp_nombre p = n * m;
        EXPECT_EQ(p.to_string(), "264344457812803264146768626852218676562500");

        mp_nombre q = 42ul * m;
        EXPECT_EQ(q.to_string(), "950568048150");

        mp_nombre r = n * 666ul;
        EXPECT_EQ(r.to_string(), "7778762591831740715041003485375000");

        r *= 4;
        EXPECT_EQ(r.to_string(), "31115050367326962860164013941500000");
    }

    TEST(test_mp_nombre, test_shift)
    {
        mp_nombre n(228);

        mp_nombre m = n << 10;
        EXPECT_EQ(m, 233472);

        mp_nombre p = n >> 5;
        EXPECT_EQ(p, 7);
    }

    TEST(test_mp_nombre, test_division)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(275LL);
        n /= m;

        EXPECT_EQ(n, 829155);

        n /= 100;
        EXPECT_EQ(n, 8291);

        n/=m;
        EXPECT_EQ(n, 30);

        n.set(2280176);
        mp_nombre p = n / m;
        EXPECT_EQ(p, 8291);

        mp_nombre q = 42000000000000ul / m;
        EXPECT_EQ(q, 152727272727);

        mp_nombre r = n / 666ul;
        EXPECT_EQ(r, 3423);

        r /= 4;
        EXPECT_EQ(r, 855);
    }

    TEST(test_mp_nombre, test_modulo)
    {
        mp_nombre n(228017639LL);
        mp_nombre m(275LL);
        n %= m;

        EXPECT_EQ(n, 14);

        n %= 10;
        EXPECT_EQ(n, 4);

        n.set(2280176);
        n %= m;
        EXPECT_EQ(n, 151);

        n.set(2280176);
        mp_nombre p = n % m;
        EXPECT_EQ(p, 151);

        mp_nombre q = 42000000000000ul % m;
        EXPECT_EQ(q, 75);

        unsigned long r = n % 666ul;
        EXPECT_EQ(r, 458);

        r %= 4;
        EXPECT_EQ(r, 2);
    }

    TEST(test_mp_nombre, test_divisible)
    {
        mp_nombre n(228017635LL);
        mp_nombre m(275LL);

        EXPECT_EQ(mp_nombre::divisible(n, m), false);
        EXPECT_EQ(mp_nombre::divisible(n, 5), true);
        EXPECT_EQ(mp_nombre::divisible(2750000, m), true);
    }

    TEST(test_mp_nombre, test_puissance)
    {
        mp_nombre n(24);
        n = mp_nombre::puissance(n, 10);

        EXPECT_EQ(n, 63403380965376);

        n = mp_nombre::puissance_modulaire(n, 5, 1000);
        EXPECT_EQ(n, 376);

        mp_nombre m = mp_nombre::puissance(9, 10);
        EXPECT_EQ(m, 3486784401);

        mp_nombre p = mp_nombre::puissance_modulaire(m, 100000, 1024);
        EXPECT_EQ(p, 513);
    }

    TEST(test_mp_nombre, test_racine)
    {
        mp_nombre n(63403380965376);
        EXPECT_EQ(mp_nombre::carre_parfait(n), true);

        mp_nombre m = mp_nombre::racine_carre(n);
        EXPECT_EQ(m, 7962624);
        EXPECT_EQ(mp_nombre::carre_parfait(m), false);

        mp_nombre p = mp_nombre::racine(n, 10);
        EXPECT_EQ(p, 24);

        mp_nombre q = std::sqrt(n);
        EXPECT_EQ(q, 7962624);

        mp_nombre r = std::cbrt(n);
        EXPECT_EQ(r, 39875);
    }

    TEST(test_mp_nombre, test_premier)
    {
        mp_nombre n(22801763489);
        EXPECT_TRUE(mp_nombre::premier(n));

        n *= 10;
        EXPECT_TRUE(!mp_nombre::premier(n));

        mp_nombre m = mp_nombre::premier_suivant(n);
        EXPECT_EQ(m, 228017634893);
        EXPECT_TRUE(mp_nombre::premier(m));
    }

    TEST(test_mp_nombre, test_stream)
    {
        std::ostringstream oss;
        mp_nombre n(22801763489);
        oss << n;

        std::istringstream iss(oss.str());
        mp_nombre m;
        iss >> m;

        EXPECT_EQ(n, m);
    }

    TEST(test_mp_nombre, test_logique)
    {
        mp_nombre n("10110000111000101", 2);
        mp_nombre m("10111110001010000", 2);

        mp_nombre n_and = n & m;
        mp_nombre n_or = n | m;
        mp_nombre n_xor = n ^ m;
        mp_nombre n_not = ~n;

        EXPECT_EQ(n_and.to_string(2), "10110000001000000");
        EXPECT_EQ(n_or.to_string(2), "10111110111010101");
        EXPECT_EQ(n_xor.to_string(2), "1110110010101");
        EXPECT_EQ(n_not.to_string(2), "-10110000111000110");
    }

    TEST(test_mp_nombre, test_pgcd)
    {
        mp_nombre n(456753);
        mp_nombre m(97643);
        mp_nombre p(158665);

        EXPECT_EQ(mp_nombre::PGCD(n, m), 1);
        EXPECT_EQ(mp_nombre::PGCD(p, 456755), 65);
    }

    TEST(test_mp_nombre, test_ppcm)
    {
        mp_nombre n(456753u);
        mp_nombre m(97643u);
        mp_nombre p(158665u);

        EXPECT_EQ(mp_nombre::PPCM(n, m), 44598733179);
        EXPECT_EQ(mp_nombre::PPCM(p, 456755), 1114938955);
    }

    TEST(test_mp_nombre, test_chiffres)
    {
        mp_nombre n("31115050367326962860164013941500001");

        std::deque<unsigned long int> chiffres;
        n.boucle_chiffre([&chiffres] (unsigned long int d) { chiffres.push_front(d); });

        const std::vector<unsigned long int> resultat {
                3,1,1,1,5,0,5,0,3,6,7,3,2,6,9,6,2,8,6,0,1,6,4,0,1,3,9,4,1,5,0,0,0,0,1
        };

        EXPECT_EQ_COLLECTIONS(resultat.begin(), resultat.end(), chiffres.begin(), chiffres.end());

        EXPECT_EQ(n.nombre_chiffres(), 35);
        EXPECT_EQ(n.somme_chiffres(14), 198);

        auto ec = n.extraire_chiffres();
        EXPECT_EQ_COLLECTIONS(resultat.begin(), resultat.end(), ec.begin(), ec.end());

        EXPECT_EQ(n.inverser_nombre(), "10000514931046106826962376305051113");
        EXPECT_TRUE(!n.palindrome());
        mp_nombre m("89123457675432198");
        EXPECT_TRUE(m.palindrome());
    }
