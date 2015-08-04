#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

borne_max = 614889782588491410
# 614889782588491410
# 356195430470880
# 890488576177200
puissance_max = 26

premiers = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]

def prochain_diviseur(d,n):
	for i in xrange(d,int(n**(0.5))+1):
		if n%i == 0:
			return i
	return n

def decomposition(n):
	l = {}
	d = 2
	while n > 1:
		d = prochain_diviseur(d,n)
		n = n / d
		if d in l:
			l[d] = l[d] + 1
		else:
			l[d] = 1
	return l

def solutions(n):
	l = decomposition(n)
	p = 1
	for d,v in l.iteritems():
		p = p * (2 * v + 1)
	p = (p + 1)/2
	return p

def problem110():
	limite = int(sys.argv[1])
	
	p = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29* 31 * 37 * 41 * 43 * 47
	n_min = borne_max + 1
	a = time.time()
	for i in reversed(premiers):
		n = p
		found = False
		while not found:
			s = solutions(n)
			#print n,s
			if s >= limite:
				found = True
			else:
				n = n + p
		if n < n_min:
			n_min = n
		elif n == n_min:
			break
		p = p / i
	print time.time() - a
	print n, decomposition(9350130049860600)

#def problem110b()

problem110()
		
