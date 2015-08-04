#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits10(n):
	l = set([])
	# print taille 
	while (n > 0):
		l.add(n%10)
		# print n
		n = n/10
	# print n
	return l

i = 1
trouve = False
while (trouve == False):
	l1 = digits10(i)
	if (l1 == digits10(2*i) and l1 == digits10(3*i) and l1 == digits10(4*i) and l1 == digits10(5*i) and l1 == digits10(6*i)):
		trouve = True
	else:
		i=i+1
	
print i
