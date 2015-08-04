#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

carre = []
cube = []
tesseract = []

limite = int(sys.argv[1])

def crible(n):
	limite_crible = int(math.sqrt(n))
	premier = {}
	for p in range(2,limite_crible + 1):
		premier[p] = True
	for p in range(2,limite_crible + 1):
		if premier[p]:
			if p**2 <= limite:
				carre.append(p**2)
			if p**3 <= limite:
				cube.append(p**3)
			if p**4 <= limite:
				tesseract.append(p**4)
			for i in range(2*p,limite_crible + 1,p):
				premier[i] = False
	carre.sort()
	cube.sort()
	tesseract.sort()
	

def problem87():
	solution = set([])
	crible(limite)
	for p4 in tesseract:
		for p3 in cube:
			if (p4 + p3 > limite):
				break
			for p2 in carre:
				if (p4 + p3 + p2 > limite):
					break
				solution.add(p4 + p3 + p2)
				#print p4,p3,p2
	#print solution
	return len(solution)

print problem87()
				
