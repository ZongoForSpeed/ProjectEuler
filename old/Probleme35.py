#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = int(sys.argv[1])

def premier(n):
	ens = set([])
	mappy = {}
	for i in range(2,n):
		mappy[i] = True
	for i in range(2,n):
		if (mappy[i] == True):
			for j in range(2*i,n,i):
				mappy[j] = False
	for m in mappy:
		if (mappy[m] == True):
			ens.add(m)
	return ens

def digits10(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		# print n
		n = n/10
	# print n
	return l[::-1]	

def toNumber(l):
	s = ''
	for i in l:
		s = s + str(i)
	return int(s)

def rotation(l,n):
	return l[n:] + l[:n]

premiers = premier(limite)

resultat = set([])

for i in range(limite):
	if (i in premiers):
		b = True
		l = digits10(i)
		for j in range(1,len(l)):
			if (toNumber(rotation(l,j)) not in premiers):
				b = False
		if b:
			resultat.add(i)

print resultat
print len(resultat)
