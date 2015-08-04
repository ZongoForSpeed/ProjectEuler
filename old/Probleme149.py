#!/usr/bin/env python3

########################################################################
#   Solves problem 149 from projectEuler.net.
#   Finds the maximum-sum subsequence in a matrix
#   Copyright (C) 2011  Santiago Alessandri
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#	
#   You can contact me at san.lt.ss@gmail.com
#   Visit my wiki at http://wiki.san-ss.com.ar
#   Visit my blog at http://blog.san-ss.com.ar
########################################################################

from collections import deque

def filler():
    stack_55 = deque()
    stack_24 = deque()
    for k in range(1, 56):
        s_k = (100003 - 200003 * k + 300007 * k ** 3) % 1000000 - 500000
        stack_55.append(s_k)
        if k >= 32:
            stack_24.append(s_k)
        if k == 10:
            yield -393027
        else:
            yield s_k
    for k in range(56, 4000001):
        s_k = (stack_24.popleft() + stack_55.popleft() + 1000000) % 1000000 - 500000
        stack_55.append(s_k)
        stack_24.append(s_k)
        if k == 100:
            yield 86613
        else:
            yield s_k

def max_subseq(seq):
    max_total = 0
    max_tmp = 0
    for s in seq:
        max_tmp = max(max_tmp + s, 0)
        max_total = max(max_total, max_tmp)
    return max_total

if __name__ == '__main__':
    SIZE = 2000
    gen = filler()
    matrix = []
    for i in range(SIZE):
        row = []
        for j in range(SIZE):
            row.append(next(gen))
        matrix.append(row)

    max_sum = 0
    #Checking horizontally
    for r in matrix:
        max_sum = max(max_sum, max_subseq(r))
        
    #Checking vertically
    for i in range(SIZE):
        r = (r[i] for r in matrix)
        max_sum = max(max_sum, max_subseq(r))

    #Checking diagonally right-down starting row 0
    for i in range(SIZE):
        r = (matrix[j][j + i] for j in range(0, SIZE - i))
        max_sum = max(max_sum, max_subseq(r))
        
    #Checking diagonally right-down starting col 0
    for i in range(1, SIZE):
        r = (matrix[j + i][j] for j in range(0, SIZE - i))
        max_sum = max(max_sum, max_subseq(r))
        
    #Checking anti-diagonally starting col 0
    for i in range(SIZE):
        r = (matrix[i - j][j] for j in range(0, i + 1))
        max_sum = max(max_sum, max_subseq(r))
    #Checking anti-diagonally starting row 1999
    for i in range(1,SIZE):
        r = (matrix[SIZE - 1 - j][i + j] for j in range(0, SIZE - i))
        max_sum = max(max_sum, max_subseq(r))

    print("The result is:", max_sum)
