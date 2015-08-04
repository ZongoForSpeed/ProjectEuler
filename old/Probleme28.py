#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def spiral1(n):
	result = 0
	if (n==1):
		result = 1
	elif (n%2 == 2):
		result = 0
	else:
		k = (n**2 - (n-2)**2)/4
		print k
		result = 2*(n**2)-2*k + spiral1(n-2)
	return result;

def spiral2(n):
	result = 0
	if (n==1):
		result = 1
	elif (n%2 == 2):
		result = 0
	else:
		k = (n**2 - (n-2)**2)/4
		print k
		result = 2*(n**2)-4*k + spiral2(n-2)
	return result;


n = spiral1(1001) + spiral2(1001) - 1 
print n
