#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def squarefree(n, premier):
	free = True
	for p in premier:
		if n%p == 0:
			free = False
			break
	return free

def square(n):
	limite_crible = 2**(n//2 + 1)
	limite = 2**(n//4 + 1)
	taille = 2**n
	temp = [True] * (limite_crible + 1)
	temp[0] = False
	temp[1] = False
	print 'cribble'
	for i in xrange(2,limite + 1):	
		if temp[i]:
			for j in xrange(i**2,limite_crible + 1,i):
				temp[j] = False
	print 'premier'
	premier = []
	for p,b in enumerate(temp):
		if b: premier.append(p**2)
	#print premier
	print 'nb : ', len(premier)
	print 'algorithme'
	n = taille
	d = 1
	for i,p in enumerate(premier):
		if p < taille:
			print p
			if 4 * p < taille:
				n = n * (p - 1)
				d = d * p
			else:
				n = n - d * (taille/p)
			print n,'/',d, '=', n/d
			c = 0
			for j in xrange(1,taille):
				if squarefree(j,premier[:(i+1)]):
					c = c + 1
			print '--->', c
				
	print n/d
	compteur = 0
	for i in xrange(1,taille):
		if squarefree(i,premier): 
			#print i
			compteur = compteur + 1
	print compteur

def problem193():
	limite = int(sys.argv[1])
	square(limite)


problem193()


