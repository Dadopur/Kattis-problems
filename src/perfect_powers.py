import math
import sys

def pos_x(x):
    """Takes a pos number and finds what lowest exponent makes a perfect power (ex cube)"""
    sqrt_x = math.sqrt(x)
    b = 2
    # b can only go up to sqrt x cuz this is biggest b can be and still have a exponent b^p=x
    while(b <= sqrt_x):
        for p in range(1, 33):
            if(math.pow(b,p) == x):
                return p
        b +=1
    return 1

def neg_x(x):
    """Takes a neg number and finds what lowest exponent makes a perfect power (ex cube)"""
    sqrt_x = math.sqrt(abs(x))
    b = -2
    # b can only go up to sqrt x cuz this is biggest b can be and still have a exponent b^p=x
    while(abs(b) <= sqrt_x):
        # We only need to look at odd exponents (odd p) so +2 instead of 1
        for p in range(1, 33, 2):
            if(math.pow(b,p) == x):
                return p
        b -=1
    return 1

def main():
    while(True):
        x = int(sys.stdin.readline().strip())
        #x = int(input())
        if(x == 0):
            break
        elif(x > 0):
            print(pos_x(x))
        else:
            print(neg_x(x))

if __name__ == "__main__":
    main()