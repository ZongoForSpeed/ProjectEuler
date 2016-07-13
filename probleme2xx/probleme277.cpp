#include "problemes.h"

#include <iostream>
#include <vector>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
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
}

ENREGISTRER_PROBLEME(277, "A Modified Collatz sequence")
{
    // A modified Collatz sequence of integers is obtained from a starting value a1 in the following way:
    //
    // an+1 = an/3 if an is divisible by 3. We shall denote this as a large downward step, "D".
    // an+1 = (4an + 2)/3 if an divided by 3 gives a remainder of 1. We shall denote this as an upward
    //        step, "U".
    // an+1 = (2an - 1)/3 if an divided by 3 gives a remainder of 2. We shall denote this as a small 
    //        downward step, "d".
    //
    // The sequence terminates when some an = 1.
    //
    // Given any integer, we can list out the sequence of steps.
    // For instance if a1=231, then the sequence {an}={231,77,51,17,11,7,10,14,9,3,1} corresponds 
    // to the steps "DdDddUUdDD".
    //
    // Of course, there are other sequences that begin with that same sequence "DdDddUUdDD....".
    // For instance, if a1=1004064, then the sequence is DdDddUUdDDDdUDUUUdDdUUDDDUdDD.
    // In fact, 1004064 is the smallest possible a1 > 10^6 that begins with the sequence DdDddUUdDD.
    //
    // What is the smallest a1 > 10^15 that begins with the sequence "UDDDUdddDDUDDddDdDddDDUDDdUUDd"?
    const std::string sequence("UDDDUdddDDUDDddDdDddDDUDDdUUDd");
    const nombre limite = 1000000000000000LL;
    
    nombre resultat = 0;
    for (nombre n = 1;; ++n)
    {
        nombre r = test_sequence(n, sequence);
        if (r != 0 && r > limite)
        {
            resultat = r;
            break;
        }
    }
    
    return std::to_string(resultat);
}
