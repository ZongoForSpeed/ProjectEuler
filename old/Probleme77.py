#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def crible(n):
	premier = []
	temp = [True] * (n + 1)
	temp[0] = False
	temp[1] = False
	for i in xrange(2,int(math.sqrt(n) + 1)):	
		if temp[i]:
			
			for j in xrange(i**2,n,i):
				temp[j] = False
	premier.extend([i for i in xrange(2,n) if temp[i]])
	return premier

def fusion(l1,l2):
	l = []
	for i in l1:
		for j in l2:
			k = copy.copy(i)
			k.extend(j)
			k.sort()
			l.append(k)
	return l

def problem77():
	taille = int(sys.argv[1])
	limite = int(sys.argv[2])
	a = time.time()
        premier = crible(taille)
        print time.time() - a
	print 'taille : ', len(premier)
	c = 0
	a = time.time()
	found = False
	sop = {}
	n = 2
	while not found:
		if n >= taille:
			break
		ls = []
		for k in xrange(2,n/2+1):
			if k in sop and n-k in sop:
				if sop[k] != [] and sop[n-k] != []:
					l = fusion(sop[k],sop[n-k])
					for lk in l:
						if lk not in ls:
							#print lk
							ls.append(lk)
		#print n, sop
		if n in premier and len(ls) > limite:
			found = True
		elif len(ls) >= limite:
			found = True
		else:
			if n in premier: ls.append([n])
			sop[n] = ls
			n = n + 1
		
	if found:
		print sop[n]
		print 'resultat :', n
	print time.time() - a

problem77()
		
