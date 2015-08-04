#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def cycle(n,a):
	k = 2
	p = n**2
	while p%a != n:
		p = p * n
		k = k + 1
	return k

def pgcd(m,n):
	if n == 0:
		return m
	else:
		return pgcd(n,m%n)

def power(a,b):
	if b == 0:
		return 1
	elif b == 1:
		return a
	elif b%2 == 0:
		return power(a*a,b/2)
	else:
		return a*power(a,b-1)

def ppcm(m,n):
	return m*n/pgcd(m,n)

def reste_max(a):
	a2 = a*a
	m1 = cycle(a - 1,a2)
	m2 = cycle(a + 1,a2)
	p1 = 1
	p2 = 1
	m = ppcm(m1,m2)
	r_max = 0
	for i in xrange(1,m + 1):
		p1 = (p1 * (a - 1))%a2
		p2 = (p2 * (a + 1))%a2
		r = (p1 + p2)%a2
		if r > r_max:
			r_max = r
		if r_max == a2 - 1:
			break
	return r_max

def problem120():
	a = time.time()
	limite = int(sys.argv[1])
	sigma_r = 0
	for i in xrange(3,limite + 1):
		r = reste_max(i)
		print i, r
		sigma_r = sigma_r + r
	print time.time() - a
	return sigma_r

print problem120()

