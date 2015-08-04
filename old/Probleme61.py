#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite_min = 1000
limite_max = 10000

def digits(n):
	l = []
	while n > 0:
		l.append(n%100)
		n=n/100
	return l[::-1]

def concat(a,b):
	return a*100+b

def P(i,n):
	if i == 3:
		return n*(n+1)/2
	elif i == 4:
		return n**2
	elif i == 5:
		return n*(3*n-1)/2
	elif i == 6:
		return n*(2*n-1)
	elif i == 7:
		return n*(5*n-3)/2
	elif i == 8:
		return n*(3*n-2)
	else:
		return 0

def problem61():
	polygonal = {}
	inverse = {}
	bad = set([])
	resultat = []
	polygonals = set([])
	for i in range(3,9):
		polygonal[i] = []
		n = 0
		po = 0
		while po < limite_max:
			n = n + 1
			po = P(i,n)
			if po > limite_min:
				polygonal[i].append(po)
				if po in polygonals:
					bad.add(po)
					inverse[po].append(i)
				else:
					inverse[po] = [i]
				polygonals.add(po)
		print i, len(polygonal[i])
	print len(polygonals)
	print len(bad)
	somme = set([])
	for j1 in polygonals:
		i1 = j1/100
		i2 = j1%100
		for j2 in [k for k in range(i2*100,(i2+1)*100) if k in polygonals]:
			i3 = j2%100
			for j3 in [k for k in range(i3*100,(i3+1)*100) if k in polygonals]:
				i4 = j3%100
				for j4 in [k for k in range(i4*100,(i4+1)*100) if k in polygonals]:
					i5 = j4%100
					for j5 in [k for k in range(i5*100,(i5+1)*100) if k in polygonals]:
						i6 = j5%100
						j6 = concat(i6,i1)
						if j6 in polygonals:
							r = [j1,j2,j3,j4,j5,j6]
							r.sort()
							if len(set(r)) == len(r):
								l = []
								s = 0
								for k in r:
									for m in inverse[k]:
										l.extend([m])
									s = s + k
								l.sort()
								if len(set(l)) == 6:
									resultat.append((s,r,l))
									somme.add(s)
								

	print len(resultat)
	
	for r in resultat:
		print r
	print somme
#	resultat = {}
#	for i8 in polygonal[8]:
#		resultat.clear()
#		resultat[8] = i8
#		[i for i in a if i in b]

		
		

problem61()
		
