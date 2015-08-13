#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def suivant(r,p,q):
	d = r - q**2
	if d%p != 0:
		print "Erreur : ", r,p,q,d
	d = d / p
	e = 0
	while math.sqrt(r) + q > d:
		e = e + 1
		q = q - d		
	return [e,d,-q]

def carre(r):
	return int((r**0.5))**2 == r

def period(r):
	q = int(math.sqrt(r))
	p = 1
	s = [q,p,q]
	l = []
	#print s
	while s not in l:
		l.append(s)
		s = suivant(r,s[1],s[2])
		#print s
	return len(l) - l.index(s)

def problem64():
	limite = int(sys.argv[1])
	c = 0
	for r in xrange(2,limite+1):
		if not carre(r):
			if period(r)%2 == 1:
				c = c + 1
	print c

problem64()
		

		
	
	
		
		
