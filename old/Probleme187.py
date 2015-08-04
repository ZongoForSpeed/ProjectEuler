#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def find(n,p):
	for i in xrange(p,int(math.sqrt(n)) + 1):
		if n%i == 0:
			return i
	return n

def composite(n):
	l = []
	p = 2
	while n > 1:
		p = find(n,p)
		l.append(p)
		if len(l) > 2:
			return False
		n = n / p
	return len(l) == 2

def crible(n):
	premier = []
	temp = [True] * (n + 1)
	temp[0] = False
	temp[1] = False
	for i in xrange(2,int(math.sqrt(n) + 1)):	
		if temp[i]:
			
			for j in xrange(i**2,n,i):
				temp[j] = False
	premier.extend([i for i in xrange(2,n) if temp[i]])
	return premier

def problem187():
	n = int(sys.argv[1])
	limite = int(math.sqrt(n) + 1)	
	a = time.time()
        premier = crible(n)
        print time.time() - a
	print 'taille : ', len(premier)
	c = 0
	a = time.time()
	for p in premier:
		if p > limite:
			break
		#print p,[k for k in premier if k >= p and p*k < n]
		c = c + len([k for k in premier if k >= p and p*k < n])
	print time.time() - a
	print 'compteur : ', c

problem187()
		
