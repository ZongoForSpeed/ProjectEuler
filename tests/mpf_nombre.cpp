#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "mpf_nombre.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

#define EPSILON 0.000000001l

BOOST_AUTO_TEST_SUITE(test_mpf_nombre)

    BOOST_AUTO_TEST_CASE(test_constructeur) {
        mpf_nombre n1;
        mpf_nombre n2(42l);
        mpf_nombre n3(-666l);
        mpf_nombre n4(3.14158);
        mpf_nombre n5(22801763489l);
        mpf_nombre n7("22801763489");

        BOOST_CHECK_EQUAL(n1.get_signed_long(), 0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "42");
        BOOST_CHECK_EQUAL(n3.to_string(6), "-666");
        BOOST_CHECK_EQUAL(n4.get_signed_long(), 3);
        BOOST_CHECK_EQUAL(n5.to_string(), "22801763489");
        BOOST_CHECK_EQUAL(n7.get_signed_long(), 22801763489);
    }

    BOOST_AUTO_TEST_CASE(test_assignation) {
        mpf_nombre n(0);
        BOOST_CHECK_CLOSE(n, 0, EPSILON);

        n.set(42l);
        BOOST_CHECK_CLOSE(n, 42, EPSILON);

        n.set(-666l);
        BOOST_CHECK_CLOSE(n, -666, EPSILON);

        n.set(3.14158);
        BOOST_CHECK_CLOSE(n, 3.14158, EPSILON);

        n.set(-22801763489L);
        BOOST_CHECK_CLOSE(n, -22801763489, EPSILON);

        n.set("228017634890", 10);
        BOOST_CHECK_CLOSE(n, 228017634890, EPSILON);

        mpf_nombre m(-22632576532575);
        std::swap(n, m);
        BOOST_CHECK_CLOSE(m, 228017634890, EPSILON);
        BOOST_CHECK_CLOSE(n, -2.26325765326e+13, EPSILON);

        n.swap(m);
        BOOST_CHECK_CLOSE(m, -2.26325765326e+13, EPSILON);
        BOOST_CHECK_CLOSE(n, 228017634890, EPSILON);
    }


    BOOST_AUTO_TEST_CASE(test_addition) {
        mpf_nombre n(228017634.89);
        mpf_nombre m(2263257.6532575l);
        n += m;

        BOOST_CHECK_CLOSE(n.get_long_double(), 230280892.543257474899, EPSILON);

        n += 100;
        BOOST_CHECK_CLOSE(n.get_long_double(), 230280992.543257474899, EPSILON);

        n += m;
        BOOST_CHECK_CLOSE(n.get_long_double(), 232544250.196514964104, EPSILON);

        mpf_nombre p = n + m;
        BOOST_CHECK_CLOSE(p.get_long_double(), 234807507.849772464018, EPSILON);

        mpf_nombre q = 42ul + m;
        BOOST_CHECK_CLOSE(q.get_long_double(), 2263299.65325749991462, EPSILON);

        mpf_nombre r = n + 666ul;
        BOOST_CHECK_CLOSE(r.get_long_double(), 232544916.196514964104, EPSILON);

        r += 400000000000000ull;
        BOOST_CHECK_CLOSE(r.get_long_double(), 400000232544916.196503, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(test_negation) {
        mpf_nombre n(22632576532575LL);
        mpf_nombre m = -n;
        BOOST_CHECK_CLOSE(m, -22632576532575, EPSILON);

    }

    BOOST_AUTO_TEST_CASE(test_comparaison) {
        mpf_nombre n(25413164);
        mpf_nombre m(22632576532575);

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
        mpf_nombre n(-22632576532575LL);
        mpf_nombre m = std::abs(n);
        BOOST_CHECK_CLOSE(m, 22632576532575, EPSILON);

        mpf_nombre::abs(n, n);
        BOOST_CHECK_CLOSE(n, 22632576532575, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(test_soustraction) {
        mpf_nombre n(22801763489LL);
        mpf_nombre m(22632576532575LL);
        n -= m;

        BOOST_CHECK_CLOSE(n, -22609774769086, EPSILON);

        n -= 100;
        BOOST_CHECK_CLOSE(n, -22609774769186, EPSILON);

        n -= m;
        BOOST_CHECK_CLOSE(n, -45242351301761, EPSILON);

        mpf_nombre p = n - m;
        BOOST_CHECK_CLOSE(p, -67874927834336, EPSILON);

        mpf_nombre q = 42ul - m;
        BOOST_CHECK_CLOSE(q, -22632576532533, EPSILON);

        mpf_nombre r = n - 666ul;
        BOOST_CHECK_CLOSE(r, -45242351302427, EPSILON);

        r -= 400000000000000ull;
        BOOST_CHECK_CLOSE(r, -445242351302427, EPSILON);
    }


    BOOST_AUTO_TEST_CASE(test_multiplication) {
        mpf_nombre n(228017639LL);
        mpf_nombre m(22632572575LL);
        n *= m;

        BOOST_CHECK_CLOSE(n, 5.16062576305e+18, EPSILON);

        n *= 100;
        BOOST_CHECK_CLOSE(n, 5.16062576305e+20, EPSILON);

        n *= m;
        BOOST_CHECK_CLOSE(n, 1.16798237115e+31, EPSILON);

        mpf_nombre p = n * m;
        BOOST_CHECK_CLOSE(p, 2.64344457813e+41, EPSILON);

        mpf_nombre q = 42ul * m;
        BOOST_CHECK_CLOSE(q, 950568048150, EPSILON);

        mpf_nombre r = n * 666ul;
        BOOST_CHECK_CLOSE(r, 7.77876259183e+33, EPSILON);

        r *= 4;
        BOOST_CHECK_CLOSE(r, 3.11150503673e+34, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(test_division) {
        mpf_nombre n(228017639LL);
        mpf_nombre m(275LL);
        n /= m;

        BOOST_CHECK_CLOSE(n, 829155.050909, EPSILON);

        n /= 100;
        BOOST_CHECK_CLOSE(n, 8291.55050909, EPSILON);

        n /= m;
        BOOST_CHECK_CLOSE(n, 30.1510927603, EPSILON);

        n.set(2280176);
        mpf_nombre p = n / m;
        BOOST_CHECK_CLOSE(p, 8291.54909091, EPSILON);

        mpf_nombre q = 42000000000000ul / m;
        BOOST_CHECK_CLOSE(q, 152727272727, EPSILON);

        mpf_nombre r = n / 666ul;
        BOOST_CHECK_CLOSE(r, 3423.68768769, EPSILON);

        r /= 4;
        BOOST_CHECK_CLOSE(r, 855.921921922, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(test_constant) {
        BOOST_CHECK_CLOSE(mpf_nombre::pi(), M_PIl, EPSILON);
        BOOST_CHECK_CLOSE(mpf_nombre::e(), M_El, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(test_trigo) {
        BOOST_CHECK_CLOSE(std::cos(mpf_nombre::pi() / 3), 0.5l, EPSILON);
        BOOST_CHECK_CLOSE(std::sin(mpf_nombre::pi() / 3), 0.866025403784, EPSILON);

        mpf_nombre sin_pi_3;
        mpf_nombre::sin(sin_pi_3, mpf_nombre::pi() / 3);
        mpf_nombre sqrt3_2;
        mpf_nombre::racine_carre(sqrt3_2, 0.75);
        BOOST_CHECK_CLOSE(sin_pi_3, sqrt3_2, EPSILON);

    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
