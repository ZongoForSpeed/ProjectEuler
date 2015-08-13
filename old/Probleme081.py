#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

fichier = sys.argv[1]

matrix = []
for ligne in open(fichier):
	l = []
	for i in ligne.split(','):
		l.append(int(i))
	matrix.append(l)

taille = len(matrix)
path = {}
for i in range(taille):
	for j in range(taille):
		if (i == 0 and j == 0):
			path[(i,j)] = matrix[i][j]
		elif i == 0:
			path[(i,j)] = path[(i,j-1)] + matrix[i][j]
		elif j == 0:
			path[(i,j)] = path[(i-1,j)] + matrix[i][j]
		else:
			path[(i,j)] = min(path[(i-1,j)],path[(i,j-1)]) + matrix[i][j]

print path[(taille-1,taille-1)]
			

