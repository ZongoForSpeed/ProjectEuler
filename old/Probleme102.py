#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

origine = [0.0,0.0]

def lirefichier(fichier):
	triangle = []
	for ligne in open(fichier):
		l=[]
		p=[]
		i = 0
		for s in ligne.split(','):
			p.append(float(s))
			if (i%2 == 1):
				l.append(copy.copy(p))
				p = []
			i = i + 1
		triangle.append(copy.copy(l))
	return triangle

fichier = sys.argv[1]

def aire(a,b,c):
	return 1.0/2.0*abs((b[0]-a[0])*(c[1]-a[1]) - (c[0] - a[0])*(b[1]-a[1]))

def contient(t):
	A = aire(t[0],t[1],t[2])
	A1 = aire(origine,t[1],t[2])
	A2 = aire(t[0],origine,t[2])
	A3 = aire(t[0],t[1],origine) 
	if ( A == A1 + A2 + A3 ):
		return True
	else:
		return False

def problem102():
	fichier = sys.argv[1]
	triangles = lirefichier(fichier)
	compteur = 0
	for t in triangles:
		if contient(t):
			compteur = compteur + 1
	return compteur

print problem102()




	
