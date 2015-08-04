#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <gmpxx.h>

typedef long nombre;

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

class Point
{
public:
	nombre x;
	nombre y;
	
	Point(nombre _x, nombre _y) : x(_x), y(_y) {}
};

class Vecteur
{
public:
	nombre x;
	nombre y;
	
	Vecteur(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {}
	
	static nombre scalaire(const Vecteur& v1, const Vecteur& v2)
	{
		return v1.x*v2.x + v1.y*v2.y;
	}
};

class Probleme147
{
	// In a 3x2 cross-hatched grid, a total of 37 different rectangles 
	// could be situated within that grid as indicated in the sketch.
	//
	// There are 5 grids smaller than 3x2, vertical and horizontal 
	// dimensions being important, i.e. 1x1, 2x1, 3x1, 1x2 and 2x2. 
	// If each of them is cross-hatched, the following number of 
	// different rectangles could be situated within those smaller grids:
	// 
	// 		1x1: 1
	// 		2x1: 4
	// 		3x1: 8
	// 		1x2: 4
	// 		2x2: 18
	// 
	// Adding those to the 37 of the 3x2 grid, a total of 72 different 
	// rectangles could be situated within 3x2 and smaller grids.
	// 
	// How many different rectangles could be situated within 47x43 
	// and smaller grids?
	
	nombre hauteur;
	nombre largeur;

public:
	Probleme147(nombre _hauteur, nombre _largeur) : hauteur(_hauteur), largeur(_largeur)
	{
	}
	
	void algorithme()
	{
		mpz_class solution = 0;
		{
			Timer t("algorithme");
			nombre H = hauteur + 1;
			nombre L = largeur + 1;
			nombre taille = H * L;
			for (nombre p1 = 0; p1 < taille; ++p1)
			{
				Point A(p1%H, p1/H);
				for (nombre p2 = p1 + 1; p2 < taille; ++p2)
				{
					Point B(p2%H, p2/H);
					Vecteur AB(A, B);
					for (nombre p3 = p2 + 1; p3 < taille; ++p3)
					{
						Point C(p3%H, p3/H);
						Vecteur AC(A, C);
						if (Vecteur::scalaire(AB, AC) == 0)
						{
							nombre x_max = std::max(A.x, std::max(B.x, C.x));
							nombre y_max = std::max(A.y, std::max(B.y, C.y));
							
							nombre c = (H - x_max) * (L - y_max);
							std::cout << c << std::endl;
							solution += c;
						}
					}
				}
			}		
		}
		
		std::cout << "******************** SOLUTION ********************" << std::endl;
		std::cout << solution << std::endl;
		
	}		
};

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << argv[0] << " hauteur largeur " << std::endl;
		return 1;
	}
	
	Probleme147 p(atoi(argv[1]), atoi(argv[2]));
	p.algorithme();
	
	return 0;
}
