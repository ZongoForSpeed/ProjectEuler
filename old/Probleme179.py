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

def diviseurs(n):
	l = decomposition(n)
	p = 1
	for d,v in l.iteritems():
		p = p * (v + 1)
	return p + 1

def problem179():
	limite = int(sys.argv[1])
	compteur = 0
	d_old = diviseurs(2)
	for i in xrange(3,limite + 1):
		d = diviseurs(i)
		if d_old == d:
			compteur = compteur + 1
		d_old = d
	print compteur
			
problem179()
		
