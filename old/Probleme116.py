#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def total(l):
	t = 0
	c = {}
	for i in xrange(0,l+1):
		c[0,i] = 1
		c[i,0] = 1
	for i in xrange(1,l+1):
		for j in xrange(1,l+1):
			c[i,j] = c[i,j-1] + c[i-1,j]

	for i in xrange(2,4):
		m = l/i
		p = 0
		for j in xrange(1,m + 1):
			p = p + c[l-j*i,j]
		t = t + p
	return t

print total(int(sys.argv[1]))
