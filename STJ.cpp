#include<iostream>
#include<cstring>
#define MAX_LENGTH 28

using namespace std;

char* generate_string_stj(int* m,int n,char* r){
    for(int i=1;i<=n;i++){
        char t='a'+n-i;
        int flag = -1;
        if(i == n || i== n-1)       //如果我为1，2直接定义为向左
            flag = 0;
        if((n+1-i)%2==0){
            if((m[i+1]+m[i+2])%2!=0){
                flag = 1;
            }else{
                flag = 0;
            }
        }else{
            if(m[i+1]%2!=0){
                flag = 1;
            }else{
                flag = 0;
            }
        }
        int sum = -1;
        int j;
        if(flag == 1){
            for(j=0;j<n;j++){
                if(r[j]==0){
                    sum++;
                    if(sum==m[i])
                        break;
                }
            }
            r[j]=t;
        }else{
            for(j=n-1;j>=0;j--){
                if(r[j]==0){
                    sum++;
                    if(sum==m[i])
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
    for(int i=1;i<n;i++){
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
    while(true){
        memset((void*)r,0,sizeof(char)*MAX_LENGTH);
        r = generate_string_stj(m,n,r);
        cout<<r<<endl;
        sum++;
        if(isLast_stj(m,n))
            break;
        m=next_mid_stj(m,n);
    }
    cout<<sum<<endl;
}

int main(){
    stj_permutation(7);
    return 0;
}

