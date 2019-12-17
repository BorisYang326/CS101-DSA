#include <iostream>
using namespace std;
void quickSort(int s[], int l, int r) {
    if (l < r) {
        int i = l, j = r, x = s[l];
        while (i < j) {
            while (i < j && s[j] >= x)
                j--;
            if (i < j)
                s[i++] = s[j];
            while (i < j && s[i] < x)
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}
int main(){
    int N,M;
    cin>>N>>M;
    int* dragon_hp= new int[N];
    int* knight_price =new int[M];
    for (int i = 0; i <N ; ++i) {
        cin>>dragon_hp[i];
    }
    for (int j = 0; j <M ; ++j) {
        cin>>knight_price[j];
    }
    quickSort(dragon_hp,0,N-1);
    quickSort(knight_price,0,M-1);
    int p=0;
    int q=0;
    int cnt=0;
    while(p<N && q<M){
        if(dragon_hp[p]<=knight_price[q]){
            cnt+=knight_price[q];
            q++;
            p++;
        } else{q++;}
    }
    if(p==N){cout<<cnt;}
    else{cout<<"you died!";}

    return 0;
}