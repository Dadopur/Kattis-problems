import math
while(1):
 x,n=int(input()),0
 if x==0:break
 elif x>0:n=1
 x,b=abs(x),1
 while b<=math.sqrt(x):
  b+=1
  p=1
  while p<33:
   p+=1 if n else 2
   if math.pow(b,p)==x:
    b=x
    print(p)
 if b!=x:print(1)