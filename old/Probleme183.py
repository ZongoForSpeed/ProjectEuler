#~/usr/bin/python

import string
import sys
import math
import time
import decimal

def pgcd(a,b):
	if b == 0:
		return a
	else:
		return pgcd(b,a%b)

def power(a,b):
	if b == 0:
		return 1
	elif b == 1:
		return a
	elif b%2 == 0:
		return power(a**2,b/2)
	else:
		return a * power(a,b-1)

def P(n,k):
	return decimal.Decimal(str(n/k))**int(k)

def infini(n,k):
	d = pgcd(n,k)
	n1 = n / d
	k1 = k / d
	p = 2
	while k1 > 1:
		if k1%p == 0:
			if p not in [2,5]:
				return True
			else :
				k1 = k1 / p
		elif p > 5:
			return True
		else:
			p = p + 1
	return False

def terminating(n):
	k0 = decimal.Decimal(str(n))/decimal.Decimal(str(math.e))
	k_max = math.ceil(k0)
	p_max = P(n,k_max)
	k_min = math.floor(k0)
	p_min = P(n,k_min)
	k = 0
	if (p_max > p_min):
		k = k_max
	else:
		k = k_min
	return not infini(n,k)

def problem183():
	limite = int(sys.argv[1])
	sigma = 0
	print 11, terminating(11)
	print 8, terminating(8)
	for i in xrange(5,limite + 1):
		#print i
		if terminating(i):
			sigma = sigma - i
		else:
			sigma = sigma + i
	return sigma

print problem183()
	
	
	
	


