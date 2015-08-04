#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

euler = {}

premier = []

def crible(n):
	dico = {}
	for i in range(2,n+1):
		dico[i] = True
	for i in range(2,n+1):
		if dico[i]:
			premier.append(i)
			for j in range(2*i,n+1,i):
				dico[j] = False
	premier.sort()

def phi(n):
	if (n == 1):
		euler[n] = 1
		return 1	
	d = 2
	p = n
	found = False
	if n in premier:
		p = n - 1
	else:
		while not found:
			if (n%d == 0):
				found = True
			else:
				d = d + 1
		d_max = d
		k = 1
		while n%d_max == 0:
			d_max = d_max * d
			k = k + 1
		d_max = d_max/d
		if (n == d_max):
			p = (d - 1)*d**(k-2)
		else:
			p = euler[d_max] * euler[n/d_max]
	euler[n] = p
	return p

def decomposition(n):
	result = []
	if n in premier:
		result.append(n)		
	else:
		for p in premier:
			if n%p == 0:
				result.append(p)
			if p > n:
				break
	return result

def phi2(n):
	result = n
	p = decomposition(n)
	for i in p:
		result = result * (i-1) / i
	return result

def problem72():
	limite = int(sys.argv[1])
	print limite
	crible(limite)
	print '-- fin crible --', len(premier)
	fraction = 0
	for d in range(2,limite+1):
		if d%(limite/100) == 0:
			print d
		fraction = fraction + phi(d)

	return fraction

print problem72()
