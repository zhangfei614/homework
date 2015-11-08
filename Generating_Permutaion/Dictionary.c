#include<stdio.h>
#include<string.h>
#include<time.h>
#define MAX_LENGTH 28

char candidate[MAX_LENGTH];

char* generate_string_dic(int* mid,int n,char* result)
{
    memset((void*)candidate,0,sizeof(char)*MAX_LENGTH);
    int i;
    for(i=1;i<=n;i++)
    {
        candidate[i]='a'+i-1;
    }
    for(i=n;i>=1;i--){
        int count = -1;
        int j=1;
        while(j<=n){
            if(candidate[j]!=0){
                count++;
                if(count == mid[i])
                    break;
            }
            j++;
        }
        result[n-i]=candidate[j];
        candidate[j]=0;
    }
    result[n]='\0';
    return result;
}
int isLast_dic(int* mid,int n){
    int i;
    for(i=1;i<=n;i++){
        if(mid[i]!=i-1) return 0;
    }
    return 1;
}

int* next_mid_dic(int* mid){
    mid[1]+=1;
    int i=1;
    while(mid[i]>=i)
    {
        mid[i+1]=mid[i+1]+mid[i]/i;
        mid[i]=mid[i]%i;
        i++;
    }
    return mid;
}

void dictionary_permutation(int n)
{
    int mid[MAX_LENGTH];
    char result[MAX_LENGTH];

    char* r = result;
    int*  m = mid;
    memset((void*)m,0,sizeof(int)*MAX_LENGTH);   //

    int sum = 0;

    while(1){
        r = generate_string_dic(m,n,r);
        //printf("%s\n",r);
        sum++;
        if(isLast_dic(m,n))
            break;
        m=next_mid_dic(m);
    }
    //printf("%d\n",sum);
}

int main(){
    int n;
    clock_t start,finish;
    double usedTime;
    while(scanf("%d",&n)==1){
        start = clock();
        dictionary_permutation(n);
        finish = clock();
        usedTime = (double)(finish-start)/CLOCKS_PER_SEC;
        printf("%f\n",usedTime);
    }
    return 0;
}
