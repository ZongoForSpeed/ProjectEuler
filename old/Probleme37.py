#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

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

def digits(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		n = n/10
		print n
	return l[::-1]

def derive(n):
	s = str(n)
	taille = len(s)
	l = [n]
	for i in range(1,taille):
		l.append(int(s[:i]))
		l.append(int(s[i:])) 
	l.sort()
	return l


def EstPremier(n):
	if (n == 1 or n == 0):
		return False
	limite = int(math.sqrt(n))
	m = 2
	while (m <= limite):
		if (n%m == 0):
			return False
		m = m + 1
	return True

def Est(n):
	resultat = True
	for i in derive(n):
		if (EstPremier(i) == False):
			resultat = False
			break
	return resultat

print 10, Est(10)

def problem37():
	liste = []
	produit = 1
	n = 10
	while (len(liste) < 11):
		if (Est(n)):
			liste.append(n)
			produit = produit * n
			print n
		n = n + 1
	print 'liste', liste
	print produit
	return liste

problem37()
	

