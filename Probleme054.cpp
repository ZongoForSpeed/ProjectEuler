#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <array>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::vector<std::string> main;
typedef std::vector<main> mains;

namespace
{
    struct Carte
    {
        unsigned short valeur;
        char couleur;
        Carte (const std::string & carte)
        {
            switch(carte.at(0))
            {
            case '2': valeur = 2; break;
            case '3': valeur = 3; break;
            case '4': valeur = 4; break;
            case '5': valeur = 5; break;
            case '6': valeur = 6; break;
            case '7': valeur = 7; break;
            case '8': valeur = 8; break;
            case '9': valeur = 9; break;
            case 'T': valeur = 10; break;
            case 'J': valeur = 11; break;
            case 'Q': valeur = 12; break;
            case 'K': valeur = 13; break;
            case 'A': valeur = 14; break;
            default:
                valeur = 0;
            }
            couleur = carte.at(1);
        }
        
        ~Carte() {}
        
        bool operator<(const Carte & c) const
        {
            if (valeur != c.valeur)
                return valeur < c.valeur;
                
            return couleur < c.couleur;
        }
    };
    
    struct Main
    {
        std::vector<Carte> cartes;
        
        Main(const std::string & carte1, 
             const std::string & carte2, 
             const std::string & carte3, 
             const std::string & carte4, 
             const std::string & carte5)
        {
            cartes.push_back(Carte(carte1));
            cartes.push_back(Carte(carte2));
            cartes.push_back(Carte(carte3));
            cartes.push_back(Carte(carte4));
            cartes.push_back(Carte(carte5));
            
            std::sort(cartes.begin(), cartes.end());
        }
        
        unsigned short royal_flush() const
        {
            if (straight_flush() == 14)
                return 14;
            return 0;
        }
        
        unsigned short straight_flush() const
        {
            if (flush() != 0)
                return straight();
            return 0;
        }
        
        unsigned short flush() const
        {
            if (cartes.at(0).couleur == cartes.at(1).couleur
                && cartes.at(0).couleur == cartes.at(2).couleur
                && cartes.at(0).couleur == cartes.at(3).couleur
                && cartes.at(0).couleur == cartes.at(4).couleur)
                return cartes.at(4).valeur;
            return 0;
        }
        
        unsigned short straight() const 
        {
            if (cartes.at(0).valeur + 1 == cartes.at(1).valeur
                && cartes.at(0).valeur + 2 == cartes.at(2).valeur
                && cartes.at(0).valeur + 3 == cartes.at(3).valeur
                && cartes.at(0).valeur + 4 == cartes.at(4).valeur)
                return cartes.at(4).valeur;
            return 0;
        }
        
        unsigned short full_house() const
        {
            if (cartes.at(0).valeur == cartes.at(1).valeur 
                && cartes.at(0).valeur == cartes.at(2).valeur 
                && cartes.at(3).valeur == cartes.at(4).valeur)
                return cartes.at(0).valeur;
            if (cartes.at(0).valeur == cartes.at(1).valeur 
                && cartes.at(2).valeur == cartes.at(3).valeur 
                && cartes.at(2).valeur == cartes.at(4).valeur)
                return cartes.at(2).valeur;
            return 0;
        }
        
        unsigned short carre() const
        {
            if ((cartes.at(0).valeur == cartes.at(1).valeur && cartes.at(0).valeur == cartes.at(2).valeur && cartes.at(0).valeur == cartes.at(3).valeur)
                || (cartes.at(1).valeur == cartes.at(2).valeur && cartes.at(1).valeur == cartes.at(3).valeur && cartes.at(1).valeur == cartes.at(4).valeur))
                return cartes.at(2).valeur;
            return 0;
        }
        
        unsigned short brelan() const
        {
            if ((cartes.at(0).valeur == cartes.at(1).valeur && cartes.at(0).valeur == cartes.at(2).valeur)
                || (cartes.at(1).valeur == cartes.at(2).valeur && cartes.at(1).valeur == cartes.at(3).valeur)
                || (cartes.at(2).valeur == cartes.at(3).valeur && cartes.at(2).valeur == cartes.at(4).valeur))
                return cartes.at(2).valeur;
            return 0;
        }
        
        unsigned short paire() const
        {
            if (cartes.at(0).valeur == cartes.at(1).valeur || cartes.at(1).valeur == cartes.at(2).valeur)
                return cartes.at(1).valeur;
            if (cartes.at(2).valeur == cartes.at(3).valeur || cartes.at(3).valeur == cartes.at(4).valeur)
                return cartes.at(3).valeur;
            return 0;
        }
        
