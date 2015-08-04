#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def solutions(n):
	c = 0
	for i in xrange(n+1,2*n+1):
		if n*i%(i-n) == 0:
			c = c + 1
	return c

def problem108():
	limite = int(sys.argv[1])
	found = False
	n = 2
	while not found:
		s = solutions(n)
		print n,s
		if s >= limite:
			found = True
		else:
			n = n + 1
	print n

problem108()
		
