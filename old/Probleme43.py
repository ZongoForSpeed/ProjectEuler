#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def pandigital(n):
	liste = []
	# print taille 
	while (n > 0):
		liste.append(n%10)
		# print n
		n = n/10
	# print n
	for d in range(0,10):
		if (liste.count(d) != 1):
			return False
	return True

def pandigitalSimple(n):
	liste = []
	while (n > 0):
		liste.append(n%10)
		# print n
		n = n/10
	for d in liste:
		if (liste.count(d) > 1):
			return False
	return True

def groupe(a,b):
	r = -1
	if (a%100 == b/10):
		r = a*10 + b%10
		if (pandigitalSimple(r)):
			return r
	return -1


def intersection(a,b):
	resultat = []
	for i in a:
		for j in b:
			g = groupe(i,j)
			if g >=0:
				resultat.append(g)
	return resultat

def problem43():
	resultat = range(0,1000,1)
	premier = [2,3,5,7,11,13,17]
	for i in premier:
		resultat = intersection(resultat, range(0,1000,i))
	somme = 0
	for i in resultat:
		if (pandigital(i)):
			print i
			somme+=i
	return somme

print problem43()
