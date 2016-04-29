#include "arithmetiques.h"
#include "polygonal.h"

#include <set>
#include <vector>
#include <boost/optional.hpp>

namespace diophantienne
{
    template<typename Nombre>
    boost::optional<Nombre> carre_parfait(Nombre x)
    {
        Nombre s = racine_carre(x);
        if (s * s == x)
            return s;
        else
            return boost::none;
    }
    
    // PQa algorithm as described in: http://www.jpr2718.org/pell.pdf
    // This performs the continued fraction expansion for (p0+sqrt(d))/q0
    template<typename Nombre>
    std::pair<std::vector<Nombre>, size_t> PQa(Nombre p0, Nombre q0, Nombre d)
    {
        long double sqrt_d = std::sqrt(d);
        //   assert 0 < d, "D cannot be negative or zero"
        //   assert q0 != 0, "Q0 cannot be zero"
        //   assert (p0*p0 - d) % q0 == 0, "P0² cannot be different from D modulo Q0"
        //   assert int(sqrt_d) * int(sqrt_d) != d, "D cannot be a perfect square"
        Nombre a_i = 1, a_im = 0;
        Nombre b_i = 0, b_im = 1;
        Nombre g_i = q0, g_im = -p0;
        Nombre p_i = p0, q_i = q0;
        Nombre p_ir = 0, q_ir = 0;
        
        size_t i = 0;
        boost::optional<size_t> ir;
        
        std::vector<Nombre> alphas;
        while (true)
        {
            long double xi_i = (p_i + sqrt_d) / q_i;
            long double xibar_i = (p_i - sqrt_d) / q_i;
            
            Nombre alpha_i = static_cast<Nombre>(xi_i);
            
            std::tie(a_i, a_im) = std::make_pair(alpha_i * a_i + a_im, a_i);
            std::tie(b_i, b_im) = std::make_pair(alpha_i * b_i + b_im, b_i);
            std::tie(g_i, g_im) = std::make_pair(alpha_i * g_i + g_im, g_i);
            
            // Everything is now as of i
            if (!ir && xi_i > 1 && xibar_i > -1 && xibar_i < 0)
            {
                ir = i;
                p_ir = p_i;
                q_ir = q_i;
            }
            
            if (ir && *ir != i && p_i == p_ir and q_i == q_ir)
                break;
            
            alphas.push_back(alpha_i);
            
            // Update p_i and q_i for i+1
            p_i = alpha_i * q_i - p_i;
            q_i = (d - p_i * p_i) / q_i;
            
            ++i;
        }
        
        return std::make_pair(alphas, i - *ir);
    }
    
    // Get the minimal solution for x² - d.y² = epsilon, where epsilon can be 1 or -1
    template<typename Nombre>
    std::pair<Nombre, Nombre> pell1_min(Nombre d, Nombre epsilon)
    {
        // assert epsilon == 1 or epsilon == -1, "epsilon is different from -1 and 1"
        std::vector<Nombre> alphas;
        size_t l = 0;
        std::tie(alphas, l) = PQa<Nombre>(0, 1, d);
        
        size_t index = 0;
        if (l & 1)
        {
            index = (epsilon == 1) ? 2*l - 1 : l - 1;
        }
        else if (epsilon == -1)
        {
            return std::make_pair(0, 0);
        }
        else
        {
            index = l - 1;
        }
        
        Nombre b_i = 0, b_im = 1;
        Nombre g_i = 1, g_im = 0;
        
        size_t pre_l = alphas.size() - l;
        for (size_t i = 0; i < index + 1; ++i)
        {
            Nombre alpha_i = (i < pre_l) ? alphas[i] : alphas[pre_l + (i - pre_l) % l];
            std::tie(b_i, b_im) = std::make_pair(alpha_i * b_i + b_im, b_i);
            std::tie(g_i, g_im) = std::make_pair(alpha_i * g_i + g_im, g_i);
        }
        
        return std::make_pair(g_i, b_i);
    }

    // Get the minimal solution for x² - d.y² = 4*epsilon, where epsilon can be 1 or -1
    template<typename Nombre>
    std::pair<Nombre, Nombre> pell4_min(Nombre d, Nombre epsilon)
    {
        // assert epsilon == 1 or epsilon == -1, "epsilon is different from -1 and 1"
        switch(d % 4)
        {
        case 0:
            {
                auto resultat = pell1_min(d / 4, epsilon);
                return std::make_pair(2 * resultat.first, resultat.second);
            }
            break;
        case 2:
        case 3:
            {
                auto resultat = pell1_min(d / 4, epsilon);
                return std::make_pair(2 * resultat.first, 2 *resultat.second);
            }
            break;
        default:
            break;
        }
        
        std::vector<Nombre> alphas;
        size_t l = 0;
        std::tie(alphas, l) = PQa<Nombre>(1, 2, d);
        
        if (l % 2 == 0 && epsilon)
            return std::make_pair(0, 0);
        
        Nombre b_i = 0, b_im = 1;
        Nombre g_i = 2, g_im = -1;
        size_t pre_l = alphas.size() - l;

        for (size_t i = 0; i < l; ++i)
        {
            Nombre alpha_i = (i < pre_l) ? alphas[i] : alphas[pre_l + (i - pre_l) % l];
            std::tie(b_i, b_im) = std::make_pair(alpha_i * b_i + b_im, b_i);
            std::tie(g_i, g_im) = std::make_pair(alpha_i * g_i + g_im, g_i);
        }

        // If l is odd, solution to the -4 equation.
        // If l is even, solution to the +4 equation.
        // So the only case where we have to change g and b is when l is odd and epsilon is 1
        if (l % 2 == 1 && epsilon == 1)
            return std::make_pair((g_i*g_i + b_i*b_i*d) / 2, g_i*b_i);
        else
            return std::make_pair(g_i, b_i);
    }
    
