//public class Problem164 {
    //private static final int MAX_SUM = 9;
    //private static final int NUM_OF_DIGIT = 20;
    //private static long[][][] count = new long[10][10][NUM_OF_DIGIT];
 
    //private static long getCount(int d1, int d2, int remainDigits) {
        //if (remainDigits == 0)
            //return 1;
        //else {
            //if (count[d1][d2][remainDigits] == 0)
                //for (int i=0; i<=MAX_SUM-(d1+d2); i++)
                    //count[d1][d2][remainDigits] += getCount(d2, i, remainDigits-1);
            //return count[d1][d2][remainDigits];
        //}
    //}
 
    //public static void main(String[] args) {
        //final long start = System.currentTimeMillis();
        //long result=0;

	        //for (int i=1; i<=9; i++)
	            //result += getCount(0, i, NUM_OF_DIGIT-1);
	        //System.out.println(result);
	        //System.out.format("%.3f\n", (System.currentTimeMillis()-start)/1000.0);
	    //}
	//}
//}

#include <iostream>
#include <vector>
#include <cstdlib>

typedef size_t nombre;

class Timer
{
private:
    time_t debut;
    std::string titre;

public:
    Timer(const std::string &t) : titre(t)
    {
        debut = time(NULL);
        std::cout << "Debut " << titre << " ..." << std::endl;
    }

    virtual ~Timer()
    {
        std::cout << "Fin " << titre << " en " << time(NULL) - debut << " secondes " << std::endl;
    }
};

class Probleme164
{
	// How many 20 digit numbers n (without any leading zero) exist such
	// that no three consecutive digits of n have a sum greater than 9?
	
	nombre somme_max;
	nombre chiffres;
	
	typedef std::vector<nombre> vecteur;
	typedef std::vector<vecteur> matrice;
	typedef std::vector<matrice> tableau;
	
	tableau compteur;

public:
	Probleme164(nombre chiffres_) : somme_max(9), chiffres(chiffres_) {}

	void algorithme()
	{
		{
			Timer t("contruction tableau");
			vecteur v(chiffres,0);
			matrice m(10, v);
			compteur.assign(10, m);
		}

		nombre solution = 0;
		{
			Timer t("algorithme");
			for (nombre i = 1; i < 10; ++i)
			{
				solution += getCount(0, i, chiffres - 1);
			}
		}
		
		std::cout << "**************** SOLUTION ****************" << std::endl;
		std::cout << solution << std::endl;
	}
	
	nombre getCount(nombre d1, nombre d2, nombre reste) 
	{
        if (reste == 0)
            return 1;
        else if (compteur[d1][d2][reste] == 0)
                for (nombre i=0; i<=somme_max-(d1+d2); i++)
                    compteur[d1][d2][reste] += getCount(d2, i, reste-1);
        return compteur[d1][d2][reste];
    }
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme164 p(atoi(argv[1]));
	p.algorithme();	
	
	return 0;
}
