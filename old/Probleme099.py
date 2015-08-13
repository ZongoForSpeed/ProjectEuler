#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

fichier = sys.argv[1]

i = 1
l_max = 0.0
i_max = 0
liste = []
for ligne in open(fichier):
	s = ligne.split(',')
	liste.append(s)
	l = float(s[1])*math.log(float(s[0]))
	if l > l_max:
		l_max = l
		i_max = i
	i = i + 1

print i_max
	
