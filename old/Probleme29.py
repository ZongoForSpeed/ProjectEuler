#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

s = set([])
n = 100
for i in range(2,n+1):
	for j in range(2,n+1):
		s.add(i**j)

print len(s)
		
