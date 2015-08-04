#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def power(n,p,d):
	if p == 0:
		return 1
	elif p == 1:
		return n%d
	elif p%2 == 0:
		return power((n*n)%d,p/2,d)
	else:
		return (n*power(n,p - 1,d))%d

def cycle(n,d):
	k = 2
	p = n**2
	while p%d != n:
		p = (p * n)%d
		k = k + 1
	return k

def problem188():
	n = int(sys.argv[1])
	p = int(sys.argv[2])
	D = [int(sys.argv[3])]
	for i in xrange(1,p):
		D.append(D[-1])
	D = D[::-1]
	P = 1
	for d in D:
		P = power(n,P,d)
	print P

problem188()
	
	
