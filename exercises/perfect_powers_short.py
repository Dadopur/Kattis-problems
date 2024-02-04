import math
while(1):
 x=int(input())
 n=0
 if(x==0):break
 elif(x>0):n=1
 x=abs(x)
 b=1
 while b<=math.sqrt(x):
  b+=1
  p=1
  while p<33:
   if n: p+=1
   else: p+=2
   if math.pow(b,p)==x:
    b=math.inf
    print(p)
 if b!=math.inf:print(1)