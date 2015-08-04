#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def EstPentagonal(n):
	delta = 1 + 24 * n
	sDelta = math.sqrt(delta)
	d1 = (1.0+sDelta)/(6.0)
	if (int(d1) == d1 and d1 > 0):
		return True
	d2 = (1.0-sDelta)/(6.0)
	if (int(d2) == d2 and d2 > 0):
		return True
	return False

def Pentagonal(n):
	return n*(3*n - 1)/2

possible = True
d_min = -1
penta = []
n = 1
while possible:
	p = Pentagonal(n)
	if d_min != -1 and d_min < p - penta[-1]:
		possible = False
		break
	for i in penta[::-1]:
		d = p - i
		if (d_min != -1 and d > d_min):
			break
		elif d in penta and EstPentagonal(p + i):
			if (d_min == -1 or d < d_min):
				d_min = d
				print p, i, d_min
				break
	print n
	penta.append(p)
	n = n + 1

print d_min

