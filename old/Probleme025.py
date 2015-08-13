#! /usr/bin/env python
#-*- coding: utf-8 -*-

from math import *

a, b, n = 0, 1, 1
while log(b,10) < 999:
#	print n,
#	print b
	a, b = b, a+b
	n=n+1

print n	

