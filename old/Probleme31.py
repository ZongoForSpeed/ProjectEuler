#! /usr/bin/env python
#-*- coding: utf-8 -*-

import math
import sys
import string

compteur = 0
for i200 in range(0,201,200):
	for i100 in range(0,201-i200,100):
		for i50 in range(0,201 - (i200 + i100),50):
			for i20 in range(0,201 - (i200 + i100 + i50),20):
				for i10 in range(0,201 - (i200 + i100 + i50 + i20),10):
					for i5 in range(0,201 - (i200 + i100 + i50 + i20 + i10),5):
						for i2 in range(0,201 - (i200 + i100 + i50 + i20 + i10 + i5),2):
							for i1 in range(0,201 - (i200 + i100 + i50 + i20 + i10 + i5 + i2),1):
								if (i1 + i2 + i5 + i10 + i20 + i50 + i100 + i200 == 200):
									compteur = compteur + 1

print compteur
