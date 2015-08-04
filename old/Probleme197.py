#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

# ⌊2^30.403243784-x2⌋ × 10-9

def suivant(x):
	n = int(2.0**(30.403243784-x**2))
	return float(n) / 1000000000

def problem197():
	limite = int(sys.argv[1])
	n = 1
	u = -1
	up = suivant(u)
	while n < limite:
		upp = suivant(up)
		n = n + 1
		if u == upp:
			break
		u = up
		up = upp
	print n
	print u + up
	
problem197()