        std::pair<unsigned short, unsigned short> double_paire() const 
        {
            if (cartes.at(0).valeur == cartes.at(1).valeur && (cartes.at(2).valeur == cartes.at(3).valeur || cartes.at(3).valeur == cartes.at(4).valeur))
                return std::make_pair(cartes.at(3).valeur, cartes.at(1).valeur);
            if (cartes.at(1).valeur == cartes.at(2).valeur && cartes.at(3).valeur == cartes.at(4).valeur)
                return std::make_pair(cartes.at(3).valeur, cartes.at(1).valeur);
            return std::make_pair(0, 0);
        }
        
        bool operator<(const Main & main)
        {
            if (royal_flush() != main.royal_flush())
                return royal_flush() < main.royal_flush();
                
            if (straight_flush() != main.straight_flush())
                return straight_flush() < main.straight_flush();
                
            if (carre() != main.carre())
                return carre() < main.carre();
            
            if (full_house() != main.full_house())
                return full_house() < main.full_house();
            
            if (flush() != main.flush())
                return flush() < main.flush();    
                
            if (straight() != main.straight())
                return straight() < main.straight();  
                
            if (brelan() != main.brelan())
                return brelan() < main.brelan();
                
            if (double_paire() != main.double_paire())
                return double_paire() < main.double_paire();
            if (paire() != main.paire())
                return paire() < main.paire(); 
                
            if (cartes.at(4).valeur != main.cartes.at(4).valeur)
                return cartes.at(4).valeur < main.cartes.at(4).valeur;
                
            if (cartes.at(3).valeur != main.cartes.at(3).valeur)
                return cartes.at(3).valeur < main.cartes.at(3).valeur;
            
            if (cartes.at(2).valeur != main.cartes.at(2).valeur)
                return cartes.at(2).valeur < main.cartes.at(2).valeur;
            
            if (cartes.at(1).valeur != main.cartes.at(1).valeur)
                return cartes.at(1).valeur < main.cartes.at(1).valeur;
            
            return cartes.at(0).valeur < main.cartes.at(0).valeur;
        }
    };
}

ENREGISTRER_PROBLEME(54, "Poker hands")
{
    Timer t("probleme 54");
    // In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, 
    // in the following way:
    // 
    //      High Card: Highest value card.
    //      One Pair: Two cards of the same value.
    //      Two Pairs: Two different pairs.
    //      Three of a Kind: Three cards of the same value.
    //      Straight: All cards are consecutive values.
    //      Flush: All cards of the same suit.
    //      Full House: Three of a kind and a pair.
    //      Four of a Kind: Four cards of the same value.
    //      Straight Flush: All cards are consecutive values of same suit.
    //      Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
    // The cards are valued in the order:
    //      2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
    //
    // If two players have the same ranked hands then the rank made up of the highest value wins; 
    // for example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie,
    // for example, both players have a pair of queens, then highest cards in each hand are compared 
    // (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on.
    //
    // Consider the following five hands dealt to two players:
    //
    //  Hand	Player 1	 	    Player 2	 	    Winner
    //  1	    5H 5C 6S 7S KD      2C 3S 8S 8D TD      Player 2
    //          Pair of Fives       Pair of Eights
    //
    //  2	 	5D 8C 9S JS AC      2C 5C 7D 8S QH      Player 1
    //          Highest card Ace    Highest card Queen
    // 	
    //  3	    2D 9C AS AH AC      3D 6D 7D TD QD      Player 2
    //          Three Aces          Flush with Diamonds
    // 	
    //  4	    4D 6S 9H QH QC      3D 6D 7H QD QS      Player 1
    //          Pair of Queens      Pair of Queens
    //          Highest card Nine   Highest card Seven
    // 	
    // 5	 	2H 2D 4C 4D 4S      3C 3D 3S 9S 9D      Player 1
    //          Full House          Full House
    //          With Three Fours    with Three Threes
    // 
    // The file, poker.txt, contains one-thousand random hands dealt to two players. 
    // Each line of the file contains ten cards (separated by a single space): the first five are 
    // Player 1's cards and the last five are Player 2's cards. You can assume that all hands are valid 
    // (no invalid characters or repeated cards), each player's hand is in no specific order, and in each 
    // hand there is a clear winner.
    //
    // How many hands does Player 1 win?
    std::ifstream ifs("data/p054_poker.txt");
    std::string carte1, carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9, carte10;
    nombre compteur = 0;
    while (ifs >> carte1 >> carte2 >> carte3 >> carte4 >> carte5 >> carte6 >> carte7 >> carte8 >> carte9 >> carte10)
    {   
        Main m1(carte1, carte2, carte3, carte4, carte5);
        Main m2(carte6, carte7, carte8, carte9, carte10);
        if (m2 < m1)
            ++compteur;
    }
    std::cout << "Solution: " << compteur << std::endl;
}
