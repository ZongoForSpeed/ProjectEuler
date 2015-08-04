#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def digits(n):
	s = 0
	while (n > 0):
		s = s + n%10
		n = n/10
	return s

def valid(n):
	if n%10 == 0:
		return False
	d = digits(n)
	if d == 1:
		return False
	while n > 1:
		if n%d == 0:
			n = n/d
		else:
			return False
	return True

def problem119():
	limite = int(sys.argv[1])
	a = []
	n = 10
	l = 0
	while l < limite:
		if valid(n):
			print n
			a.append(n)
			l = l + 1
		n = n + 1
	print a

problem119()
