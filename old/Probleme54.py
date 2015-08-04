#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

carte = {'A': 14,'K': 13,'J': 11,'Q':12, '3': 3, '2': 2,'5': 5, '4': 4, '7': 7, '6': 6, '9': 9, '8': 8,'T':10}

figure = {'FullHouse': 7, 'Poker': 8, 'QuinteFlush': 9, 'DPaire': 3, 'Paire': 2, 'Flush': 6, 'Quinte': 5, 'HC': 1, 'Brelan': 4, 'RoyalFlush': 10}

couleur = {'S':4,'H':3,'D':2,'C':1}

def transforme(l):
	result = []
	for c in l:
		result.append([carte[c[0]],couleur[c[1]]])
	return result

def suite(l):
	l.sort()
	if (l[0][0] + 1 == l[1][0] and l[1][0] + 1 == l[2][0] and l[2][0] + 1 == l[3][0] and l[3][0] + 1 == l[4][0]):
		return True
	else:
		return False

def couleur(l)
	if (l[0][1] == l[1][1] and l[1][1] == l[2][1] and l[2][1] == l[3][1] and l[3][1] == l[4][1]):
		return True
	else:
		return False

def carre(l):
	l.sort()
	if (l[0][0] == l[1][0] and l[1][0] == l[2][0] and l[2][0] == l[3][0]):
		return True
	elif (l[1][0] == l[2][0] and l[2][0] == l[3][0] and l[3][0] == l[4][0]):
		return True
	else:
		return False
	



def figure(l):
	
