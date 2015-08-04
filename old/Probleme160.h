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
    Problem160(nombre limite_);
    ~Problem160();
 
    void algorithme();
 
private:
    nombre facteur(nombre n, nombre & f2, nombre & f5);
};
 
