#! /usr/bin/env python
#-*- coding: utf-8 -*-

from math import *
somme = 0
for i in range(1,1001):
	somme = somme + i**i 
	somme = somme%10000000000

print somme
