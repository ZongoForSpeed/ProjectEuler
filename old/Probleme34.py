#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits10(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		# print n
		n = n/10
	# print n
	return l[::-1]

def factorielle(n):
	if (n == 1 or n == 0):
		return 1
	else:
		return n * factorielle(n-1)

def somme_factorielle(n):
	s = 0
	for i in digits10(n):
		s = s + factorielle(i)
	return s


print 7*factorielle(9)
l = []
s = 0
for i in range(2540160):
	if (i == somme_factorielle(i)):
		s = s + i
		l.append(i)

print l
print s
		
