#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def lirefichier(fichier):
	matrice = []
	for ligne in open(fichier):
		l=[]
		for s in ligne.split(','):
			l.append(int(s))
		matrice.append(copy.copy(l))
	return matrice

def problem82():
	fichier = sys.argv[1]
	matrice = lirefichier(fichier)
	n = len(matrice)
	chemin = {}
	for i in range(n):
		chemin_bas = {}
		for j in range(n):
			if i == 0:
				chemin_bas[j] = matrice[j][i]
			elif j == 0:
				chemin_bas[j] = chemin[(i-1,j)] + matrice[j][i]
			else:
				chemin_bas[j] = min(chemin[(i-1,j)],chemin_bas[j-1]) + matrice[j][i]

		chemin_haut = {}
		for j in range(n)[::-1]:
			if i == 0:
				chemin_haut[j] = matrice[j][i]
			elif j == n-1:
				chemin_haut[j] = chemin[(i-1,j)] + matrice[j][i]
			else:
				chemin_haut[j] = min(chemin[(i-1,j)],chemin_haut[j+1]) + matrice[j][i]

		for j in range(n):
			chemin[(i,j)] = min(chemin_haut[j],chemin_bas[j])

	l_min = -1
	for i in range(n):
		if (l_min == -1):
			l_min = chemin[(n-1,i)]
		else:
			l_min = min(l_min,chemin[(n-1,i)])
	return l_min

print problem82()

