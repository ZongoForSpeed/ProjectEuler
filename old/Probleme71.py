#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def _n(d):
	return int(math.ceil(3.0*d/7.0)-1)

limite = int(sys.argv[1])

d = 2
n_min = 0
d_min = 1
r_min = 1.0
while d <= limite:
	n = _n(d)
	r = 3.0/7.0 - float(n)/float(d)
	if (r>0 and r< r_min):
		print n, d, r
		r_min = r
		n_min = n
		d_min = d
	d = d + 1

print n_min, d_min, r_min
	
