#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def lirefichier():
	fichier = sys.argv[1]
	encode = []

	for ligne in open(fichier):
		for i in ligne.split(','):
			encode.append(int(i))
	return encode

def decode(encode,passwd):
	resultat = []
	k = 0
	l = len(passwd)
	for e in encode:
		resultat.append(e ^ passwd[k%l])
		k+=1
	return resultat

accept = []



def valid(encode):
	for i in encode:
		if i not in accept:
			return False
	return True	

def affiche(encode):
	string = ''
	for i in encode:
		string = string + chr(i)
	return string

def problem59():
	encode = lirefichier()
	passwd = [ord('g'),ord('o'),ord('d')]
	code = decode(encode,passwd)
	print affiche(passwd), '---', affiche(code)
	somme = 0
	for i in code:
		somme+=i
	return somme

print problem59()
	

