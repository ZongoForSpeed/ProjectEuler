#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

limite = int(sys.argv[1])

def decomposition_old(n,k):
	compteur = 0
	if n == 0:
		compteur = 0
	elif k == 0:
		compteur = 0
	elif k == 1:
		compteur = 1
	elif k >=n:
		return decomposition(n,n-1)
	else:
		
		for i in range(0,n,k):
			c = decomposition(n-i,k-1)
			if c > 0:
				compteur+= c
	print n,k,compteur
	return compteur

def ajout(gl,l):
	found = False
	for sl in gl:
		if sl == l:
			found = True
			break
	if not found:
		gl.append(l)

s={}
s[0] = []
s[0].append([])
s[1] = []
s[1].append([1])

for i in range(2,limite+1):
	s[i] = []
	si = []
	for k in range(0,i)[::-1]:
		delta = i - k
		for l in s[k]:
			l1= copy.copy(l)
			l1.append(delta)
			l1.sort()
#			for sl in gl:
#				if sl == l:
#					found = True
#					break
#			if not found:
			if l1 not in s[i]:
				s[i].append(l1)
	print i,len(s[i]) - 1

print limite,len(s[limite])-1
		

