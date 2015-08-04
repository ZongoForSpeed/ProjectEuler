#~/usr/bin/python

import string
import sys
import math
import time

def pgcd(a,b):
	if b == 0:
		return a
	else:
		return pgcd(b,a%b)

def reduire(f):
	p = f[0]
	q = f[1]
	d = pgcd(p,q)
	if d == 1:
		return f
	else:
		return (p/d,q/d)

def carre(f):
	return (f[0]**2,f[1]**2)

def addition(a,b):
	return (a[0]*b[1]+a[1]*b[0],b[1]*a[1])

def soustraction(a,b):
	return (a[0]*b[1]-a[1]*b[0],b[1]*a[1])

def nulle(a):
	return a[0] == 0

def inferieur(a,b):
	return a[0]*b[1] <= a[1]*b[0]

def fractions(k):
	f = []
	for d in xrange(2,k+1):
		for n in xrange(1,d):
			if pgcd(d,n) == 1:
				f.append((n,d))
	return f

def inverse(x):
	return (x[1],x[0])

def golden1(x,y,z):
	return nulle(soustraction(addition(x,y),z))

def golden2(x,y,z):
	return nulle(soustraction(addition(carre(x),carre(y)),carre(z)))

def golden1p(x,y,z):
	return golden1(inverse(x),inverse(y),inverse(z))

def golden2p(x,y,z):
	return golden2(inverse(x),inverse(y),inverse(z))

def problem180():
	k = int(sys.argv[1])
	frac = fractions(k)
	solutions = []
	s = (0,1)
	for x in frac:
		for y in frac:
			if inferieur(x,y):
				for z in frac:
					t = reduire(addition(x,addition(y,z)))
					if t not in solutions:
						if golden1(x,y,z) or golden2(x,y,z) or golden1p(x,y,z) or golden2p(x,y,z):
							print x,y,z, t
							s = reduire(addition(s,t))
							solutions.append(t)
	
	print s, s[1] + s[0]

problem180()


