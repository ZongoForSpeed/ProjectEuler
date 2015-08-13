#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

# m5.txt
# matrix.txt

def voisin(n,taille):
	v = []
	i = n[0]
	j = n[1]
	if i > 1:
		v.append((i-1,j))
	if j > 1:
		v.append((i,j-1))
	if i < taille:
		v.append((i+1,j))
	if j < taille:
		v.append((i,j+1))
	return v
		

def prochain(graphe,frontiere,distance):
	suivant = ()
	minimum = -1
	for v in frontiere:
		if distance[v] + graphe[v] < minimum or minimum == -1:
			minimum = distance[v] + graphe[v]
			suivant = v
	return suivant
		

def dijkstra(fichier):
	graphe = {}
	infini = 0
	i = 1
	for ligne in open(fichier):
		j = 1
		for s in ligne.split(','):
			graphe[i,j] = int(s)
			infini = infini + int(s)
			j = j + 1
		i = i + 1
	taille = int(len(graphe)**(0.5))
	# initialisation
	distance = {}
	predecesseur = {}
	noeud = []
	for i in xrange(1,taille + 1):
		for j in xrange(1,taille + 1):
			distance[i,j] = infini
			predecesseur[i,j] = (1,1)
			noeud.append((i,j))
	debut = (1,1)
	fait = []
	frontiere = set([debut])
	fin = (taille,taille)
	distance[debut] = 0
	s1 = debut
	while len(fait) != taille**2:
		fait.append(s1)
		frontiere.remove(s1)
		print len(fait)
		#print s1,graphe[s1]
		#print fait
		for n in voisin(s1,taille):
			if distance[n] > distance[s1] + graphe[s1]:
				predecesseur[n] = s1
				distance[n] = distance[s1] + graphe[s1]
			if n not in fait:
				frontiere.add(n)
		s1 = prochain(graphe,frontiere,distance)
		#print s1
	#print predecesseur
	#print distance
	s1 = fin
	print distance[fin] + graphe[fin]
	#print distance[fin]

dijkstra(sys.argv[1])	

