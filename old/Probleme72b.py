#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def find_factor(n) :
	for i in xrange(2, int(n**0.5 + 1)) :
		if n % i == 0 :
			return i
	return n
 
def find_factors(n) :
	factors = []
	while n != 1 :
		fac = find_factor(n)
		if fac not in factors :
			factors.append(fac)
		n /= fac
	return factors
 
somme = 0
for n in xrange(2, 1000001) :
	factors = find_factors(n)
	dividend = n
	divisor = 1
	for factor in factors :
		dividend *= factor - 1
		divisor  *= factor
	totient = dividend / divisor
	somme = somme + totient

print somme
	
