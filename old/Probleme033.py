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
		n = n/10
	return l[::-1]

def FractionEgale(a,b,c,d):
	return a*d == b*c

def Zarb(n,d):
	dd = digits(d)
	dn = digits(n)
	inter = set(dd) & set(dn)
	if (inter == set([]) or n%10==0 or d%10 == 0):
		return False
	for dp in dd:
		for np in dn:
			if FractionEgale(n,d,np,dp) and np not in inter and dp not in inter:
				return True
	return False

def problem33():
	solution = []
	for d in range(10,100):
		for n in range(10,d):
			if Zarb(n,d):
				solution.append([n,d])
	return solution

print problem33()
