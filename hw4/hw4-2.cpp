#include <iostream>
using namespace std;
#include <string>
int compare(int a,int b,int c){
    int mid=a>=b ? a: b;
    int max=mid>=c ? mid:c;
    return max;
}
//int dp_match(int index_1,int index_2,int**dp_table){
//    if(index_1,index_2)
//    if(dp_table[index_1][index_2]!=NULL){ return dp_table[index_1][index_2];}
//    dp_table[index_1][index_2]=
//}

int hash_dic(char s){
    switch(s)
    {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        case '-':
            return 4;
        default:
            return NULL;
    }
};
int main(){
    int N=0;
    int M=0;
    cin>>N;
    string str_1;
    cin>>str_1;
    cin>>M;
    string str_2;
    cin>>str_2;
    int match_table[5][5]={{0,-3,-4,-2,-1},{-3,5,-1,-2,-1},{-4,-1,5,-3,-2},{-2,-2,-3,5,-2},{-1,-1,-2,-2,5}};
    int** dp_table= new int*[N];
    for (int k = 0; k < N; ++k) {
        dp_table[k]= new int[M];
        for (int t = 0; t < M; ++t) {
            dp_table[k][t]=-99999;
        }
    }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                dp_table[i][0]+=match_table[hash_dic(str_1[j])][hash_dic('-')];
            }
        }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp_table[0][i]+=match_table[hash_dic('-')][hash_dic(str_2[j])];
        }
    }


    for (int i = 0; i < N; i++) {
        for (int j = 0 ; j < M; j++) {
            dp_table[i][j]=compare(dp_table[i-1][j-1]+match_table[hash_dic(str_1[i])][hash_dic(str_2[j])],dp_table[i-1][j]+match_table[hash_dic(str_1[i])][hash_dic('-')],dp_table[i][j-1]+match_table[hash_dic('-')][hash_dic(str_2[j])]);

        }
    }
    for (int l = 0; l < N; ++l) {
        for (int i = 0; i < M; ++i) {
            cout<<dp_table[l][i]<<" ";
        }
        cout<<endl;
    }
    cout<<dp_table[hash_dic(str_1[N-1])][hash_dic(str_2[M-1])];
    

}