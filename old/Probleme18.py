#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def max(a,b):
	result = 0
	if (a > b):
		result = a
	else:
		result = b
	return result

fichier = sys.argv[1]
# print fichier

triangle = {}
n = 1
for ligne in open(fichier):
	triangle[n] = {}
	m = 1
	for i in ligne.split(' '):
		triangle[n][m] = int(i.strip())
		m = m + 1
	n = n + 1

# print triangle

n = len(triangle)

resultat = {}

for i in range(1,n+1):
	resultat[i] = {}
	if (i == 1):
		resultat[i][i] = triangle[i][i]
	else:
		for j in range(1,i+1):
			if (j == 1):
				resultat[i][j] = resultat[i-1][j] + triangle[i][j]
			elif (j == i):
				resultat[i][j] = resultat[i-1][j-1] + triangle[i][j]
			else:
				resultat[i][j] = max(resultat[i-1][j-1],resultat[i-1][j]) + triangle[i][j]

gagnant = 0
for i in resultat[n]:
	if (resultat[n][i] > gagnant):
		gagnant = resultat[n][i]

print gagnant
