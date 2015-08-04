#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def EstCarre(n):
	return (int(math.sqrt(n))**2) == n

def EstTriangulaire(n):
	delta = 1 + 8 * n
	sDelta = math.sqrt(delta)
	d1 = (-1.0+sDelta)/(2.0)
	if (int(d1) == d1 and d1 > 0):
		return True	
	d2 = (-1.0-sDelta)/(2.0)
	if (int(d2) == d2 and d2 > 0):
		return True
	return False

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

def EstHexagonal(n):
	delta = 1 + 8 * n
	sDelta = math.sqrt(delta)
	d1 = (1.0+sDelta)/(4.0)
	if (int(d1) == d1 and d1 > 0):
		return True
	d2 = (1.0-sDelta)/(4.0)
	if (int(d2) == d2 and d2 > 0):
		return True
	return False

n = int(sys.argv[1])
h = 0
trouve = False
while (trouve == False):
	h = n*(2*n - 1)
	if (EstTriangulaire(h) and EstPentagonal(h)):
		trouve = True
	else:
		n = n + 1

print h
print n

