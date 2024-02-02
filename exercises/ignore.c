#include <stdio.h>
int main() {
    int n;
    int k = 0;
    do{
        scanf("%d", &n);
        while(n != k){
            k = n;
            printf("%c", "0125689"[n%7]);
            n/=7;
        }
    } while(n);
}