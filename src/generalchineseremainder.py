"""
Using the general chinese remainder theorem to find a number X that is congruent to a mod n and b mod m.
The time complexity is O(log(nm)) where n and m are the numbers to find the remainder of (not always relative prime).

Author: Daniel Purgal
"""

def gcd_extended(a, b):
    """
    Extended Euclidean algorithm to find the greatest common divisor of a, b,
    and the coefficients x and y of the equation ax + by = gcd(a, b).
    """
    if b == 0:
        return a, 1, 0
    gcd, x1, y1 = gcd_extended(b, a % b)
    x = y1
    y = x1 - y1 * (a // b)
    return gcd, x, y

def chinese_remainder(a, n, b, m):
    """
    Find what number X is congruent to a mod n and b mod m. 
    Return -1, -1 if there is no solution.
    """
    k = n * m
    gcd, x, y = gcd_extended(n, m)
    M = k // gcd
    if (a -b) % gcd != 0:
        return -1, -1
    
    X = ((a * m * y + b * n * x) // gcd) % M
    return X, M

def main():
    num_tests = int(input())
    for _ in range(num_tests):
        a, n, b, m = map(int, input().split())
        result = chinese_remainder(a, n, b, m)
        if result[0] == -1 and result[1] == -1:
            print("no solution")
        else:
            print(result[0], result[1])

if __name__ == "__main__":
    main()