#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def bisextile(a):
	result = True
	if (a%4 != 0):
		result = False
	elif (a%100 !=0):
		result = True
	elif (a%400 !=0):
		result = False
	else:
		result = True
	return result	

def longueur_mois(m,a):
	n = 0;
	if (m == 2):
		if (bisextile(a)):
			n = 29
		else:
			n = 28
	elif (m == 4 or m == 6 or m == 9 or m == 11):
		n = 30
	else:
		n = 31
	return n

def problem19():
	result = 0
	jour = 1
	annee = 1901
	mois = 1
	while (annee < 2001):
		if (jour%7 == 0):
			result = result + 1
		jour = jour + longueur_mois(mois,annee)
		if (mois == 12):
			mois = 1
			annee = annee + 1
		else:
			mois = mois + 1
	return result

print problem19()

