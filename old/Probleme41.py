#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def digits(n):
	liste = []
	# print taille 
	while (n > 0):
		liste.append(n%10)
		# print n
		n = n/10
	# print n
	liste.sort()
	return (liste == range(1,len(liste) + 1))

k = int(sys.argv[1])
n = 10**k

pandigital = []
premier = {}
i = 2
while i <= n:
	premier[i] = True
	i = i + 1
i = 2
while i <= n:
	if premier[i]:
		for j in range(2*i,n,i):
			premier[j] = False
		if digits(i):
			pandigital.append(i)
	i = i + 1 

print pandigital[-1]

