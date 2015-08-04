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

def decomposition(n):
	factors = set([])
	while n != 1 :
		fac = find_factor(n)
		if fac not in factors :
			factors.add(fac)
		n /= fac
	return factors

def rad(n):
	factors = decomposition(n)
	r = 1
	for i in factors:
		r*=i
	return r

def problem124():
	radical = []
	limite = int(sys.argv[1])
	valeur = int(sys.argv[2])
	for i in xrange(1,limite+1):
		radical.append([rad(i),i])
	radical.sort()
	return radical[valeur-1]

print problem124()
