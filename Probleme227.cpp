#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// #include <boost/multiprecision/cpp_int.hpp>
//
// typedef boost::multiprecision::mpz_int nombre;
typedef unsigned long long nombre;
typedef std::vector<long double> vecteur;

ENREGISTRER_PROBLEME(227, "The Chase")
{
    Timer timer("probleme 227");
    // "The Chase" is a game played with two dice and an even number of players.
    //
    // The players sit around a table; the game begins with two opposite players having one die each. 
    // On each turn, the two players with a die roll it.
    // If a player rolls a 1, he passes the die to his neighbour on the left; if he rolls a 6, 
    // he passes the die to his neighbour on the right; otherwise, he keeps the die for the next turn.
    // The game ends when one player has both dice after they have been rolled and passed; that player 
    // has then lost.
    //
    // In a game with 100 players, what is the expected number of turns the game lasts?
    //
    // Give your answer rounded to ten significant digits.
    vecteur chase(51, 0.0);
    chase.back() = 1.0;
    
    nombre tours = 0;
    long double fin = 0.0;
    long double esperance = 0.0;
    
    long double erreur = std::pow(0.1L, 12);
    
    while (fin < 1 - erreur)
    {
    	chase.front() = 0.0;
    	++tours;
    	vecteur nouveau(51, 0.0);
    	for (size_t i = 0; i < 51; ++i)
    	{
    		switch(i)
    		{
    		case 0:
    			break;
    		case 1:
    			nouveau[0] += chase[1] * 2 / 9;
	            nouveau[1] += chase[1] * 19 / 36;
	            nouveau[2] += chase[1] * 2 / 9;
	            nouveau[3] += chase[1] / 36;
	            break;
            case 49:
	            nouveau[47] += chase[49] / 36;
	            nouveau[48] += chase[49] * 2 / 9;
	            nouveau[49] += chase[49] * 19 / 36;
	            nouveau[50] += chase[49] * 2 / 9;
	            break;
	        case 50:
	            nouveau[48] += chase[50] / 18;
	            nouveau[49] += chase[50] * 4 / 9;
	            nouveau[50] += chase[50] / 2;
	            break;
	        default:
	            nouveau[i - 2] += chase[i] / 36;
	            nouveau[i - 1] += chase[i] * 2 / 9;
	            nouveau[i] += chase[i] / 2;
	            nouveau[i + 1] += chase[i] * 2 / 9;
	            nouveau[i + 2] += chase[i] / 36;
	            break;
    		}
    	}
    	
    	std::swap(chase, nouveau);
    	fin += chase.front();
    	esperance += tours * chase.front();
    }
    
    std::cout << std::setprecision(10);
    std::cout << "Solution: " << esperance << std::endl;
}
