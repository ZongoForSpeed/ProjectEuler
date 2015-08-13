#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def cycle(n):
	nombre = n
	taille = 0
	restes = []
	r = 1
	while (r not in restes):
		restes.append(r)
		while (r%nombre == r):
			r = r * 10
		r = r%nombre
	return restes


gagnant = 0
n_max = 0
for i in range(2,1000):
	if (i%2 != 0 and i%5 != 0):
		n = len(cycle(i))
		if (n > n_max):
			n_max = n
			gagnant = i

print gagnant
print n_max
