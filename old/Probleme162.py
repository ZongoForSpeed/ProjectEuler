s = 0
for n in xrange(3, 17): 
	s+=15 * 16**(n - 1) + 41 * 14**(n - 1) - (43 * 15**(n - 1) + 13**n)
 
print "Answer to PE162 = %X" % s
