#include<iostream>
#define MAX_LENGTH 28

using namespace std;

char* generate_string(int* m,int n,char* r){
    for(int i=n;i>=1;i--){
        char t='a'+i-1;
        int flag = -1;
        if(i == 2 || i== 1)
            flag = 0;
        else if(i%2==0){
            if((mid[i-1]+mid[i-2])%2==0){
                flag = 1;
            }else{
                flag = 0;
            }
        }else{
            if(mid[i-1]%2==0){
                flag = 1;
            }else{
                flag = 0;
            }
        }
        int sum = -1;
        if(flag = 0){
            for(int j=0;j<=n;j++){
                if(r[j])
            }
        }
    }
}
void stj_permutation(int n){
    int mid[MAX_LENGTH];
    char result[MAX_LENGTH];
    for(int i=1;i<MAX_LENGTH;i++){
        mid[i]=0;
    }
    int sum = 0;
    char* r = result;
    int*  m = mid;
}

int main(){
    cout<<"Hello world"<<endl;
    return 0;
}

