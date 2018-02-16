#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "mp_decimal.h"

class fixture_mp_decimal {
public:
    fixture_mp_decimal() {
        mp_decimal::init();
    }

    ~fixture_mp_decimal() {
        mp_decimal::clear();
    }
};

BOOST_FIXTURE_TEST_SUITE(test_mp_decimal, fixture_mp_decimal)

    BOOST_AUTO_TEST_CASE(test_constructeur)
    {
        mp_decimal n1;
        mp_decimal n2("101010", 2);
        mp_decimal n3(-666l);
        mp_decimal n4(3.14158);
        mp_decimal n5(22'801'763'489l);
        mp_decimal n7("22801763489");

        BOOST_CHECK_EQUAL(n1.get_long(), 0);
        BOOST_CHECK_EQUAL(n2.to_string(2), "42");
        BOOST_CHECK_EQUAL(n3.get_long(), -666l);
        BOOST_CHECK_EQUAL(n4.get_long(), 3);
        BOOST_CHECK_EQUAL(n5.to_string(0), "2e+10");
        BOOST_CHECK_EQUAL(n7, 22801763489);
    }
    
    BOOST_AUTO_TEST_CASE(test_assignation)
    {
        mp_decimal n;
        BOOST_CHECK_EQUAL(n, 0);

        n.set("101010", 2);
        BOOST_CHECK_EQUAL(n.to_string(2), "42");
        
        n.set(-666l);
        BOOST_CHECK_EQUAL(n.get_long(), -666l);
        
        n.set(3.14158);
        BOOST_CHECK_EQUAL(n.to_string(6), "3.14158");

        n.set(-22'801'763'489l);
        BOOST_CHECK_EQUAL(n, -22801763489);
        
        n.set("228017634890", 10);
        BOOST_CHECK_EQUAL(n, 228017634890);

        mp_decimal m(-22632576532575);
        std::swap(n, m);
        BOOST_CHECK_EQUAL(m.to_string(12), "228017634890");
        BOOST_CHECK_EQUAL(n.to_string(14), "-22632576532575");

        n.swap(m);
        BOOST_CHECK_EQUAL(m.to_string(14), "-22632576532575");
        BOOST_CHECK_EQUAL(n.to_string(12), "228017634890");
    }


    BOOST_AUTO_TEST_CASE(test_comparaison)
    {
        mp_decimal n (250987654413.11234567864l);
        mp_decimal m ("226312345678925765.325326787654321234567898575");

        BOOST_CHECK(n == n);
        BOOST_CHECK(n != 2543164);
        BOOST_CHECK(n > 25164);
        BOOST_CHECK(n >= 25413164);
        BOOST_CHECK(n >= 2543164);
        BOOST_CHECK(n <= 250987654413.11234568l);
        BOOST_CHECK(!(n <= 250987654413));
        BOOST_CHECK(n < 250987654413.2);
        BOOST_CHECK(!(n == m));
        BOOST_CHECK(n > m);
        BOOST_CHECK(m < n);
        BOOST_CHECK(n >= m);
        BOOST_CHECK(m <= m);

        BOOST_CHECK_EQUAL(mp_decimal::PI.to_string(100), "3.141592653589793115997963468544185161590576171875");
        BOOST_CHECK_EQUAL(mp_decimal::E.to_string(100), "2.718281828459045090795598298427648842334747314453125");
        BOOST_CHECK_EQUAL(mp_decimal::EULER.to_string(100), "0.57721566490153286554942724251304753124713897705078125");
        BOOST_CHECK_EQUAL(mp_decimal::CATALAN.to_string(100), "0.91596559417721901130704509341740049421787261962890625");
    }


    BOOST_AUTO_TEST_CASE(test_addition)
    {
        mp_decimal n(22801763489LL);
        mp_decimal m(22632576532575LL);
        n += m;

        BOOST_CHECK_EQUAL(n.get<unsigned long long>(), 22655378296064);

        n += 100;
        BOOST_CHECK_EQUAL(n.get<unsigned long long>(), 22655378296164);

        n += m;
        BOOST_CHECK_EQUAL(n.get<unsigned long long>(), 45287954828739);

        mp_decimal p = n + m;
        BOOST_CHECK_EQUAL(p.get<unsigned long long>(), 67920531361314);

        mp_decimal q = 42ul + m;
        BOOST_CHECK_EQUAL(q.get<unsigned long long>(), 22632576532617);

        mp_decimal r = n + 666ul;
        BOOST_CHECK_EQUAL(r.get<unsigned long long>(), 45287954829405);

        r += 400000000000000ull;
        BOOST_CHECK_EQUAL(r.get<unsigned long long>(), 445287954829405);
    }

    BOOST_AUTO_TEST_CASE(test_soustraction)
    {
        mp_decimal n(22801763489LL);
        mp_decimal m(22632576532575LL);
        n -= m;

        BOOST_CHECK_EQUAL(n, -22609774769086);

        n -= 100;
        BOOST_CHECK_EQUAL(n, -22609774769186);

        n -= m;
        BOOST_CHECK_EQUAL(n, -45242351301761);

        mp_decimal p = n - m;
        BOOST_CHECK_EQUAL(p, -67874927834336);

        mp_decimal q = 42ul - m;
        BOOST_CHECK_EQUAL(q, -22632576532533);

        mp_decimal r = n - 666ul;
        BOOST_CHECK_EQUAL(r, -45242351302427);

        r -= 400000000000000ull;
        BOOST_CHECK_EQUAL(r, -445242351302427);
    }



    BOOST_AUTO_TEST_CASE(test_negation)
    {
        mp_decimal n(22632576532575LL);
        mp_decimal m = -n;
        BOOST_CHECK_EQUAL(m, -22632576532575);

        m.negation();
        BOOST_CHECK_EQUAL(m, 22632576532575);
    }

    BOOST_AUTO_TEST_CASE(test_abs)
    {
        mp_decimal n(-22632576532575LL);
        mp_decimal m = std::abs(n);
        BOOST_CHECK_EQUAL(m.get<unsigned long long>(), 22632576532575);

        n = mp_decimal::abs(n);
        BOOST_CHECK_EQUAL(n.get<unsigned long long>(), 22632576532575);
    }


    BOOST_AUTO_TEST_CASE(test_multiplication)
    {
        mp_decimal n(228017639LL);
        mp_decimal m(22632572575LL);
        n *= m;

        BOOST_CHECK_EQUAL(n.to_string(30), "5160625763047650425");

        n *= 100;
        BOOST_CHECK_EQUAL(n.to_string(30), "516062576304765042500");

        n *= m;
        BOOST_CHECK_EQUAL(n.to_string(60), "11679823711459070142704209437500");

        mp_decimal p = n * m;
        BOOST_CHECK_EQUAL(p.to_string(80), "264344457812803264146768626852218676562500");

        mp_decimal q = 42ul * m;
        BOOST_CHECK_EQUAL(q.to_string(20), "950568048150");

        mp_decimal r = n * 666ul;
        BOOST_CHECK_EQUAL(r.to_string(80), "7778762591831740715041003485375000");

        r *= 4;
        BOOST_CHECK_EQUAL(r.to_string(80), "31115050367326962860164013941500000");
    }


    BOOST_AUTO_TEST_CASE(test_division)
    {
        mp_decimal n(228017639LL);
        mp_decimal m(275LL);
        n /= m;

        BOOST_CHECK_EQUAL(n, 829155.05);

        n /= 100;
        BOOST_CHECK_EQUAL(n, 8291.5505);

        n/=m;
        BOOST_CHECK_EQUAL(n, 30.151093);

        n.set(2280176);
        mp_decimal p = n / m;
        BOOST_CHECK_EQUAL(p, 8291.5491);

        mp_decimal q = 42000000000000ul / m;
        BOOST_CHECK_EQUAL(q, 152727272727);

        mp_decimal r = n / 666ul;
        BOOST_CHECK_EQUAL(r, 3423);

        r /= 4;
        BOOST_CHECK_EQUAL(r, 855);
    }



    BOOST_AUTO_TEST_CASE(test_vecteur) {
        std::vector<mp_nombre> Pk{1};
        std::cout << Pk.front() << std::endl;
    }

    /*
    BOOST_AUTO_TEST_CASE(test_shift)
    {
        mp_decimal n(228);

        mp_decimal m = n << 10;
        BOOST_CHECK_EQUAL(m, 233472);

        mp_decimal p = n >> 5;
        BOOST_CHECK_EQUAL(p, 7);
    }


    BOOST_AUTO_TEST_CASE(test_modulo)
    {
        mp_decimal n(228017639LL);
        mp_decimal m(275LL);
        n %= m;

        BOOST_CHECK_EQUAL(n, 14);

        n %= 10;
        BOOST_CHECK_EQUAL(n, 4);

        n.set(2280176);
        n %= m;
        BOOST_CHECK_EQUAL(n, 151);

        n.set(2280176);
        mp_decimal p = n % m;
        BOOST_CHECK_EQUAL(p, 151);

        mp_decimal q = 42000000000000ul % m;
        BOOST_CHECK_EQUAL(q, 75);

        unsigned long r = n % 666ul;
        BOOST_CHECK_EQUAL(r, 458);

        r %= 4;
        BOOST_CHECK_EQUAL(r, 2);
    }

    BOOST_AUTO_TEST_CASE(test_divisible)
    {
        mp_decimal n(228017635LL);
        mp_decimal m(275LL);

        BOOST_CHECK_EQUAL(mp_decimal::divisible(n, m), false);
        BOOST_CHECK_EQUAL(mp_decimal::divisible(n, 5), true);
        BOOST_CHECK_EQUAL(mp_decimal::divisible(2750000, m), true);
    }

    BOOST_AUTO_TEST_CASE(test_puissance)
    {
        mp_decimal n(24);
        n = mp_decimal::puissance(n, 10);

        BOOST_CHECK_EQUAL(n, 63403380965376);

        n = mp_decimal::puissance_modulaire(n, 5, 1000);
        BOOST_CHECK_EQUAL(n, 376);

        mp_decimal m = mp_decimal::puissance(9, 10);
        BOOST_CHECK_EQUAL(m, 3486784401);

        mp_decimal p = mp_decimal::puissance_modulaire(m, 100000, 1024);
        BOOST_CHECK_EQUAL(p, 513);
    }

    BOOST_AUTO_TEST_CASE(test_racine)
    {
        mp_decimal n(63403380965376);
        BOOST_CHECK_EQUAL(mp_decimal::carre_parfait(n), true);

        mp_decimal m = mp_decimal::racine_carre(n);
        BOOST_CHECK_EQUAL(m, 7962624);
        BOOST_CHECK_EQUAL(mp_decimal::carre_parfait(m), false);

        mp_decimal p = mp_decimal::racine(n, 10);
        BOOST_CHECK_EQUAL(p, 24);

        mp_decimal q = std::sqrt(n);
        BOOST_CHECK_EQUAL(q, 7962624);

        mp_decimal r = std::cbrt(n);
        BOOST_CHECK_EQUAL(r, 39875);
    }

    BOOST_AUTO_TEST_CASE(test_premier)
    {
        mp_decimal n(22801763489);
        BOOST_CHECK(mp_decimal::premier(n));

        n *= 10;
        BOOST_CHECK(!mp_decimal::premier(n));

        mp_decimal m = mp_decimal::premier_suivant(n);
        BOOST_CHECK_EQUAL(m, 228017634893);
        BOOST_CHECK(mp_decimal::premier(m));
    }

    BOOST_AUTO_TEST_CASE(test_stream)
    {
        std::ostringstream oss;
        mp_decimal n(22801763489);
        oss << n;

        std::istringstream iss(oss.str());
        mp_decimal m;
        iss >> m;

        BOOST_CHECK_EQUAL(n, m);
    }

    BOOST_AUTO_TEST_CASE(test_logique)
    {
        mp_decimal n("10110000111000101", 2);
        mp_decimal m("10111110001010000", 2);

        mp_decimal n_and = n & m;
        mp_decimal n_or = n | m;
        mp_decimal n_xor = n ^ m;
        mp_decimal n_not = ~n;

        BOOST_CHECK_EQUAL(n_and.to_string(2), "10110000001000000");
        BOOST_CHECK_EQUAL(n_or.to_string(2), "10111110111010101");
        BOOST_CHECK_EQUAL(n_xor.to_string(2), "1110110010101");
        BOOST_CHECK_EQUAL(n_not.to_string(2), "-10110000111000110");
    }

    BOOST_AUTO_TEST_CASE(test_pgcd)
    {
        mp_decimal n(456753);
        mp_decimal m(97643);
        mp_decimal p(158665);

        BOOST_CHECK_EQUAL(mp_decimal::PGCD(n, m), 1);
        BOOST_CHECK_EQUAL(mp_decimal::PGCD(p, 456755ul), 65);
    }

    BOOST_AUTO_TEST_CASE(test_ppcm)
    {
        mp_decimal n(456753u);
        mp_decimal m(97643u);
        mp_decimal p(158665u);

        BOOST_CHECK_EQUAL(mp_decimal::PPCM(n, m), 44598733179);
        BOOST_CHECK_EQUAL(mp_decimal::PPCM(p, 456755ul), 1114938955);
    }

    BOOST_AUTO_TEST_CASE(test_chiffres)
    {
        mp_decimal n("31115050367326962860164013941500001");

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
        mp_decimal m("89123457675432198");
        BOOST_CHECK(m.palindrome());
    }
    */

BOOST_AUTO_TEST_SUITE_END()
