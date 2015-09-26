#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

namespace
{
    struct point
    { 
        double x,y; 
        point() : x(0.0), y(0.0) {}
        point(double _x, double _y) : x(_x), y(_y) {}
    };
    
    point suivant(point a, point b)
    {
    	double m = tan(-atan((a.y-b.y)/(a.x-b.x))+2*atan(-4*b.x/b.y));
    	double c = b.y-m*b.x;

    	// solution of 4x^2 + (mx+c)^2 = 100:
    	double x1 = (-2*m*c + sqrt(400*m*m+1600-16*c*c))/(8+2*m*m);
    	double x2 = (-2*m*c - sqrt(400*m*m+1600-16*c*c))/(8+2*m*m);

    	point s;
    	if (fabs(b.x-x1)<0.0001) 
    	    s.x = x2;
    	else 
    	    s.x = x1;
    	s.y = m*s.x + c;
    	return s;	
    }
}

void probleme144()
{
    Timer t("probleme 144");
	// In laser physics, a "white cell" is a mirror system that acts as a delay line for the laser beam.
	// The beam enters the cell, bounces around on the mirrors, and eventually works its way back out.
    //
    // The specific white cell we will be considering is an ellipse with the equation 4x2 + y2 = 100
    // 
    // The section corresponding to −0.01 ≤ x ≤ +0.01 at the top is missing, allowing the light to enter 
    // and exit through the hole.
    //
    // The light beam in this problem starts at the point (0.0,10.1) just outside the white cell, and 
    // the beam first impacts the mirror at (1.4,-9.6).
    // 
    // Each time the laser beam hits the surface of the ellipse, it follows the usual law of reflection
    // "angle of incidence equals angle of reflection." That is, both the incident and reflected beams
    // make the same angle with the normal line at the point of incidence.
    // 
    // In the figure on the left, the red line shows the first two points of contact between the laser 
    // beam and the wall of the white cell; the blue line shows the line tangent to the ellipse at the
    // point of incidence of the first bounce.
    //
    // The slope m of the tangent line at any point (x,y) of the given ellipse is: m = −4x/y
    // 
    // The normal line is perpendicular to this tangent line at the point of incidence.
    // 
    // The animation on the right shows the first 10 reflections of the beam.
    // 
    // How many times does the beam hit the internal surface of the white cell before exiting?
    point a(0.0, 10.1);
    point b(1.4, -9.6);
	nombre resultat = 0;
	while (!(fabs(b.x) < 0.01 && b.y > 0))
	{
		point c = b;
		b = suivant(a, b);
		a = c;
		++resultat;
	}
    std::cout << "Solution: " << resultat << std::endl;
}
