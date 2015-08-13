#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

def match(l1,l2):
	return l1[2] == l2[1]

def triplets(n):
	t = []
	for a in xrange(1,11):
		for b in xrange(1,11):
			if a == b:
				continue
			for c in xrange(1,11):
				if c == a or b == c:
					continue
				if a + b + c == n:
					t.append([a,b,c])
	return t

def minus(n1,n2):
	return n1[0] <= n2[0]
	
def probleme68():
	t = triplets(int(sys.argv[1]))
	solution = []
	for t1 in t:
		for t2 in t:
			if not match(t1,t2) or not minus(t1,t2):
				continue
			for t3 in t:
				if not match(t2,t3) or not minus(t1,t3):
					continue
				for t4 in t:
					if not match(t3,t4) or not minus(t1,t3):
						continue
					for t5 in t:
						if match(t4,t5) and match(t5,t1) and minus(t1,t5):
							l = copy.copy(t1)
							l.extend(t2)
							l.extend(t3)
							l.extend(t4)
							l.extend(t5)
							if len(set(l)) == 10:
								solution.append(l)
	for s in solution:
		l = ''
		for i in s:
			if i == 10:
				l = l + str(0)
			else:
				l = l + str(i)
		print l



probleme68()
