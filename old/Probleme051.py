#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def diviseur(n):
	for i in xrange(2,int(math.sqrt(n))):
		if n%i == 0:
			return i
	return n

def estpremier(n):
	return n == diviseur(n)

def binaire(n):
	while n > 0:
		if n%10 not in [0,1]:
			return False
		n = n / 10
	return True

def digits(n):
	l = []
	while n > 0:
		l.append(n%10)
		n = n / 10
	return l[::-1]

def ndigits(n):
	l = 0
	while n > 0:
		l = l + 1
		n = n / 10
	return l

def number(l):
	n = 0
	k = 0
	for i in l[::-1]:
		n = n + i*10**k
		k = k + 1
	return n

def denombrer(l):
	if l == []:
		return []
	else:
		r1 = denombrer(l[1:])
		r0 = []
		if len(r1) == 0:
			r0.append([0])
			if l[0] == 1:
				r0.append([1])
		else:
			if l[0] == 1:
				for r in r1:
					c0 = copy.copy(r)
					c1 = copy.copy(r)
					c0.insert(0,0)
					c1.insert(0,1)
					r0.append(c0)
					r0.append(c1)
			else:
				for r in r1:
					r.insert(0,0)
					r0.append(r)
		return r0


def masque(n,b):
	l = digits(n)
	if l.count(b) == 0:
		return []
	else:
		m = []
		result = []
		for i in xrange(len(l)):
			if l[i] == b:
				m.append(1)
			else:
				m.append(0)
		ma = denombrer(m)
		ma.pop(0)
		for mi in ma:
			ni = number(mi)
			result.append((n-b*ni,ni))
		return result
		
def masques(n,limite):
	result = []
	for b in range(11-limite):
		result.extends(masque(n,b))
	return result

def crible(tableau):
        if not tableau or tableau[0]**2 > tableau[-1]: return tableau
        return tableau[:1] + crible([i for i in tableau if i%tableau[0]])

def problem51():
	limite = int(sys.argv[1])
	premier = crible(range(2,10))
	done = []
	n = 1
	found = False
	p_max = -1
	l_max = []
	while not found:
		n = n + 1
		print 'debut itération',n
		premier.extend(range(10**(n-1),10**n))
		premier = crible(premier)
		print 'fin crible'
		mask = []
		print 'recherche masque'
		for p in premier :
			if p not in done:
				for m in masque(p,limite):
					if m not in mask:
						mask.append(m)
				done.append(p)
		print 'traitement masque'		
		for m in mask:
			p0 = m[0]
			m0 = m[1]
			c = 0
			for i in range(10):
				p1 = p0+i*m0
				if p1 in premier and ndigits(p1) == n:
					c = c + 1
					l_max.append(p1)
			if c >= limite:
				p_max = l_max[0]
				found = True
				break
			else:
				l_max = []
		if found:
			break
		print 'fin itération',n
	print p_max
	print l_max
		


problem51()

