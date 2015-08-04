#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
from copy import copy

def odd(n):
	while n > 0:
		if n%2 == 0:
			return False
		n = n / 10
	return True

def reversible(n):
	if n%10 != 0:
		r = int(str(n)[::-1])
		if odd(r+n):
			return True
	return False


def problem145():
	limite = int(sys.argv[1])
	compteur = 0
	for i in xrange(limite):
		if reversible(i):
			compteur = compteur + 1
	print compteur

problem145()

