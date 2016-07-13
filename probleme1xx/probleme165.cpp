#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>
#include <boost/optional.hpp>

typedef long long nombre;
typedef boost::rational<nombre> fraction;

namespace
{
    struct Point
    {
        fraction x;
        fraction y;
        
        Point(fraction _x, fraction _y) : x(_x), y(_y) { }
        
        bool operator<(const Point & p) const 
        {
            if (x != p.x)
                return x < p.x;
                
            return y < p.y;
        }
    };
    
    struct Segment
    {
        Point p1;
        Point p2;
        
        Segment(const Point & _p1, const Point & _p2) : p1(_p1), p2(_p2) { }
        
        boost::optional<Point> intersection(const Segment & s) const
        {
            fraction d = (s.p2.y - s.p1.y) * (p2.x - p1.x) - (s.p2.x - s.p1.x) * (p2.y - p1.y);
            if (d == 0)
                return boost::none;

            fraction u = ((s.p2.x - s.p1.x) * (p1.y - s.p1.y) - (s.p2.y - s.p1.y) * (p1.x - s.p1.x)) / d;
            fraction v = ((p2.x - p1.x) * (p1.y - s.p1.y) - (p2.y - p1.y) * (p1.x - s.p1.x)) / d;
            if ((u <= 0) || (u >= 1) || (v <= 0) || (v >= 1))
                return boost::none;

            return Point(p1.x + u * (p2.x - p1.x), p1.y + u * (p2.y - p1.y)); 
        }
    };
    
    std::ostream& operator<<(std::ostream& os, const Point & p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Segment & s)
    {
        os << "[" << s.p1 << ", " << s.p2 << "]";
        return os;
    }
}

ENREGISTRER_PROBLEME(165, "Intersections")
{
    // A segment is uniquely defined by its two endpoints.
    // By considering two line segments in plane geometry there are three possibilities:
    // the segments have zero points, one point, or infinitely many points in common.
    //
    // Moreover when two segments have exactly one point in common it might be the case that that 
    // common point is an endpoint of either one of the segments or of both. If a common point of 
    // two segments is not an endpoint of either of the segments it is an interior point of both 
    // segments.
    // We will call a common point T of two segments L1 and L2 a true intersection point of L1 and 
    // L2 if T is the only common point of L1 and L2 and T is an interior point of both segments.
    //
    // Consider the three segments L1, L2, and L3:
    //
    //          L1: (27, 44) to (12, 32)
    //          L2: (46, 53) to (17, 62)
    //          L3: (46, 70) to (22, 40)
    //
    // It can be verified that line segments L2 and L3 have a true intersection point. We note that 
    // as the one of the end points of L3: (22,40) lies on L1 this is not considered to be a true 
    // point of intersection. L1 and L2 have no common point. So among the three line segments, we 
    // find one true intersection point.
    //
    // Now let us do the same for 5000 line segments. To this end, we generate 20000 numbers using 
    // the so-called "Blum Blum Shub" pseudo-random number generator.
    //
    //          s0 = 290797
    //          sn+1 = sn×sn (modulo 50515093)
    //          tn = sn (modulo 500)
    //
    // To create each line segment, we use four consecutive numbers tn. That is, the first line 
    // segment is given by:
    //
    // (t1, t2) to (t3, t4)
    //
    // The first four numbers computed according to the above generator should be: 27, 144, 12 and
    // 232. The first segment would thus be (27,144) to (12,232).
    //
    // How many distinct true intersection points are found among the 5000 line segments?
    size_t limite = 20000;

    Segment L1(Point(27, 44), Point(12, 32));
    Segment L2(Point(46, 53), Point(17, 62));
    Segment L3(Point(46, 70), Point(22, 40));
    
    std::cout << "L1 = " << L1 << std::endl;
    std::cout << "L2 = " << L2 << std::endl;
    std::cout << "L3 = " << L3 << std::endl;
    
    if (auto p = L1.intersection(L2)) std::cout << "L1 x L2" << *p << std::endl;
    if (auto p = L1.intersection(L3)) std::cout << "L1 x L3" << *p << std::endl;
    if (auto p = L2.intersection(L3)) std::cout << "L2 x L3" << *p << std::endl;
    
    std::vector<nombre> t;
    nombre s = 290797;
    for (size_t n = 0; n < limite; ++n)
    {
        s = (s*s)%50515093;
        t.push_back(s%500);
    }

    std::vector<Segment> segments;
    for (size_t n = 0; n < limite; n+=4)
    {
        segments.push_back(Segment(Point(t[n], t[n+1]), Point(t[n+2], t[n+3])));
    }    
    
    std::cout << segments.front() << std::endl;
    std::set<Point> intersections;
    for (auto it1 = segments.begin(), en = segments.end(); it1 != en; ++it1)
    for (auto it2 = std::next(it1); it2 != en; ++it2)
    {
        if (auto p = it1->intersection(*it2))
            intersections.insert(*p);
    }
    
    return std::to_string(intersections.size());
}
