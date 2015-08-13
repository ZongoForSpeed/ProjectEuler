#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

taille = int(sys.argv[1])
borne = int(sys.argv[2])

def factorielle(n):
	f = 1
	for i in range(1,n+1):
		f = f * i
	return f
def C(n,p):
	return factorielle(n)/(factorielle(n-p)*factorielle(p))

compteur = 0
for n in range(taille+1):
	for p in range(0,n+1):
		if (C(n,p)> borne):
			compteur = compteur + 1


print compteur

