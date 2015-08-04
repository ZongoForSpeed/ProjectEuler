#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def power(a,b):
	if (b == 0):
		return 1
	elif (b == 1):
		return a
	elif (b%2 == 0):
		return power(a*a,b/2)
	else:
		return a*power(a,b-1)

def digits(n):
	l = 0
	# print taille 
	while (n > 0):
		l = l + n%10
		n = n/10
	return l

s_max = 0
for a in range(1,100):
	for b in range(1,100):
		s = digits(power(a,b))
		if (s > s_max):
			s_max = s

print s_max
