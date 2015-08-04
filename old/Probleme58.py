#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def isPremier(n):
	borne = int(math.sqrt(n))
	premier = True
	for i in range(2,borne+1):
		if (n%i == 0):
			premier = False
			break
	return premier

limite = float(sys.argv[1])

n = 3
n_premier = 3
n_diagonale = 4

print limite

while (float(n_premier) > limite * float(n_diagonale)):
	n_old = n
	n = n + 2

	n_debut = n_old**2
	n_fin = n**2

	delta = (n_fin - n_debut) / 4
	n_diagonale = n_diagonale + 1

	for i in range(1,4):
		k = i * delta + n_debut
		#print k
		n_diagonale = n_diagonale + 1
		if isPremier(k):
			n_premier = n_premier + 1
			
	#print n,limite, float(n_premier)/float(n_diagonale)
			

print n,limite, float(n_premier)/float(n_diagonale)
