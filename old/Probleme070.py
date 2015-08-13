#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def digits(n):
	d = []
	while n > 0:
		d.append(n%10)
		n/=10
	d.sort()
	return d

def permutation(n,m):
	return digits(n) == digits(m)

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

def totient(n):
	factors = find_factors(n)
	t = n
	for factor in factors :
		t = t * (factor -1) / factor
	return t
 
winner = 0
ratio_min = 10.0
for n in xrange(2, 10000001) :
	factors = find_factors(n)
	t = totient(n)
	if permutation(n,t):
		ratio = float(n)/float(t)
		if ratio < ratio_min:
			ratio_min = ratio
			winner = n
print winner
	
