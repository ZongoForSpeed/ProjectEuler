#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def factorielle(n):
	p = 1
	for i in xrange(1,n+1):
		p = p * i
	return p

def total(l):
	t = 0
	for s4 in xrange(0,l + 1,4):
		n4 = s4 / 4
		for s3 in xrange(0, l - s4 + 1, 3):
			n3 = s3 / 3
			for s2 in xrange(0, l - s3 - s4 + 1, 2):
				n2 = s2 / 2
				n1 = l - s2 - s3 - s4
				n = factorielle(n1 + n2 + n3 + n4)
				d = factorielle(n1) * factorielle(n2) * factorielle(n3) * factorielle(n4)
				t = t + (n/d)
	return t

print total(int(sys.argv[1]))
