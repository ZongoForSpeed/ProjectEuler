#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

fichier = sys.argv[1]

key = []
for ligne in open(fichier):
	key.append(ligne.strip())

def findMin(key):
	trouve = -1
	max_pos = {}
	for k in key:
		n = 1
		for i in k:
			if (max_pos.has_key(i)):
				max_pos[i] = max(max_pos[i],n)
			else:
				max_pos[i] = n
			n = n +1


	for j in max_pos:
		if (max_pos[j] == 1):
			trouve = j
	return trouve

def estVide(key):
	estVide = True
	for k in key:
		if (len(k) != 0):
			estVide = False
	return estVide

def remove(key,mink):
	for i in range(len(key)):
		if (len(key[i]) != 0):
			if (key[i][0] == mink):
				key[i] = key[i][1:]

	return key

passwd = ''
while (estVide(key) == False):
	mink = findMin(key)
	print mink
	passwd = passwd + mink
	key = remove(key,mink)
	

print passwd

