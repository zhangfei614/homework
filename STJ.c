#include<stdio.h>
#include<string.h>
#define MAX_LENGTH 28
#define RIGHT 1
#define LEFT 0
char* generate_string_stj(int* m,int n,char* r){
    int i;

    memset((void*)r,0,sizeof(char)*MAX_LENGTH);
    for(i=1;i<=n;i++){
        char t='a'+n-i;             // filled character
        int flag = -1;
        if(i == n || i== n-1)       // if it is 1 or 2,let it be left
            flag = LEFT;
        if((n+1-i)%2==0){           // if it is an even number
            if((m[i+1]+m[i+2])%2!=0){       //if b(i-1)+b(i-2) is an odd number,let it be right
                flag = RIGHT;
            }else{
                flag = LEFT;                //else,let it be left
            }
        }else{
            if(m[i+1]%2!=0){        // if it is an odd number
                flag = 1;                   //if b(i) is an odd number,let it be right
            }else{
                flag = 0;                   //else,let it be left
            }
        }
        int count = -1;             //to count the blank position
        int j;
        if(flag == RIGHT){          //to right
            for(j=0;j<n;j++){
                if(r[j]==0){
                    count++;
                    if(count==m[i])
                        break;
                }
            }
            r[j]=t;
        }else{                      //to left
            for(j=n-1;j>=0;j--){
                if(r[j]==0){
                    count++;
                    if(count==m[i])
                        break;
                }
            }
            r[j]=t;
        }
    }
    return r;
}

int* next_mid_stj(int* mid,int n){
    mid[1]+=1;
    int i=1;
    int weight = n-i+1;
    while(mid[i]>=weight){
       mid[i+1]=mid[i+1]+mid[i]/weight;
        mid[i]=mid[i]%weight;
        i++;
        weight--;
    }
    return mid;
}

int isLast_stj(int* mid,int n){
    int i;
    for(i=1;i<n;i++){
        if(mid[i]<=mid[i+1]) return 0;
    }
    return 1;
}

void stj_permutation(int n){

    int mid[MAX_LENGTH];
    char result[MAX_LENGTH];

    char* r = result;
    int*  m = mid;
    memset((void*)m,0,sizeof(int)*MAX_LENGTH);

    int sum = 0;
    while(1){

        r = generate_string_stj(m,n,r);
        printf("%s\n",r);
        sum++;
        if(isLast_stj(m,n))
            break;
        m=next_mid_stj(m,n);
    }
    printf("%d\n",sum);
}

int main(){
    stj_permutation(25);
    return 0;
}
