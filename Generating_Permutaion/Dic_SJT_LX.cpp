#include <iostream>
#include <utility>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <ctime>
using namespace std;

#define LEFT true
#define RIGHT false

int proxy_number[27];
bool flag[26];
void print_proxy_number(int n) {
    for (int i=1; i<n; ++i)
        cout << proxy_number[i] << " ";
    cout << endl;
}

bool next_permutation_by_decr(char* first, char* last)
{
    if (first == last || first+1 == last) return false;
    // now at least two elements
    // generate proxy number
    int len = last-first;
    int cnt;
    for (char* i = last-1; i>=first; --i) {
        cnt = 0;
        for (char *j = last-1; j>i; --j) {
            if (*i > *j) ++cnt;
        }
        proxy_number[*i-'a'] = cnt;
    }

    // get next proxy number
    // proxy_number[i]'s base is i+1
    int carry = 0;
    if (++proxy_number[len-1] == len) {
        carry = 1;
        proxy_number[len-1] = 0;
    }
    for (int i = len-2; i>=1; --i) {
        if (!carry) break;
        if (++proxy_number[i] == i+1) {
            carry = 1;
            proxy_number[i] = 0;
        } else {
            carry = 0;
        }
    }

    if (carry) { // overflow means a round is over
        std::reverse(first, last);
        return false;
    }

    // from proxy number to permutation
    memset(flag, 0, len);
    for (int i = len-1; i>=0; --i) {
        for (int j = len-1; j>=0; --j) {
            if (!flag[j]) {
                if (proxy_number[i] == 0) {
                    flag[j] = true; 
                    *(first+j) = 'a'+i;
                    break;
                }
                --proxy_number[i];
            }
        }
    }
    return true;
}


void print_flag(int n) {
    for (int i=1; i<n; ++i) {
        cout << flag[i] << " ";
    }
    cout << endl;
}

bool next_permutation_by_sjt(char* first, char *last) {
    int len = last-first;
    flag[1] = LEFT; // the seconde element always head left
    int cnt = 0;
    for (int i=len-1; i>=0; --i) {
        if (*(first+i) == 'b') break;
        if (*(first+i) == 'a') ++cnt;
    }
    proxy_number[1] = cnt;

    for (int i=2; i<len; ++i) {
        if (i&1) { // note we start from 0, means odd number need check previous 2 numbers
            if ((proxy_number[i-1]&1) ^ (proxy_number[i-2]&1)) { // odd => right
                flag[i] = RIGHT;
            } else {
                flag[i] = LEFT;                              // even => left
            }
        } else {
            if (proxy_number[i-1]&1) {
                flag[i] = RIGHT;
            } else {
                flag[i] = LEFT;
            }
        }
        cnt = 0;
        if (flag[i] == LEFT) {
            for (int j=len-1; j>=0; --j) {
                if (*(first+j) == 'a'+i) break;
                if (*(first+j) < 'a'+i) ++cnt;
            }
        } else {
            for (int j=0; j<len-1; ++j) {
                if (*(first+j) == 'a'+i) break;
                if (*(first+j) < 'a'+i) ++cnt;
            }
        }
        proxy_number[i] = cnt;
    }

    // find the max mobilable number
    bool isFound = false;
    int index;
    for (int i=len-1; i>=1; --i) {
       for (int j=0; j<len; ++j) {
           if (*(first+j) == 'a'+i) {
               if ( (j==0 && flag[i]==LEFT) ||
                    (j==len-1 && flag[i]==RIGHT) ||
                    (flag[i] == LEFT && *(first+j) < *(first+j-1)) ||
                    (flag[i] == RIGHT && *(first+j) < *(first+j+1))
                    ) {
                   isFound = false;
                   break;
               } else {
                   isFound = true;
                   index = j;
                   break;
               }
           }
       } 
       if (isFound) break;
    }
    if (!isFound) { // no element can move, which means the end of the round
        std::sort(first, last);
        return false;
    }

    // move the mobilable element
    bool direction = flag[*(first+index)-'a'];
    if (direction == LEFT) {
        std::iter_swap(first+index, first+index-1);
    } else {
        std::iter_swap(first+index, first+index+1);
    }
    return true;
}

const char *template_str = "abcdefghijklmnopqrstuvwxyz";
char perm_str[27];
/*
int main() {
    int n;
    while (cin >> n) {
        strncpy(perm_str, template_str, n);
        perm_str[n] = '\0';
        do {
            cout << perm_str << endl;
        } while(next_permutation_by_sjt(perm_str, perm_str+n));
    }

}
*/
int main(){
   int n;
   clock_t start,finish;
   double usedTime;
   while(scanf("%d",&n)==1){
       int sum = 0;
       start = clock();
       strncpy(perm_str, template_str, n);
       perm_str[n] = '\0';
       do {
           sum++;
       } while(next_permutation_by_sjt(perm_str, perm_str+n));
       finish = clock();
       usedTime = (double)(finish-start)/CLOCKS_PER_SEC;
       printf("%f\n",usedTime);
   }  
}

