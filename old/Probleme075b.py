#=========================================================================
#
# Python Source File -- Created with SAPIEN Technologies PrimalScript 4.1
#
# NAME: problem 75
#
# AUTHOR: patrol , ustc
# DATE : 2008-8-14
#
# COMMENT:
#
#=========================================================================
def mycmp(x,y):
    if x[1]>y[1]:
        return 1
    elif x[1]<y[1]:
        return -1
    else:
        return 0
def Gcd(a,b):
    if b==0:
        return a
    return Gcd(b,a%b)   
def enterDict(k,L,e):
    global lDict
    L = k*L
    e = map(lambda x:k*x,e)
    if L not in lDict:
        lDict[L]=[1,L,e]
    else:
        tmpList=lDict[L]
        flag=True
        for i in tmpList[2:]:
            if i==e:
                flag=False
                break
        if flag:
            tmpList[0] += 1
            tmpList.append(e)
            lDict[L]=tmpList

lDict={}
N=2000000
for m in range(1,1000):
    for n in range(1,m):
        a=2*m*n
        b=m**2-n**2
        c=m**2+n**2
        l=a+b+c
        k=N/l
        for i in range(1,k+1):
            abc=[a,b,c]
            abc.sort()
            enterDict(i,l,abc)
count = 0
valuesList=lDict.values()
valuesList.sort(reverse=False,cmp=mycmp)
for value in valuesList:
#       print value
    if value[0]==1:
        count += 1
print 'answer=%d'%count
