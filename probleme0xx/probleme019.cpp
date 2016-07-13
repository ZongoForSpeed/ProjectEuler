#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>

#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(19, "Counting Sundays")
{
    // You are given the following information, but you may prefer to do some research for yourself.
    // 
    // 1 Jan 1900 was a Monday.
    // Thirty days has September,
    // April, June and November.
    // All the rest have thirty-one,
    // Saving February alone,
    // Which has twenty-eight, rain or shine.
    // And on leap years, twenty-nine.
    // A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
    //
    // How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
    boost::gregorian::month_iterator start(boost::gregorian::date(1901,1,1),1);
    boost::gregorian::date end(2000,12,31);
    nombre resultat = 0;
    while (start <= end)
    {
        if (start->day_of_week() == boost::date_time::Sunday)
        {
            // std::cout << *start << std::endl;
            ++resultat;
        }
        ++start;
    }
    return std::to_string(resultat);
}
