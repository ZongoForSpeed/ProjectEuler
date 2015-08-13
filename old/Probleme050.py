#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

limite = int(sys.argv[1])

liste = {}
decomp = {}
listeP1 = []
for i in range(2,limite):
	liste[i] = True
	decomp[i] = 0
for i in range(2,limite):
	if liste[i]:
		listeP1.append(i)
		for j in range(i**2,limite,i):
			liste[j] = False

taille = len(listeP1)
s = 0
i_limite = 0
while(s < limite):
	s+=listeP1[i_limite]
	i_limite+=1
print i_limite
i_max = 0
p_max = 0
for i in range(1,i_limite):
	for j in range(taille-i):
		p = 0
		for k in range(j,j+i):
			p+=listeP1[k]
			if p > limite:
				break
		if p > limite:
			break
		if p in listeP1 and i > i_max:
			p_max = p
			i_max = i
			print i_max, p_max
			break

print i_max, p_max
