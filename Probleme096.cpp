#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

namespace
{
    vecteur options(const matrice & S, const nombre i, const nombre j)
    {
        std::vector<bool> test(10, true);
        const nombre groupe_i = i - i%3;
        const nombre groupe_j = j - j%3;
        for (nombre k = 0; k < 9; ++k)
        {
            test[S[i][k]] = false;
            test[S[k][j]] = false;
            test[S[groupe_i + k%3][groupe_j + k/3]] = false;
        }
        
        vecteur option;
        for (nombre n = 1; n < 10; ++n)
            if (test[n]) option.push_back(n);
            
        return option;
    }
    
    bool sudoku (matrice & S)
    {
        nombre minimum = 10;
        nombre i_min = 10;
        nombre j_min = 10;
        vecteur option;
        for (nombre i = 0; i < 9; ++i)
        for (nombre j = 0; j < 9; ++j)
        {
            if (S[i][j] == 0)
            {
                vecteur o = options(S, i, j);
                if (o.empty())
                    return false;
                    
                if (o.size() < minimum)
                {
                    i_min = i;
                    j_min = j;
                    option = o;
                }
            }
        }
        
        if (option.empty())
            return true;
            
        matrice T = S;
        for (nombre o: option)
        {
            T[i_min][j_min] = o;
            if (sudoku(T))
            {
                S = T;
                return true;
            }
        }
        
        return false;
    }
    
    void affiche(const matrice & S)
    {
        std::cout << "[" << std::endl;
        for (const auto & ligne: S)
            std::cout << "    " << ligne << std::endl;
        
        std::cout << "]" << std::endl;
    }
}

void probleme096()
{
    Timer t("probleme 96");
    // Su Doku (Japanese meaning number place) is the name given to a popular puzzle concept. Its 
    // origin is unclear, but credit must be attributed to Leonhard Euler who invented a similar, 
    // and much more difficult, puzzle idea called Latin Squares. The objective of Su Doku puzzles, 
    // however, is to replace the blanks (or zeros) in a 9 by 9 grid in such that each row, column, 
    // and 3 by 3 box contains each of the digits 1 to 9. Below is an example of a typical starting
    // puzzle grid and its solution grid.
    //
    // matrice exemple = {
    //     {0, 0, 3, 0, 2, 0, 6, 0, 0},
    //     {9, 0, 0, 3, 0, 5, 0, 0, 1},
    //     {0, 0, 1, 8, 0, 6, 4, 0, 0},       
    //     {0, 0, 8, 1, 0, 2, 9, 0, 0},
    //     {7, 0, 0, 0, 0, 0, 0, 0, 8},
    //     {0, 0, 6, 7, 0, 8, 2, 0, 0},   
    //     {0, 0, 2, 6, 0, 9, 5, 0, 0},
    //     {8, 0, 0, 2, 0, 3, 0, 0, 9},
    //     {0, 0, 5, 0, 1, 0, 3, 0, 0}
    // };
    //
    // A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although 
    // it may be necessary to employ "guess and test" methods in order to eliminate options (there 
    // is much contested opinion over this). The complexity of the search determines the difficulty 
    // of the puzzle; the example above is considered easy because it can be solved by straight 
    // forward direct deduction.
    //
    // The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty 
    // different Su Doku puzzles ranging in difficulty, but all with unique solutions (the first 
    // puzzle in the file is the example above).
    // 
    // By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner 
    // of each solution grid; for example, 483 is the 3-digit number found in the top left corner of
    // the solution grid above.
    nombre resultat = 0;
    
    std::ifstream ifs("data/p096_sudoku.txt");
    std::string ligne;
    matrice m;
    while (std::getline(ifs, ligne))
    {
        // std::cout << "\"" << ligne << "\"" << std::endl;
        if (ligne.substr(0,4) == "Grid")
        {
            if (!m.empty())
            {
                sudoku(m);
                resultat += 100*m[0][0] + 10*m[0][1] + m[0][2];
                m.clear();
            }
        }
        else
        {
            std::istringstream iss (ligne);
            char c;
            vecteur v;
            while (iss >> c)
            {
                v.push_back(c - '0');
            }
            m.push_back(v);
        }
    }
    sudoku(m);
    resultat += 100*m[0][0] + 10*m[0][1] + m[0][2];
    std::cout << "Solution: " << resultat << std::endl;
}
