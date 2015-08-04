#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def factorielle(n):
	f = 1
	while n > 1:
		f = f * n
		n = n - 1
	return f

def digits(n):
	liste = []
	while n > 0:
		liste.append(n%10)
		n = n / 10
	return liste[::-1]

def next(n):
	result = 0
	for i in digits(n):
		result = result + factorielle(i)
	return result

def chaine(n):
	l = []
	while (n not in l):
		l.append(n)
		n = next(n)
	return len(l)

n = 1
limite = int(sys.argv[1])
compteur = 0

while (n < limite):
	if (chaine(n) == 60):
		print n
		compteur = compteur + 1
	n = n + 1	

print compteur
