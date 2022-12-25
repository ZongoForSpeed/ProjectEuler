#include <boost/test/unit_test.hpp>
#include <random>

#include "utilitaires.h"
#include "mpz_nombre.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_mpz_nombre)

    BOOST_AUTO_TEST_CASE(test_constructeur) {
        mpz_nombre n1;
        mpz_nombre n2(42);
        mpz_nombre n3(-666);
        mpz_nombre n4(3.14158);
        mpz_nombre n5(22801763489LL);
        mpz_nombre n7("22801763489");

        BOOST_CHECK_EQUAL(n1.get_signed_long(), 0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "101010");
        BOOST_CHECK_EQUAL(n3.to_string(6), "-3030");
        BOOST_CHECK_EQUAL(n4.get_signed_long(), 3);
        BOOST_CHECK_EQUAL(n5.to_string(), "22801763489");
        BOOST_CHECK_EQUAL(n7, 22801763489);
    }

    BOOST_AUTO_TEST_CASE(test_assignation) {
        mpz_nombre n;
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

    }

    BOOST_AUTO_TEST_CASE(test_swap) {
        mpz_nombre n(228017634890);
        mpz_nombre m(-22632576532575);
        std::swap(n, m);
        BOOST_CHECK_EQUAL(m, 228017634890);
        BOOST_CHECK_EQUAL(n, -22632576532575);

        n.swap(m);
        BOOST_CHECK_EQUAL(m, -22632576532575);
        BOOST_CHECK_EQUAL(n, 228017634890);

        std::vector<mpz_nombre> v;
        for (size_t k = 0; k <= 12; ++k) {
            v.push_back(mpz_nombre::catalan(k));
        }

        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(v.begin(), v.end(), g);

        std::sort(v.begin(), v.end());

        std::cout << v << std::endl;
    }

    BOOST_AUTO_TEST_CASE(test_addition) {
        mpz_nombre n(22801763489LL);
        mpz_nombre m(22632576532575LL);
        n += m;

        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296064);

        n += 100;
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22655378296164);

        n += m;
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 45287954828739);

        mpz_nombre p = n + m;
        BOOST_CHECK_EQUAL(p.get_unsigned_long_long(), 67920531361314);

        mpz_nombre q = 42ul + m;
        BOOST_CHECK_EQUAL(q.get_unsigned_long_long(), 22632576532617);

        mpz_nombre r = n + 666ul;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 45287954829405);

        r += 400000000000000ull;
        BOOST_CHECK_EQUAL(r.get_unsigned_long_long(), 445287954829405);
    }

    BOOST_AUTO_TEST_CASE(test_negation) {
        mpz_nombre n(22632576532575LL);
        mpz_nombre m = -n;
        BOOST_CHECK_EQUAL(m, -22632576532575);

        m.negation();
        BOOST_CHECK_EQUAL(m, 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_comparaison) {
        mpz_nombre n(25413164);
        mpz_nombre m(22632576532575);

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

    BOOST_AUTO_TEST_CASE(test_abs) {
        mpz_nombre n(-22632576532575LL);
        mpz_nombre m = std::abs(n);
        BOOST_CHECK_EQUAL(m.get_unsigned_long_long(), 22632576532575);

        mpz_nombre::abs(n, n);
        BOOST_CHECK_EQUAL(n.get_unsigned_long_long(), 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_soustraction) {
        mpz_nombre n(22801763489LL);
        mpz_nombre m(22632576532575LL);
        n -= m;

        BOOST_CHECK_EQUAL(n, -22609774769086);

        n -= 100;
        BOOST_CHECK_EQUAL(n, -22609774769186);

        n -= m;
        BOOST_CHECK_EQUAL(n, -45242351301761);

        mpz_nombre p = n - m;
        BOOST_CHECK_EQUAL(p, -67874927834336);

        mpz_nombre q = 42ul - m;
        BOOST_CHECK_EQUAL(q, -22632576532533);

        mpz_nombre r = n - 666ul;
        BOOST_CHECK_EQUAL(r, -45242351302427);

        r -= 400000000000000ull;
        BOOST_CHECK_EQUAL(r, -445242351302427);
    }

    BOOST_AUTO_TEST_CASE(test_multiplication) {
        mpz_nombre n(228017639LL);
        mpz_nombre m(22632572575LL);
        n *= m;

        BOOST_CHECK_EQUAL(n.to_string(), "5160625763047650425");

        n *= 100;
        BOOST_CHECK_EQUAL(n.to_string(), "516062576304765042500");

        n *= m;
        BOOST_CHECK_EQUAL(n.to_string(), "11679823711459070142704209437500");

        mpz_nombre p = n * m;
        BOOST_CHECK_EQUAL(p.to_string(), "264344457812803264146768626852218676562500");

        mpz_nombre q = 42ul * m;
        BOOST_CHECK_EQUAL(q.to_string(), "950568048150");

        mpz_nombre r = n * 666ul;
        BOOST_CHECK_EQUAL(r.to_string(), "7778762591831740715041003485375000");

        r *= 4;
        BOOST_CHECK_EQUAL(r.to_string(), "31115050367326962860164013941500000");
    }

    BOOST_AUTO_TEST_CASE(test_shift) {
        mpz_nombre n(228);

        mpz_nombre m = n << 10;
        BOOST_CHECK_EQUAL(m, 233472);

        mpz_nombre p = n >> 5;
        BOOST_CHECK_EQUAL(p, 7);
    }

    BOOST_AUTO_TEST_CASE(test_division) {
        mpz_nombre n(228017639LL);
        mpz_nombre m(275LL);
        n /= m;

        BOOST_CHECK_EQUAL(n, 829155);

        n /= 100;
        BOOST_CHECK_EQUAL(n, 8291);

        n /= m;
        BOOST_CHECK_EQUAL(n, 30);

        n.set(2280176);
        mpz_nombre p = n / m;
        BOOST_CHECK_EQUAL(p, 8291);

        mpz_nombre q = 42000000000000ul / m;
        BOOST_CHECK_EQUAL(q, 152727272727);

        mpz_nombre r = n / 666ul;
        BOOST_CHECK_EQUAL(r, 3423);

        r /= 4;
        BOOST_CHECK_EQUAL(r, 855);
    }

    BOOST_AUTO_TEST_CASE(test_modulo) {
        mpz_nombre n(228017639LL);
        mpz_nombre m(275LL);
        n %= m;

        BOOST_CHECK_EQUAL(n, 14);

        n %= 10;
        BOOST_CHECK_EQUAL(n, 4);

        n.set(2280176);
        n %= m;
        BOOST_CHECK_EQUAL(n, 151);

        n.set(2280176);
        mpz_nombre p = n % m;
        BOOST_CHECK_EQUAL(p, 151);

        mpz_nombre q = 42000000000000ul % m;
        BOOST_CHECK_EQUAL(q, 75);

        unsigned long r = n % 666ul;
        BOOST_CHECK_EQUAL(r, 458);

        r %= 4;
        BOOST_CHECK_EQUAL(r, 2);
    }

    BOOST_AUTO_TEST_CASE(test_divisible) {
        mpz_nombre n(228017635LL);
        mpz_nombre m(275LL);

        BOOST_CHECK_EQUAL(mpz_nombre::divisible(n, m), false);
        BOOST_CHECK_EQUAL(mpz_nombre::divisible(n, 5), true);
        BOOST_CHECK_EQUAL(mpz_nombre::divisible(2750000, m), true);
    }

    BOOST_AUTO_TEST_CASE(test_puissance) {
        mpz_nombre n(24);
        n = mpz_nombre::puissance(n, 10);

        BOOST_CHECK_EQUAL(n, 63403380965376);

        n = mpz_nombre::puissance_modulaire(n, 5, 1000);
        BOOST_CHECK_EQUAL(n, 376);

        mpz_nombre m = mpz_nombre::puissance(9, 10);
        BOOST_CHECK_EQUAL(m, 3486784401);

        mpz_nombre p = mpz_nombre::puissance_modulaire(m, 100000, 1024);
        BOOST_CHECK_EQUAL(p, 513);
    }

    BOOST_AUTO_TEST_CASE(test_racine) {
        mpz_nombre n(63403380965376);
        BOOST_CHECK_EQUAL(mpz_nombre::carre_parfait(n), true);

        mpz_nombre m;
        mpz_nombre::racine_carre(m, n);
        BOOST_CHECK_EQUAL(m, 7962624);
        BOOST_CHECK_EQUAL(mpz_nombre::carre_parfait(m), false);

        mpz_nombre p;
        mpz_nombre::racine(p, n, 10);
        BOOST_CHECK_EQUAL(p, 24);

        mpz_nombre q = std::sqrt(n);
        BOOST_CHECK_EQUAL(q, 7962624);

        mpz_nombre r = std::cbrt(n);
        BOOST_CHECK_EQUAL(r, 39875);
    }

    BOOST_AUTO_TEST_CASE(test_premier_1) {
        mpz_nombre n(22801763489);
        BOOST_CHECK(mpz_nombre::premier(n));

        n *= 10;
        BOOST_CHECK(!mpz_nombre::premier(n));

        mpz_nombre m;
        mpz_nombre::premier_suivant(m, n);
        BOOST_CHECK_EQUAL(m, 228017634893);
        BOOST_CHECK(mpz_nombre::premier(m));
    }

    BOOST_AUTO_TEST_CASE(test_premier_2) {
        mpz_nombre n("32416189721");
        BOOST_CHECK(mpz_nombre::premier(n, 25));
        BOOST_CHECK(n.premier());
        BOOST_CHECK_EQUAL(false, mpz_nombre::premier(n + 44, 25));

        mpz_nombre m("2305843009213693951");
        BOOST_CHECK(mpz_nombre::premier(m, 25));
        BOOST_CHECK_EQUAL(false, mpz_nombre::premier(m + 44, 25));

        BOOST_CHECK_EQUAL(false, mpz_nombre::premier(n * m, 25));
        BOOST_CHECK_EQUAL(false, mpz_nombre::premier(n * m - 2, 25));

        mpz_nombre p("170141183460469231731687303715884105727");
        BOOST_CHECK(mpz_nombre::premier(p, 25));
        BOOST_CHECK_EQUAL(false, mpz_nombre::premier(p - 2, 25));
    }

    BOOST_AUTO_TEST_CASE(test_suivant) {
        mpz_nombre r("170141183460469231731687303715884105757");
        mpz_nombre q("170141183460469231731687303715884105727");
        mpz_nombre p;
        mpz_nombre::premier_suivant(p, q);
        BOOST_CHECK_EQUAL(r, p);
        for (mpz_nombre i = q + 2; i < r; i += 2) {
            BOOST_CHECK_EQUAL(false, mpz_nombre::premier(i, 25));
        }
    }

    BOOST_AUTO_TEST_CASE(test_stream) {
        std::ostringstream oss;
        mpz_nombre n(22801763489);
        oss << n;

        std::istringstream iss(oss.str());
        mpz_nombre m;
        iss >> m;

        BOOST_CHECK_EQUAL(n, m);
    }

    BOOST_AUTO_TEST_CASE(test_logique) {
        mpz_nombre n("10110000111000101", 2);
        mpz_nombre m("10111110001010000", 2);

        mpz_nombre n_and = n & m;
        mpz_nombre n_or = n | m;
        mpz_nombre n_xor = n ^ m;
        mpz_nombre n_not = ~n;

        BOOST_CHECK_EQUAL(n_and.to_string(2), "10110000001000000");
        BOOST_CHECK_EQUAL(n_or.to_string(2), "10111110111010101");
        BOOST_CHECK_EQUAL(n_xor.to_string(2), "1110110010101");
        BOOST_CHECK_EQUAL(n_not.to_string(2), "-10110000111000110");
    }

    BOOST_AUTO_TEST_CASE(test_pgcd) {
        mpz_nombre n(456753);
        mpz_nombre m(97643);
        mpz_nombre p(158665);

        BOOST_CHECK_EQUAL(mpz_nombre::PGCD(n, m), 1);
        BOOST_CHECK_EQUAL(mpz_nombre::PGCD(p, 456755ul), 65);
    }

    BOOST_AUTO_TEST_CASE(test_ppcm) {
        mpz_nombre n(456753u);
        mpz_nombre m(97643u);
        mpz_nombre p(158665u);

        BOOST_CHECK_EQUAL(mpz_nombre::PPCM(n, m), 44598733179);
        BOOST_CHECK_EQUAL(mpz_nombre::PPCM(p, 456755ul), 1114938955);
    }

    BOOST_AUTO_TEST_CASE(test_chiffres) {
        mpz_nombre n("31115050367326962860164013941500001");

        std::deque<unsigned long int> chiffres;
        n.boucle_chiffre([&chiffres](unsigned long int d) { chiffres.push_front(d); });

        const std::vector<unsigned long int> resultat{
                3, 1, 1, 1, 5, 0, 5, 0, 3, 6, 7, 3, 2, 6, 9, 6, 2, 8, 6, 0, 1, 6, 4, 0, 1, 3, 9, 4, 1, 5, 0, 0, 0, 0, 1
        };

        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), chiffres.begin(), chiffres.end());

        BOOST_CHECK_EQUAL(n.nombre_chiffres(), 35);
        BOOST_CHECK_EQUAL(n.somme_chiffres(14), 198);

        auto ec = n.extraire_chiffres();
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), ec.begin(), ec.end());

        BOOST_CHECK_EQUAL(n.inverser_nombre().to_string(), "10000514931046106826962376305051113");
        BOOST_CHECK(!n.palindrome());
        mpz_nombre m("89123457675432198");
        BOOST_CHECK(m.palindrome());
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
