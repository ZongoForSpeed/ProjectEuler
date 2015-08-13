#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

from decimal import *

getcontext().prec = 300

definition = 100

def digits(n):
	r = []
	while n>0:
		r.append(n%10)
		n = n / 10
	l = r[::-1]
	#print l[:100]
	return l[:100]

def problem80():
	limite = int(sys.argv[1])
	result = 0
	for i in xrange(2,limite+1):
		if i not in [4,9,16,25,36,49,64,81,100]:
			a = int((Decimal(i*(10**(2*definition+2)))**Decimal("0.5")))
			#print a
			result = result + sum(digits(a))
	return result

print problem80()

