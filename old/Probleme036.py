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

def digits2(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%2)
		# print n
		n = n/2
	# print n
	return l[::-1]

palindromic = 0
for i in range(1000000):
	l10 = digits10(i)
	l2 = digits2(i)
	if (l10 == l10[::-1] and l2 == l2[::-1]):
		palindromic = palindromic + i

print palindromic


