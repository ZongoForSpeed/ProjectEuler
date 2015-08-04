#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy
import time

def factorielle(n):
	p = 1
	for i in xrange(1,n+1):
		p = p * i
	return p

def C(n,k):
	return factorielle(n)/(factorielle(n-k)*factorielle(k))


