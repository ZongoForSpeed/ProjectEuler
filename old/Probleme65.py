#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def liste_e(n):
	l = [2]
	for i in range(1,n + 1):
		l.append(1)
		l.append(2*i)
		l.append(1)
	return l[:n]

def digits(n):
	result = 0
	while n > 0:
		result = result + n%10
		n = n / 10
	return result

def e(n):
	l = liste_e(n)
	num = l[-1]
	den = 1
	for k in l[:-1][::-1]:
		d1 = num
		num = k * num + den
		den = d1
	print digits(num)
		
		
