#include<iostream>
#include<cstdio>
#include<bitset>
#define LENGTH 10

using namespace std;

int main(){

    bitset<LENGTH> b;
    unsigned long long min = 0;
    unsigned long long t;
    unsigned long long i;
    for(i=0;i<LENGTH;i++){
        scanf("%I64d",&t);
        if(t>=LENGTH) continue;
        b[t]=1;
        if(t==min) min++;
    }
    for(;min<LENGTH;i++){
        if(b[min]==0){
            break;
        }
    }
    printf("%I64d\n",min);
    return 0;
}
