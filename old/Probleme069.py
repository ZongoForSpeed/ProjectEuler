#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

euler = {}

def phi(n):
	if (n == 1):
		euler[n] = 1
		return 1	
	d = 2
	p = n
	found = False
	while not found:
		if (n%d == 0):
			found = True
		else:
			d = d + 1
	if (d == n):
		p = n - 1
	else:
		d_max = d
		k = 1
		while n%d_max == 0:
			d_max = d_max * d
			k = k + 1
		d_max = d_max/d
		if (n == d_max):
			p = (d - 1)*d**(k-2)
		else:
			p = euler[d_max] * euler[n/d_max]
	euler[n] = p
	return p

def problem69(n):
	i_max = 0
	i = 1
	r_max = 0.0
	while i <= n:
		r = float(i)/float(phi(i))
		if r > r_max:
			r_max = r
			i_max = i
			print i_max, r_max
		i = i + 1
	print 'resultat : ', i_max, r_max
	return i_max

limite = int(sys.argv[1])

print problem69(limite)
	
