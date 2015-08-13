#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		# print n
		n = n/10
	# print n
	return l[::-1]

def somme(n,k):
	result = 0;
	for i in digits(n):
		result = result + i**k
	return result

def problem30():
	s = 0
	k = 5
	for i in range(2,1000000):
		if i == somme(i,k):
			s = s + i
	return s	

print problem30()



