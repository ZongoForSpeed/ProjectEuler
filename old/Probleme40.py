#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = int(sys.argv[1])

def digits10(n):
	l = []
	# print taille 
	while (n > 0):
		l.append(n%10)
		# print n
		n = n/10
	# print n
	return l[::-1]	

grosnombre = [0]

i = 1
while (len(grosnombre) <= limite):
	grosnombre = grosnombre + digits10(i)
	i = i + 1
i = 1
d = []
while (i <= limite):
	d.append(grosnombre[i])
	i = i * 10	

print d
