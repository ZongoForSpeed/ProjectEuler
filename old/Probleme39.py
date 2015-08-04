#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

n_max = 0
p_max = 0

for p in range(1,1000):
	nb = 0
	for a in range(1,p+1):
		for b in range(a+1,p+1):
			c = p - (a +b)
			if (c > 0 and c > b and c > a and (a**2 + b**2 == c**2)):
				nb = nb + 1
	if (nb > n_max):
		n_max = nb
		p_max = p

print p_max

