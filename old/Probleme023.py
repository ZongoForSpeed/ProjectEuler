#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def sigma_diviseurs(n):
	s = 0
	for i in range(1,n):
		if (n%i == 0):
			s = s + i
	return s
	
def abundants(n):
	s = set([])
	for i in range(n):
		if (i < sigma_diviseurs(i)):
			s.add(i)
	return s


n = 28123

ab = abundants(n)

ab2 = set([])
for i in ab:
	for j in ab:
		ab2.add(i+j)
s = 0
for i in range(1,n):
	if (i not in ab2):
		s = s + i

print s