    // Get all the solutions for x² - d.y² = epsilon, where epsilon can be 1 or -1
    template<typename Nombre, typename Callback>
    void pell1(Nombre d, Nombre epsilon, Callback & callback)
    {
        Nombre t = 0;
        Nombre u = 0;
        
        std::tie(t, u) = pell1_min(d, epsilon);
        if (t == 0 || u == 0)
            return;
        
        Nombre x = t;
        Nombre y = u;
        
        for (size_t n = 0;; ++n)
        {
            if (epsilon == 1 || n % 2 == 0)
            {
                if (!callback(x, y)) break;
            }
            std::tie(x, y) = std::make_pair(t*x + u*y*d, t*y + u*x);
        }
    }

    // Yield all the solutions for x² - d.y² = 4*epsilon, where epsilon can be 1 or -1
    template<typename Nombre, typename Callback>
    void pell4(Nombre d, Nombre epsilon, Callback & callback)
    {
        Nombre t = 0;
        Nombre u = 0;
        
        std::tie(t, u) = pell1_min(d, epsilon);
        
        if (t == 0 && u == 0)
            return;
            
        Nombre x = t;
        Nombre y = u;
        
        for (size_t n = 0;; ++n)
        {
            if (epsilon == 1 || n % 2 == 0)
            {
                if (!callback(x, y)) break;
            }
            std::tie(x, y) = std::make_pair((t*x + u*y*d) / 2, (t*y + u*x) / 2);
        }
    }
    
    template<typename Nombre>
    std::vector<std::pair<Nombre, Nombre>> pell_funds_bf(Nombre d, Nombre n)
    {
        Nombre t = 0;
        Nombre u = 0;
        std::tie(t, u) = pell1_min<Nombre>(d, 1);
        
        Nombre l1 = 0;
        Nombre l2 = 0;
        
        if (n > 0)
        {
            l1 = 0;
            l2 = racine_carre(n*(t-1)/(2*d));
        }
        else
        {
            l1 = racine_carre(-n / (1*d));
            l2 = racine_carre((-n*(t+1)) / (2*d));
        }
        
        std::vector<std::pair<Nombre, Nombre>> funds;
        for (Nombre y = l1; y < l2 + 1; ++y)
        {
            if (auto s = carre_parfait(n + d*y*y))
            {
                Nombre x = *s;
                funds.push_back(std::make_pair(x, y));
                
                if ((x*x+d*y*y) % n != 0 || (2*x*y) % n != 0) 
                    funds.push_back(std::make_pair(-x, y));
            }
        }
        
        return funds;
    }
    
    template<typename Nombre>
    std::vector<std::pair<Nombre, Nombre>> pell_bf(Nombre d, Nombre n, Nombre max_x)
    {
        auto funds = pell_funds_bf(d, n);
        std::set<std::pair<Nombre, Nombre>> solution;
        for (auto p: funds)
            solution.insert(std::make_pair(std::abs(p.first), std::abs(p.second)));
        
        auto callback = [&] (Nombre t, Nombre u)
        {
            bool added = false;
            for (auto p: funds)
            {
                Nombre x = p.first*t + p.second*u*d;
                Nombre y = p.first*u + p.second*t;
                
                if (std::abs(x) <= max_x)
                {
                    solution.insert(std::make_pair(std::abs(x), std::abs(y)));
                    added = true;
                }
            }
            return added;
        };
        
        pell1<Nombre>(d, 1, callback);
        
        return std::vector<std::pair<Nombre, Nombre>>(solution.begin(), solution.end());
    }

    // Find solutions to a.x² - b.y² = c²
    template<typename Nombre>
    std::vector<std::pair<Nombre, Nombre>> quad_s(Nombre a, Nombre b, Nombre c, Nombre max_x)
    {
        std::vector<std::pair<Nombre, Nombre>> resultat;
        auto pell = pell_bf(a*b, a*c, a*max_x);
        for (auto p : pell)
        {
            if (p.first % a == 0)
                resultat.push_back(std::make_pair(p.first / a, p.second));
        }
        
        return resultat;
    }
}
