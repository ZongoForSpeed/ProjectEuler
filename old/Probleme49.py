#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = 10000

liste = {}
listePremier = []
for i in range(2,limite):
	liste[i] = True
for i in range(2,limite):
	if liste[i]:
		listePremier.append(i)
		for j in range(i**2,limite,i):
			liste[j] = False

def digits(n):
	l = []
	while n > 0:
		l.append(n%10)
		n = n / 10
	l.sort()
	return l[::-1]

def estPremier(n):
	return n in listePremier

listePremier2 = filter(estPremier,range(1000,limite))

preresultat = []
for p in listePremier2:
	d = digits(p)
	l = [p]
	for q in listePremier2:
		if q > p and d == digits(q):
			l.append(q)
	if len(l) >= 3:
		l.sort()
		preresultat.append(l)

print preresultat
print len(preresultat)

resultat = []
for l in preresultat:
	s = len(l)
	for i in range(s-2):
		for j in range(i+1,s-1):
			for k in range(j+1,s):
				if ((l[j] - l[i]) == (l[k] - l[j])):
					resultat.append([l[i],l[j],l[k]])

print resultat
	
