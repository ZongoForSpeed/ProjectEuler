#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

phi = (1.0+math.sqrt(5.0))/2.0
phi_prime = (1.0-math.sqrt(5.0))/2.0
sqrt5 = 1.0/math.sqrt(5.0)


def pendigital(n):
	l = []
	if n%10 == 0:
		return False
	while n > 0:
		l.append(n%10)
		n= n/10
	l.sort()
	if l == range(1,10):
		return True
	return False

def add(n,m):
	return (n+m)%10**9

def fibonacci(n):
	if n < 3: 
		return 0 + (0 < n)
	elif n%2: 
		return fibonacci(n / 2 + 1) ** 2 + fibonacci((n - 1) / 2) ** 2
	else: 
		return fibonacci(n / 2 + 1) ** 2 - fibonacci((n - 1) / 2) ** 2


p_courant = 1
p_ancien = 1
n = 2
found = False
while not found:
	p_nouveau = add(p_courant,p_ancien)
	n = n + 1
	if pendigital(p_nouveau):
		f = fibonacci(n)
		k = math.log(f,10)
		print n, k
		s = str(f)
		if pendigital(int(s[:9])):
			found = True
	p_ancien = p_courant
	p_courant = p_nouveau

print n
##print fibonacci(n)
		

