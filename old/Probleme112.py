#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def digits(n):
	l = []
	while (n > 0):
		l.append(n%10)
		n = n/10
	return l[::-1]

def bouncy(n):
	l = digits(n)
	ls = copy.copy(l)
	ls.sort()
	if ls == l:
		return False
	elif ls[::-1] == l:
		return False
	else:
		return True

limite = float(sys.argv[1])

n = 1
n_bouncy = 0


while(float(n_bouncy) < float(n) * limite):
	n = n + 1
	if bouncy(n):
		n_bouncy = n_bouncy + 1
	
print n
	



