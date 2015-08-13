#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string
import copy

n = 3       # Size of inner region
n2, n3, n4 = n**2, n**3, n**4

def lirefichier(fichier):
	lsudoku = []
	nb_lignes = 0
	for ligne in open(fichier):
		print nb_lignes,ligne
		if (nb_lignes%2 == 1):
			lsudoku.append(ligne.strip())
		nb_lignes+=1
	return lsudoku

def show(flatline):
    'Display grid from a string (values in row major order with blanks for unknowns)'
    fmt = '|'.join(['%s' * n] * n)
    sep = '+'.join(['-'  * n] * n)
    for i in range(n):
        for j in range(n):
            offset = (i*n+j)*n2
            print fmt % tuple(flatline[offset:offset+n2])
        if i != n-1:
            print sep

def _find_friends(cell):
    'Return tuple of cells in same row, column, or subgroup'
    friends = set()
    row, col = cell // n2, cell % n2
    friends.update(row * n2 + i for i in range(n2))
    friends.update(i * n2 + col for i in range(n2))   
    nw_corner = row // n * n3 + col // n * n
    friends.update(nw_corner + i + j for i in range(n) for j in range(0,n3,n2))
    friends.remove(cell)
    return tuple(friends)
friend_cells = map(_find_friends, range(n4))

def select_an_unsolved_cell(possibles, heuristic=min):
    # Default heuristic:  select cell with fewest possibilities
    # Other possible heuristics include:  random.choice() and max()
    return heuristic((len(p), cell) for cell, p in enumerate(possibles) if len(p)>1)[1]

def solve(possibles, pending_marks):
    # Apply pending_marks (list of cell,value pairs) to possibles (list of str).
    # Mutates both inputs.  Return solution as a flat string (values in row-major order)
    # or return None for dead-ends where all possibilites have been eliminated.
    for cell, v in pending_marks:
        possibles[cell] = v
        for f in friend_cells[cell]:
            p = possibles[f]
            if v in p:
                p = possibles[f] = p.replace(v, '')     # exclude value v from friend f
                if not p:
                    return None               # Dead-end:  all possibilities eliminated
                if len(p) == 1:
                    pending_marks.append((f, p[0]))

    # Check to see if the puzzle is fully solved (each cell has only one possible value)
    if max(map(len, possibles)) == 1:
        return ''.join(possibles)
    
    # If it gets here, there are still unsolved cells
    cell = select_an_unsolved_cell(possibles)
    for v in possibles[cell]:           # try all possible values for that cell
        ans = solve(possibles[:], [(cell, v)])
        if ans is not None:
            return ans

def sudoku(s):
	pending_marks = [(i,v) for i, v in enumerate(s) if v != '0']
	possibles = ['123456789'] * len(s)
	result = solve(possibles, pending_marks)
	return result[:3]
# ----- Examples -----
fichier = sys.argv[1]
lsudoku = lirefichier(fichier)
print lsudoku
result = 0
for given in lsudoku:
	r = sudoku(given)
	print r
	result+= int(r)

print result


