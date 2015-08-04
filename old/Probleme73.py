#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def pgcd(a, b):
    if a % b == 0:
        return b
    return pgcd(b, a % b)

limite = int(sys.argv[1])

compteur = 0
for d in range(4,limite+1):
	nf1 = float(d)/3.0
	n1 = int(math.ceil(float(d)/3.0))
	nf2 = float(d)/2.0
	n2 = int(math.floor(float(d)/2.0))
	for n in range(n1,n2+1):
		if (pgcd(n,d) == 1):
			compteur = compteur + 1

print compteur


