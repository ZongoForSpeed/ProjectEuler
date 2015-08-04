#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math

n = 10000

diviseurs = {1:0}
for i in range(2,n+1):
	diviseurs[i] = 0
	for j in range(1,i):
		if (i%j == 0):
			diviseurs[i] = diviseurs[i] + j

print diviseurs

proper = []
for i in range(2,n+1):
	j = diviseurs[i]
	if (j != i and j < n):
		if (diviseurs[j] == i):
			proper.append(i)

print proper
somme = 0
for i in proper:
	somme=somme + i

print somme
		
		


