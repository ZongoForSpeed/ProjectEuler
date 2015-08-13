#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def triangle(n):
	return n*(n+1)/2

limite = 2000

tij_min = 0
nij_min = []
i_min = 0
j_min = 0
for i in range(1,limite+1):
	ti = triangle(i)
	for j in range(1,i+1):
		tj = triangle(j)
	
		if (abs(2000000-ti*tj) < abs(2000000 - tij_min)):
			tij_min = ti*tj
			nij_min = [i*j]
			i_min= [i]
			j_min = [j]
		elif abs(2000000-ti*tj) == abs(2000000 - tij_min):
			nij_min.append(i*j)
		if (ti*tj > 2000000):
			break

print i_min,j_min,nij_min, tij_min

