#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def factorielle(n):
	p = 1
	for i in xrange(1,n+1):
		p = p * i
	return p

def C(n,k):
	return factorielle(n)/(factorielle(n-k)*factorielle(k))

def croissant(l):
	c = 0
	for li in xrange(0,l):
		for i in xrange(0,10):
			c = c + C(li+i,i)
	return c

def decroissant(l):
	c = 0
	for li in xrange(0,l):
		for i in xrange(0,9):
			c = c + C(li+i,i)
	return c

def doublon(l):
	return l * 10

def compte(l):
	return croissant(l) + decroissant(l) - doublon(l)

print croissant(int(sys.argv[1]))
print decroissant(int(sys.argv[1]))
print doublon(int(sys.argv[1]))
print compte(int(sys.argv[1]))
