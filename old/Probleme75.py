#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def rectangle(a,b):
	c = int(math.sqrt(a**2 + b**2))
	if a**2 + b**2 == c**2:
		return c
	else:
		return -1

def problem75():
	limite = int(sys.argv[1])
	#slimite = int(math.sqrt(limite) + 1)
	triangle = {}
	for (a,b,c) in [(a,b,c) for a in xrange(limite/3) for b in xrange(limite/2) for c in xrange(limite/2) if a + b + c <= limite and a < b and b < c]:
		#print a,b,c
		if a**2 + b**2 == c**2:
			l = a + b + c
			if l in triangle:
				triangle[l] = triangle[l] + 1
			else:
				triangle[l] = 1
	compteur = 0
	#print triangle
	for k,v in triangle.iteritems():
		if v == 1:
			compteur = compteur + 1
	print 'compteur :', compteur

problem75()
