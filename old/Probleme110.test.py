#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def decomposition(n):
	l = []
	d = 2
	while n > 1:
		if n%d == 0:
			l.append(d)
			n = n/d
		else:
			d = d + 1
	return l

def solutions(n):
	c = 0
	print n,
	for i in xrange(n+1,2*n+1):
		if n*i%(i-n) == 0:
			print i-n, decomposition(i-n)
			c = c + 1
	print 
	return c

for ligne in open('110.test'):
	n = int(ligne)
	l = decomposition(n)
	print n , len(l), l
