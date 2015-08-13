#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def carre(n):
	return (math.sqrt(n))%1 == 0

def solution(D):
	y = 1
	found = False
	while not found:
		x2 = 1 + D * y**2
		if carre(x2):
			found = True
			return int(math.sqrt(x2))	
		y = y + 1	

def problem66():
	limite = int(sys.argv[1])
	D_max = -1
	x_max = -1
	for D in xrange(2,limite + 1):
		if not carre(D):
			x = solution(D)
			print D, x
			if x > x_max:
				x_max = x
				D_max = D
	print D_max, x_max

def problem66b():
	limite = int(sys.argv[1])
	liste = [D for D in xrange(2,limite + 1) if not carre(D)]
	solutions = []
	y = 1
	while len(liste) > 0:
		for D in liste:
			x2 = 1 + D * y**2
			if carre(x2):
				sol = [D,int(math.sqrt(x2)),y]
				solutions.append(sol)
				liste.remove(D)
				print sol, len(liste)
		y = y + 1		
	S_max = -1
	x_max = -1
	for s in solutions:
		if s[1] > x_max:
			S_max = s
			x_max = s[1]
	print S_max

problem66b()
		
