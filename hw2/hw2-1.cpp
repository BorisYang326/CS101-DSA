//
// Created by Borisss_Yang on 2019/10/30.
//
#include<iostream>
using namespace std;
class Solution{
public:
    int size;
    int m_array[500000];
    Solution();
    int Find_pairs();
};
Solution::Solution(){
    cin>>size;
    for (int i = 0; i < size;i++){
        cin >>m_array[i];
    }
}
int Solution::Find_pairs(){
    int count_pairs = 0;
    int flag;
    int j;
    for (int i = 0; i < size;i++){
        flag =0;
        j=i+1;
        // count_pairs++;
        while (j < size){
            if (m_array[j] > m_array[i]){
                if(j!=i+1){count_pairs++;}
                break;
            }
            else{if (m_array[j] > flag){flag=m_array[j];}
                if(m_array[j] >= flag){
                    if(j!=i+1){count_pairs++;}
                    else{//do nothing/
                    }}
            }
            j++;
        }
    }
    return count_pairs+size-1;
}
int main(){
    // int m_array[500];
    // int size;
    // Solution solution;
    // x=solution.Find_pairs(solution);
    // cout<<x;
    // cin>>size;
    // for (int i = 0; i < size;i++){
    //     cin >>m_array[i];}
    // int count_pairs = 0;
    // for (int i = 0; i < size;i++){
    //     for (int j = i+1; j < size;j++){
    //         count_pairs++;
    //         if (m_array[j] > m_array[i]){
    //             break;
    //         }
    //         else if (m_array[j] > m_array[i]&&m_array[j] < m_array[i]){break;}
    //         else if(m_array[j] <= m_array[i]){count_pairs=count_pairs;}
    //         else{count_pairs=count_pairs;}
    // }
    // cout<<count_pairs;
    Solution x;
    cout<<x.Find_pairs();
    return 0;
}
