#include <iostream>
#define MAX_LENGTH 28
using namespace std;
char* generate_string_dictionary(int* mid,int n,char* result)
{
    char candidate[MAX_LENGTH];
    for(int i=0; i<n; i++)
    {
        candidate[i]='a'+i;
    }
    for(int i=n-1; i>=0; i--)
    {
        int sum=-1;
        int j=0;
        for(; j<n; j++)
        {
            if(candidate[j]!='*')
            {
                sum++;
                if(sum==mid[i])
                    break;
            }
        }
        result[i]=candidate[j];
        candidate[j]='*';
    }
    return result;
}
int* next_mid(int* mid)
{
    mid[0]+=1;
    int i=0;
    while(mid[i]>=i+1)
    {
        mid[i+1]=mid[i+1]+mid[i]/(i+1);
        mid[i]=mid[i]%(i+1);
        i++;
    }
    return mid;
}

int isLast(char* r,int n)
{
    for(int i=0; i<n-1; i++)
    {
        if(r[i]>r[i+1]) return 0;
    }
    return 1;
}

void dictionary_permutation(int n)
{
    int mid[MAX_LENGTH];
    char result[MAX_LENGTH];
    for(int i=0; i<MAX_LENGTH; i++)
    {
        mid[i]=0;
    }
    int sum = 0;
    char* r = result;
    int*  m = mid;
    do
    {
        r = generate_string_dictionary(m,n,r);
        sum++;
        for(int i=n-1; i>=0; i--)
        {
            cout<<result[i];
        }
        cout<<endl;
        m = next_mid(m);
    }
    while(!isLast(r,n));
    cout<<sum<<endl;
}
//
//int main()
//{
//    dictionary_permutation(10);
//    return 0;
//}
