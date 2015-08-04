#include <iostream>
#include <cstdlib> 

typedef unsigned long long nombre;
 
class Problem160
{
    // For any N, let f(N) be the last five digits before the trailing zeroes in N!.
    // For example,
    //
    //      9! = 362880 so f(9)=36288
    //      10! = 3628800 so f(10)=36288
    //      20! = 2432902008176640000 so f(20)=17664
    //
    // Find f(1,000,000,000,000)
 
    nombre limite;
public:
    Problem160(nombre limite_) : limite(limite_) {}
    ~Problem160() {}
 
    void algorithme()
    {
        nombre resultat = 1;
        nombre facteur2 = 0;
        nombre facteur5 = 0;
     
        for (nombre i = 1; i < limite + 1; ++i)
        {
            nombre f = facteur(i, facteur2, facteur5);
            resultat *= f;
            resultat = resultat%100000;
        }
     
        std::cout << "resultat = " << resultat << std::endl;
        std::cout << "facteur2 = " << facteur2 << std::endl;
        std::cout << "facteur5 = " << facteur5 << std::endl;
     
        for (nombre i = facteur5; i < facteur2; ++i)
        {
            resultat *= 2;
            resultat = resultat%100000;
        }
     
        std::cout << "f(" << limite << ") = " << resultat << std::endl;
    }
 
private:
    nombre facteur(nombre n, nombre & f2, nombre & f5)
    {
        while(n%2 == 0)
        {
            n /= 2;
            ++f2;
        }
     
        while(n%5 == 0)
        {
            n /= 5;
            ++f5;
        }
     
        return n;
    }
};
 
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage is " << argv[0] << " limite" << std::endl;
        return 1;
    }
    
    Problem160 p(atoll(argv[1]));
    p.algorithme();
    return 0;  
}
        
