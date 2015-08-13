#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

def puissance(a,n,k):
	if (n == 0):
		return 1
	elif (n == 1):
		return a%k
	elif (n%2 == 0):
		return puissance(a*a,n/2,k)%k
	else:
		return (a*puissance(a,n-1,k))%k

print (28433 * puissance(2,7830457,10**10)+1)%10**10

