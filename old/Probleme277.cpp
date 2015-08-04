#include <iostream>
#include <vector>
#include <boost/rational.hpp>

#include "Timer.h"

typedef long long nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

class Probleme277
{
    // A modified Collatz sequence of integers is obtained from a starting value a1 in the following way:
    //
    // an+1 = an/3 if an is divisible by 3. We shall denote this as a large downward step, "D".
    //
    // an+1 = (4an + 2)/3 if an divided by 3 gives a remainder of 1. We shall denote this as an upward step, "U".
    //
    // an+1 = (2an - 1)/3 if an divided by 3 gives a remainder of 2. We shall denote this as a small downward step, "d".
    //
    // The sequence terminates when some an = 1.
    //
    // Given any integer, we can list out the sequence of steps.
    // For instance if a1=231, then the sequence {an}={231,77,51,17,11,7,10,14,9,3,1} corresponds to the steps "DdDddUUdDD".
    //
    // Of course, there are other sequences that begin with that same sequence "DdDddUUdDD....".
    // For instance, if a1=1004064, then the sequence is DdDddUUdDDDdUDUUUdDdUUDDDUdDD.
    // In fact, 1004064 is the smallest possible a1 > 10^6 that begins with the sequence DdDddUUdDD.
    //
    // What is the smallest a1 > 10^15 that begins with the sequence "UDDDUdddDDUDDddDdDddDDUDDdUUDd"?
public:
    Probleme277() {}
    ~Probleme277() {}
    
    void algorithme2()
    {
        Timer t("algorithme");
        const std::string sequence("UDDDUdddDDUDDddDdDddDDUDDdUUDd");
        
        fraction a(1);
        fraction b;
        
        for (std::string::const_reverse_iterator it = sequence.rbegin(); it != sequence.rend(); ++it)
        {
            char s = *it;
            switch (s)
            {
            case 'd':
                a = 3*a / 4;
                b = (3*b - 2) / 4;
                break;
            case 'D':
                a = 3*a;
                b = 3*b;
                break;
            case 'U':
                a = 3*a / 2;
                b = (3*b + 1) / 2;
                break;
            }
        }
        
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        
        // a = 205891132094649/67108864
        // b = -56288647073033/33554432
        //   = -112577294146066/67108864
    
        // 1147956813228110
        // 1125977393124310
    }
    
    nombre test_sequence(nombre n, const std::string & sequence)
    {
        for (std::string::const_reverse_iterator it = sequence.rbegin(); it != sequence.rend(); ++it)
        {
            char s = *it;
            switch (s)
            {
            case 'U':
                n = 3*n - 2;
                if (n%4 != 0)
                    return 0;
                n /= 4;
                break;
            case 'D':
                n = 3*n;
                break;
            case 'd':
                n = 3*n + 1;
                if (n%2 != 0)
                    return 0;
                n /= 2;
                break;
            }
        }
        
        return n;
    }
    
    void algorithme()
    {
        Timer t("algorithme");
        const std::string sequence("UDDDUdddDDUDDddDdDddDDUDDdUUDd");
        nombre limite = 1000000000000000LL;
        // const std::string sequence("DdDddUUdDD");
        // nombre limite = 1000000LL;
        nombre n = 1;
        vecteur solutions;
        while (true)
        {
            nombre r = test_sequence(n, sequence);
            if (r != 0)
            {
                std::cout << r;
                if (solutions.empty() == false)
                {
                    std::cout << "\t" << r - solutions.back();
                }
                
                std::cout << std::endl;
                solutions.push_back(r);
                if (r > limite)
                {
                    break;
                }
            }
            ++n;
        }
    }
};

int main(int, char**)
{
    Probleme277 p;
    p.algorithme();
    return 0;
}