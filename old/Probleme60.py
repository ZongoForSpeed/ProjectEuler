#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def crible(n):
	premier = []
	temp = [True] * (n + 1)
	temp[0] = False
	temp[1] = False
	for i in xrange(2,int(math.sqrt(n) + 1)):	
		if temp[i]:
			
			for j in xrange(i**2,n,i):
				temp[j] = False
	premier.extend([i for i in xrange(2,n) if temp[i]])
	return premier

def concat(n,m):
	return int(str(n)+str(m))
	
def estpremier(p,premier):
	if p > premier[-1]:
		for pi in premier:
			if p%pi == 0:
				return False
		return True
	else:
		return p in premier

def problem60():
	taille = int(sys.argv[1])
	limite = int(sys.argv[2])
	t = time.time()
        premier = crible(taille)
        print time.time() - t

	print 'taille : ', len(premier)

	t = time.time()
	groupe2 = []

	for p in premier:
		for pi in [pi for pi in premier if pi < p]:
			pp = concat(pi,p)
			if estpremier(concat(pi,p),premier) and estpremier(concat(p,pi),premier) :
				groupe2.append([pi,p])
	print 'fin 2', len(groupe2)
	groupe3 = []
	for pp in groupe2:
		for pi in [pi for pi in premier if pi < pp[0]]:
			ok = True
			for p in pp:
				if not estpremier(concat(pi,p),premier) or not estpremier(concat(p,pi),premier) or pi == p:
					ok = False
					break
			if ok:
				g = [pi]
				g.extend(pp)
				g.sort()
				if g not in groupe3:
					groupe3.append(g)

	print 'fin 3', len(groupe3)
	groupe4 = []
	for pp in groupe3:
		for pi in [pi for pi in premier if pi < pp[0]]:
			ok = True
			for p in pp:
				if not estpremier(concat(pi,p),premier) or not estpremier(concat(p,pi),premier) or pi == p:
					ok = False
					break
			if ok:
				g = [pi]
				g.extend(pp)
				g.sort()
				if g not in groupe4:
					groupe4.append(g)
	print 'fin 4', len(groupe4)

	groupe5 = []
	for pp in groupe4:
		for pi in [pi for pi in premier if pi < pp[0]]:
			ok = True
			for p in pp:
				if not estpremier(concat(pi,p),premier) or not estpremier(concat(p,pi),premier) or pi == p:
					ok = False
					break
			if ok:
				g = [pi]
				g.extend(pp)
				g.sort()
				if g not in groupe5:
					groupe5.append(g)
	print 'fin 5', len(groupe5)
	s = []
	for g in groupe5:
		s.append(sum(g))
	s.sort()
	print time.time() - t
	print s[0]
	print groupe5

problem60()
		
