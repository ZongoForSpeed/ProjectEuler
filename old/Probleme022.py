#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

lettre = {'A':1,'B':2,'C':3,'D':4,'E':5,'F':6,'G':7,'H':8,'I':9,'J':10,'K':11,
'L':12,'M':13,'N':14,'O':15,'P':16,'Q':17,'R':18,'S':19,'T':20,'U':21,'V':22,
'W':23,'X':24,'Y':25,'Z':26}

def max(a,b):
	result = 0
	if (a > b):
		result = a
	else:
		result = b
	return result

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

noms.sort()

scores = 0
n = 1
for nom in noms:
	scores = scores + n * score(nom)
	n = n + 1

print scores

# print noms

