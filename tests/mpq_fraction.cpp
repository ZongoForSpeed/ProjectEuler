#include <boost/test/unit_test.hpp>

#include "mpq_fraction.h"

BOOST_AUTO_TEST_SUITE(test_mpq_nombre)

    BOOST_AUTO_TEST_CASE(test_constructeur)
    {
        mpq_fraction n1;
        mpq_fraction n2(42ul, 13ul);
        mpq_fraction n3(-666l, 60l);
        mpq_fraction n4(3.14158);
        mpq_fraction n5(22801763489l, 1l);
        mpq_fraction n7("22801763489/11");

        BOOST_CHECK_EQUAL(n1.get_double(), 0.0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "101010/1101");
        BOOST_CHECK_EQUAL(n3.to_string(6), "-303/14");
        BOOST_CHECK_EQUAL(n4.get_double(), 3.14158);
        BOOST_CHECK_EQUAL(n5.to_string(), "22801763489");
        BOOST_CHECK_EQUAL(n7.to_string(), "22801763489/11");
    }

    BOOST_AUTO_TEST_CASE(test_assignation)
    {
        mpq_fraction n;
        BOOST_CHECK_EQUAL(n, 0);

        n.set(42ul);
        BOOST_CHECK_EQUAL(n.to_string(2), "101010");

        n.set(-666l);
        BOOST_CHECK_EQUAL(n.to_string(6), "-3030");

        n.set(3.0);
        BOOST_CHECK_EQUAL(n.to_string(), "3");

        n.set(-22801763489l);
        BOOST_CHECK_EQUAL(n, -22801763489);

        n.set("228017634890", 10);
        BOOST_CHECK_EQUAL(n, 228017634890);

        mpq_fraction m(-2263252575l, 4567876543ul);
        std::swap(n, m);
        BOOST_CHECK_EQUAL(m.to_string(), "228017634890");
        BOOST_CHECK_EQUAL(n.to_string(), "-2263252575/4567876543");

        n.swap(m);
        BOOST_CHECK_EQUAL(m.to_string(), "-2263252575/4567876543");
        BOOST_CHECK_EQUAL(n.to_string(), "228017634890");
    }


    BOOST_AUTO_TEST_CASE(test_addition)
    {
        mpq_fraction n(22801763489LL);
        mpq_fraction m(22632576532575LL);
        n += m;

        BOOST_CHECK_EQUAL(n, 22655378296064);

        n += 100;
        BOOST_CHECK_EQUAL(n, 22655378296164);

        n += m;
        BOOST_CHECK_EQUAL(n, 45287954828739);

        mpq_fraction p = n + m;
        BOOST_CHECK_EQUAL(p, 67920531361314);

        mpq_fraction q = 42ul + m;
        BOOST_CHECK_EQUAL(q, 22632576532617);

        mpq_fraction r = n + 666ul;
        BOOST_CHECK_EQUAL(r, 45287954829405);

        r += 400000000000000ull;
        BOOST_CHECK_EQUAL(r, 445287954829405);
    }

    BOOST_AUTO_TEST_CASE(test_negation)
    {
        mpz_nombre n(22632576532575LL);
        mpz_nombre m = -n;
        BOOST_CHECK_EQUAL(m, -22632576532575);

        m.negation();
        BOOST_CHECK_EQUAL(m, 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_comparaison)
    {
        mpz_nombre n (25413164);
        mpz_nombre m (22632576532575);

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
        mpq_fraction n(-22632576532575LL);
        mpq_fraction m = std::abs(n);
        BOOST_CHECK_EQUAL(m.get_double(), 22632576532575);

        n = mpq_fraction::abs(n);
        BOOST_CHECK_EQUAL(m.get_double(), 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_soustraction)
    {
        mpq_fraction n(22801763489LL);
        mpq_fraction m(22632576532575LL);
        n -= m;

        BOOST_CHECK_EQUAL(n, -22609774769086);

        n -= 100;
        BOOST_CHECK_EQUAL(n, -22609774769186);

        n -= m;
        BOOST_CHECK_EQUAL(n, -45242351301761);

        mpq_fraction p = n - m;
        BOOST_CHECK_EQUAL(p, -67874927834336);

        mpq_fraction q = 42ul - m;
        BOOST_CHECK_EQUAL(q, -22632576532533);

        mpq_fraction r = n - 666ul;
        BOOST_CHECK_EQUAL(r, -45242351302427);

        r -= 400000000000000ull;
        BOOST_CHECK_EQUAL(r, -445242351302427);
    }

    BOOST_AUTO_TEST_CASE(test_multiplication)
    {
        mpq_fraction n(228017639LL);
        mpq_fraction m(22632572575LL);
        n *= m;

        BOOST_CHECK_EQUAL(n.to_string(), "5160625763047650425");

        n *= 100;
        BOOST_CHECK_EQUAL(n.to_string(), "516062576304765042500");

        n *= m;
        BOOST_CHECK_EQUAL(n.to_string(), "11679823711459070142704209437500");

        mpq_fraction p = n * m;
        BOOST_CHECK_EQUAL(p.to_string(), "264344457812803264146768626852218676562500");

        mpq_fraction q = 42ul * m;
        BOOST_CHECK_EQUAL(q.to_string(), "950568048150");

        mpq_fraction r = n * 666ul;
        BOOST_CHECK_EQUAL(r.to_string(), "7778762591831740715041003485375000");

        r *= 4;
        BOOST_CHECK_EQUAL(r.to_string(), "31115050367326962860164013941500000");
    }

    BOOST_AUTO_TEST_CASE(test_division)
    {
        mpq_fraction n(2280176390LL);
        mpq_fraction m(275LL);
        n /= m;

        BOOST_CHECK_EQUAL(n.numerateur(), 456035278);
        BOOST_CHECK_EQUAL(n.denominateur(), 55);

        n /= 100;
        BOOST_CHECK_EQUAL(n.numerateur(), 228017639);
        BOOST_CHECK_EQUAL(n.denominateur(), 2750);

        n/=m;
        BOOST_CHECK_EQUAL(n.numerateur(), 228017639);
        BOOST_CHECK_EQUAL(n.denominateur(), 756250);

        n.set(2280176l);
        mpq_fraction p = n / m;
        BOOST_CHECK_EQUAL(p.numerateur(), 2280176);
        BOOST_CHECK_EQUAL(p.denominateur(), 275);

        mpq_fraction q = 42000000000000ul / m;
        BOOST_CHECK_EQUAL(q.numerateur(), 1680000000000);
        BOOST_CHECK_EQUAL(q.denominateur(), 11);

        mpq_fraction r = n / 666ul;
        BOOST_CHECK_EQUAL(r.numerateur(), 1140088);
        BOOST_CHECK_EQUAL(r.denominateur(), 333);

        r /= 4;
        BOOST_CHECK_EQUAL(r.numerateur(), 285022);
        BOOST_CHECK_EQUAL(r.denominateur(), 333);
    }

    BOOST_AUTO_TEST_CASE(test_stream)
    {
        std::ostringstream oss;
        mpq_fraction n(22801763489);
        oss << n;

        std::istringstream iss(oss.str());
        mpz_nombre m;
        iss >> m;

        BOOST_CHECK_EQUAL(n, m);
    }


BOOST_AUTO_TEST_SUITE_END()
