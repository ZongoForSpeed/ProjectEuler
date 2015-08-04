#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def polynome(n,a,b):
	return n*n + a * n + b

def diviseurs(n):
	div = set([1])
	d = 2
	while (n>1):
		if (n%d == 0):
			n = n / d
			div.add(d)
		else:
			d = d + 1
	return div

def EstPremier(n):
	if (n == 1 or n == 0):
		return False
	else:
		return n in diviseurs(n)
	
def suitePremier(a,b):
	compteur = 0
	marche = True
	while (marche):
		if EstPremier(polynome(compteur,a,b)):
			compteur = compteur + 1
		else:
			marche = False
	return compteur


def problem27(n):
	a_max = 0
	b_max = 0
	c_max = 0
	for a in range(-n+1,n):
		if (a%100 == 0):
			print 'a : ' + str(a)
		for b in range(-n+1,n):
			compteur = suitePremier(a,b)
			if (compteur > c_max):
				c_max = compteur
				a_max = a
				b_max = b
				print 'a_max : ' + str(a_max),
				print '\tb_max : ' + str(b_max),
				print '\tcompteur : ' + str(compteur)
	print 'resultat : '
	print 'a_max : ' + str(a_max),
	print '\tb_max : ' + str(b_max),
	print '\ta_max*b_max : ' + str(a_max*b_max)				
	return a_max*b_max

n = int(sys.argv[1])
print problem27(n)
