#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def concatener(a,b):
	return int(str(a)+str(b))

def valid(n):
	l = str(n)
	for i in l:
		if (l.count(i) > 1 or i == 0):
			return False
	return True

def valid2(n,m):
	if (n%10 == 0 or m%10 == 0 or valid(n) == False or valid(m) == False):
		return False
	else:
		return valid(concatener(n,m))


def pandigital(n):
	if valid(n):
		resultat = n
		m = 2
		while (m<=9):
			if (valid2(resultat,m*n)):
				resultat = concatener(resultat,m*n)
				m = m + 1
			else:
				return resultat
	else:
		return 0

def problem38(n):
	resultat = 0
	for i in range(n):
		if (i%5 != 0):
			r = pandigital(i)
			if (r > resultat):
				resultat = r
				print r
	return resultat

print problem38(int(sys.argv[1]))
