#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def inverse(n):
	return int(str(n)[::-1])

def palindrome(n):
	return n == inverse(n)

def Lychrel(n):
	limite = 50
	i = 1
	s = n + inverse(n)
	while (i <= limite):
		if (palindrome(s)):
			return False
		else:
			s = s + inverse(s)
			i = i + 1
	return True 

def problem55():
	compteur = 0
	for i in range(1,10000):
		if (Lychrel(i)):
			compteur = compteur+1
			print i
	return compteur
	
print problem55()
	

