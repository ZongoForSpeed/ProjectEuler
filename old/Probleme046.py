#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def DoubleSquare(n):
	return 2*n*n

def IsPrime(n):
	limite = int(math.sqrt(n))
	i = 2
	while i <= limite:
		if n%i == 0:
			return False
		i+=1
	return True

def OddComposite(n):
	if (n%2 == 0):
		return False
	for s in map(DoubleSquare,range(int(math.sqrt(n/2.0))+1)):
		if IsPrime(n-s):
			return True
	return False

def problem46():
	trouve = False
	n = 3
	while trouve == False:
		if OddComposite(n):
			n+=2
		else:
			trouve = True
	return n

print problem46()
