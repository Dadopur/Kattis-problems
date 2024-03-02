#include <stdio.h>
int main(){int n;while(scanf("%d",&n)!=EOF){while(n>0){printf("%c","0125986"[n%7]);n/=7;}printf("\n");}}