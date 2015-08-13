#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = int(sys.argv[1])

def diviseurs(n):
	div = []
	resultat = set([])
	d = 2
	while (n>1):
		if (n%d == 0):
			n = n / d
			div.append(d)
		else:
			d = d + 1
	for d in div:
		resultat.add(d**div.count(d))
	return resultat

def Is(n):
	d = set([])
	for i in range(limite):
		di = diviseurs(n+i)
		if (len(di) != limite):
			return False
		if (len(di & d) == 0):
			d.union(di)
		else:
			return False
	return True
		
	
def problem47():
	trouve = False
	n = 1
	while trouve == False:
		if Is(n):
			trouve = True
		else:
			n = n+1
	return n

print problem47()
