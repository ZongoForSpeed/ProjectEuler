#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

unite = {0:'',1:'one',2:'two',3:'three',4:'four',5:'five',6:'six',7:'seven',8:'eight',9:'nine',
11:'eleven',12:'twelve',13:'thirteen',14:'fourteen',15:'fifteen',16:'sixteen',17:'seventeen',18:'eighteen',19:'nineteen'}

dizaine = {0:'',1:'ten',2:'twenty',3:'thirty',4:'forty',5:'fifty',6:'sixty',7:'seventy',8:'eighty',9:'ninety'}
cent = 'hundred'
mille = 'thousand'
et = 'and'

def nombre10(n):
	result = ''
	if (n > 9 or n < 0):
		result = ''
	else:
		result = unite[n]
	return result

def nombre100(n):
	result = ''
	if (n < 0 or n > 100):
		result = ''
	elif (n < 10):
		result = nombre10(n)
	elif (n > 10 and n < 20):
		result = unite[n]
	else:
		result = dizaine[n/10]
		if (n%10 != 0):
			result = result + nombre10(n%10)
	return result

def nombre1000(n):
	result = ''
	if (n < 0 or n > 1000):
		result = ''
	elif (n < 100):
		result = nombre100(n)
	else:
		result = nombre10(n/100) + cent
		if (n%100 != 0):
			result = result + et + nombre100(n%100)
	return result

somme=0
for i in range(1,1001):
	if (i == 1000):
		somme=somme+len('onethousand')
	else:
		somme=somme+len(nombre1000(i))

print somme
