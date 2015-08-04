#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits(n):
	l = []
	while (n > 0):
		l.append(n%10)
		n = n/10
	return l[::-1]

def suivant(n):
	resultat = 0
	liste = digits(n)
	for i in liste:
		resultat = resultat + i*i
	return resultat

def direction89(n):
	s = n
	while (s!=1 and s!=89):
		s = suivant(s)
	return s==89

def problem92(n):
	i = 1
	resultat = 0
	while (i < n):
		if direction89(i):
			resultat = resultat + 1
		i = i + 1
	return resultat

print problem92(int(sys.argv[1]))

