#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = int(sys.argv[1])

def digits(n):
	l = []
	while n > 0:
		l.append(n%10)
		n = n / 10
	l.sort()
	return l

def permutation(n,m):
	if (digits(n) == digits(m)):
		return True
	else:
		return False

def est(c):
	for i in c:
		if (c[i] == limite):
			return i
	return -1

def limite_min(n):
	return int((10.0**float(n-1))**(1.0/3.0)) + 1

def limite_max(n):
	return int((10.0**float(n))**(1.0/3.0))

cube = {}

n=0
while (est(cube) == -1):
	cube = {}
	n = n + 1
	i_min = limite_min(n)
	i_max = limite_max(n)

	print i_min, i_max
	
	for i in range(i_min,i_max + 1):
		c = i**3
		found = False
		for k in cube:
			if (permutation(c,k)):
				cube[k] = cube[k] + 1
				found = True
				break
		if not found:
			cube[c] = 1
	
	print n
			
print est(cube),cube



