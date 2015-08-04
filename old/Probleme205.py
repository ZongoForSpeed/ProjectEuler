import decimal
 
pdict={}
cdict={}
 
pcount=0
ccount=0
 
for i in range(1,5):
 for j in range(1,5):
  for k in range(1,5):
   for m in range(1,5):
    for n in range(1,5):
     for l in range(1,5):
      for h in range(1,5):
       for q in range(1,5):
        for g in range(1,5):
         pcount=pcount+1
         sum=i+j+k+m+n+l+h+q+g
         if pdict.has_key(sum):
          pdict[sum]=pdict[sum]+1
         else:
          pdict[sum]=1
 
for i in range(1,7):
 for j in range(1,7):
  for k in range(1,7):
   for m in range(1,7):
    for n in range(1,7):
     for l in range(1,7):
      ccount=ccount+1
      sum=i+j+k+m+n+l
      if cdict.has_key(sum):
       cdict[sum]=cdict[sum]+1
      else:
       cdict[sum]=1
 
 
pro=0
decimal.getcontext().prec= 15
c=decimal.Decimal(ccount)
p=decimal.Decimal(pcount)
 
 
for py in pdict.keys():
 for cub in cdict.keys():
  if py>cub:
 
   pry = decimal.Decimal(pdict[py])
   cube = decimal.Decimal(cdict[cub])
   prob=((pry*cube)/c)/p
   pro=pro+prob
 
print pro
raw_input()
