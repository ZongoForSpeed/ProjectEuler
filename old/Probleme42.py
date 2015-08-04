#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

lettre = {'A':1,'B':2,'C':3,'D':4,'E':5,'F':6,'G':7,'H':8,'I':9,'J':10,'K':11,
'L':12,'M':13,'N':14,'O':15,'P':16,'Q':17,'R':18,'S':19,'T':20,'U':21,'V':22,
'W':23,'X':24,'Y':25,'Z':26}

triangle = set([])

s = 0
i = 0
while (s < 1000000):
	s = s + i
	i = i + 1
	triangle.add(s)
	
def score(s):
	result = 0
	n = len(s)
	for i in range(0,n):
		result = result + lettre[s[i]]
	return result

fichier = sys.argv[1]
print fichier

noms = []
for ligne in open(fichier):
	for i in ligne.split(','):
		noms.append(i.strip())

n = 0
for nom in noms:
	if score(nom) in triangle:
		n = n + 1

print n

# print noms

