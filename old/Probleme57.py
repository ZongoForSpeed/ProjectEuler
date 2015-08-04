#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def next(a):
	a1 = a[0]
	a2 = a[1]
	return (a1+2*a2,a1+a2)

def digits(n):
	l = []
	while n > 0:
		l.append(n%10)
		n = n / 10
	return len(l)

def problem57(n):
	s = 0
	i = 0
	a = (1,1)
	while i < n:
		a = next(a)
		i = i + 1
		if (digits(a[0]) > digits(a[1])):
			s = s + 1
	return s

limite = int(sys.argv[1])

print problem57(limite)
	
