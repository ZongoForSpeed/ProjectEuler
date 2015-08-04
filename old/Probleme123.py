#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

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

def power(a,b,p):
	if b == 0:
		return 1
	elif b == 1:
		return a%p
	elif b%2 == 0:
		return power((a*a)%p,b/2,p)
	else:
		return (a*power(a,b-1,p))%p

def problem123():
	n = int(sys.argv[1])
	r_max = int(sys.argv[2])
	limite = int(math.sqrt(n) + 1)	
	a = time.time()
        premier = crible(n)
        print time.time() - a
	print 'taille : ', len(premier)
	c = 0
	a = time.time()
	p_max = -1
	i_max = -1
	for i, p in enumerate(premier):
		r = power(p-1,i+1,p**2) + power(p+1,i+1,p**2)
		r = r%(p**2)
		if r > r_max:
			i_max = i + 1
			p_max = p
			break
	print time.time() - a
	print 'resultat : ', i_max, p_max

problem123()
		
