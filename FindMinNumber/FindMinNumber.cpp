#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include "config.h"
#define BYTE_LENGTH 8
using namespace std;

void print_bitmap(unsigned char* bitmap,unsigned int bytes_length){
    cout<<"The legth of bit map is "<<bytes_length<<endl;
    for(unsigned int i = 0 ;i<bytes_length;i++){
        for(int j=0;j<BYTE_LENGTH;j++){
            if(bitmap[i] & (1<<j)){
                cout<<1;
            }else{
                cout<<0;
            }
        }
        cout<<endl;
    }
}

int main(){

    clock_t start,finish;
    start = clock();
    
        
    unsigned int MAX_RESULT;
    if(NUMBERS_COUNT < MAX_NUMBER){
        MAX_RESULT = NUMBERS_COUNT;
    }else{
        MAX_RESULT = MAX_NUMBER;
    }
    
    unsigned char* bitmap;
    unsigned int bytes_length = MAX_RESULT/BYTE_LENGTH + 1;
    bitmap =(unsigned char*) malloc(bytes_length);
    memset(bitmap,0,bytes_length);
    
    ifstream fin("data.in",ios::in|ios::binary);
    
    unsigned int t;
    unsigned int i;
    unsigned int min = 0;
    for(i=0;i<NUMBERS_COUNT;i++){
        fin>>t;
        if(t>=MAX_RESULT) continue;
        bitmap[t/BYTE_LENGTH] = bitmap[t/BYTE_LENGTH] | (1<<(t%BYTE_LENGTH));
        if(t==min) min++;
    }
    // print_bitmap(bitmap,bytes_length);
    for(;min<MAX_RESULT;min++){
        if(!(bitmap[min/BYTE_LENGTH] & (1<<(min%BYTE_LENGTH))))
            break;
    }
    // for(i=min/BYTE_LENGTH;i<bytes_length;i++){
    //     if(bitmap[i] ^ 0xff){
    //         int j;
    //         for(j=0;j<BYTE_LENGTH;j++){
    //             if(!(bitmap[i] & (1<<j))) break;
    //         }
    //         min = i*BYTE_LENGTH+j;
    //         break;
    //     }else{
    //         continue;
    //     }
    // }
    cout<<min<<endl;
    delete(bitmap);
    fin.close();
    
    finish = clock();
    cout<<"The tiem of this program is "<<(finish-start)<<endl;
    return 0;
}
