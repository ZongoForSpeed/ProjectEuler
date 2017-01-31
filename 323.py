#!/usr/bin/env python

mc = {}
mem = {}

def choose(n, k):
    if k == 0 or k == n: return 1
    if (n, k) in mc: return mc[n,k]
    ret = 1
    k = min(k, n-k)
    for i in xrange(k): ret *= (n-i)
    for i in xrange(2, k+1): ret /= i
    mc[n, k] = mc[n, n-k] = ret
    return ret

def prob(bits, drops): #bits for number of bits, drops for water drops in a bucket (ya I am insane don't even try to understand)
    if (bits, drops) in mem: return mem[bits, drops]
    val = 2**(-bits)
    if drops == 1:
        mem[bits, drops] = val
        return val
    ret = 0
    for i in xrange(bits):
        ret += choose(bits, i)*val*prob(bits-i, drops-1)
    mem[bits, drops] = ret
    return ret

if __name__=='__main__':
    expect = 0
    for i in xrange(1, 1025):
        expect += i*prob(32, i)
    print expect
