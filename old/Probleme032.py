#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		# print n
		n = n/10
	# print n
	return l[::-1]

def valid(l):
	for i in l:
		if (l.count(i) > 1 or i == 0):
			return False
	return True

NombresValides = []

for i in range(1,10000):
	if ((valid(digits(i))) and (i%5 != 0)):
		NombresValides.append(i)

resultat = set([])
for i in NombresValides:
	for j in NombresValides:
		if (j > i):
			k = i * j
			l = digits(k)
			if (valid(l)):
				l.extend(digits(i))
				l.extend(digits(j))
				if (valid(l) and len(l) == 9):
					resultat.add(k)

somme = 0

for i in resultat:
	somme = somme + i

print somme
