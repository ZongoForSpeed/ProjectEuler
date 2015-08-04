#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

valeur = {'I' : 1, 'V': 5, 'X' : 10, 'L' : 50, 'C' : 100, 'D' : 500, 'M':1000} 

unite = {0: '',1: 'I',2: 'II',3: 'III',4: 'IV',5: 'V',6: 'VI',7: 'VII',8: 'VIII',9: 'IX'}
dizaine = {0: '', 1: 'X', 2: 'XX',3: 'XXX',4: 'XL',5: 'L',6: 'LX',7: 'LXX',8: 'LXXX',9: 'XC'}
centaine = {0: '', 1: 'C',2: 'CC',3: 'CCC',4: 'CD',5: 'D',6: 'DC',7: 'DCC',8: 'DCCC',9: 'CM'}
millier = {0: '',1: 'M',2: 'MM',3: 'MMM',4: 'MMMM',5: 'MMMMM',
	6: 'MMMMMM',7: 'MMMMMMM',8: 'MMMMMMMM',9: 'MMMMMMMMM'}

def convertir(s):
	result = 0
	n = len(s)
	for i in range(n):
		r = valeur[s[i]]
		found = False
		for c in s[(i+1):]:
			if valeur[c] > r:
				found = True
				break
		if not found:
			result = result + r
		else:
			result = result - r
	return result

def romain(n):
	result = ''
	result = result + millier[n/1000]
	n = n%1000
	result = result + centaine[n/100]
	n = n%100
	result = result + dizaine[n/10]
	n = n%10
	result = result + unite[n]
	return result
		

fichier = sys.argv[1]

result = 0
for ligne in open(fichier):
	sold = ligne.strip()
	n = convertir(sold)
	s = romain(n)
	print sold, '->', n, '->', s
	result = result + len(sold) - len(s)

print result


