//
// Created by Borisss_Yang on 2019/12/29.
//
#include <iostream>

using namespace std;
long LEN = 1048576;// 2^20

class hash_block {
public:
    long key, value;

    hash_block(long k = 0, long v = -1);
};

hash_block::hash_block(long k, long v) : key(k), value(v) {}

class hash_map {
public:
    long size = LEN;

    hash_block **hash_table;

    hash_map();

    ~hash_map();

    long get_value(long key);

    void set_value(long key, long value);
};

hash_map::hash_map() {
    hash_table = new hash_block *[size]();
}


hash_map::~hash_map() {
    for (int i = 0; i < size; i++)
        if (hash_table[i] != NULL) { delete hash_table[i]; }
    delete[] hash_table;
}

void hash_map::set_value(long key, long value) {
    int index = key & (size - 1);
    while (hash_table[index] && hash_table[index]->key != key) { index = (index + 1) & (size - 1); }
    if (hash_table[index] == NULL) { hash_table[index] = new hash_block(key, value); }
    else {
        hash_table[index]->value += value;
        hash_table[index]->key = key;
    }

}

long hash_map::get_value(long key) {
    int index = key & (size - 1);
    while (hash_table[index] && hash_table[index]->key != key)
        index = (index + 1) & (size - 1);           // SIZE不够大时，这里也面临死循环的问题
    return hash_table[index] ? hash_table[index]->value : 0;      // 注意这里需要判断key不存在的情况
}

long gcd(long a, long b) {
    if (a == 0 | b == 0) { return 0; }
    if (a < b) { swap(a, b); }
    long c = b;
    while (a % b != 0)    //for(;m%n!=0;)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return c;
}

//long* convert(long* seq,long begin,long len){
//    long* k_arr= new long[len];
//    for (long i = 0; i <len ; ++i) {
//        k_arr[i]=0;
//    }
//    k_arr[0]=seq[begin];
//    long cnt=1;
//    while(cnt+begin<len){
//        if(k_arr[cnt-1]==1){ break;}
//        else{
//            k_arr[cnt]=gcd(k_arr[cnt-1],seq[begin+cnt]);
//        }
//        cnt++;
//    }
//    return k_arr;
//}
//long count(long value,long** count_arr,long len){
//    long count=0;
//    for (long i = 0; i <len ; ++i) {
//        for (long j = 0; j <len ; ++j) {
//            if(count_arr[i][j]==value){
//                count++;
//            }
//        }
//    }
//    return count;
//}


int main() {
    long N;
    long M;
    cin >> N;
    long *seq = new long[N];
    for (long i = 0; i < N; ++i) {
        cin >> seq[i];
    }
    cin >> M;
    long *m_seq = new long[M];
    for (long j = 0; j < M; ++j) {
        cin >> m_seq[j];
    }

    hash_map gcd_hash;

    for (int k1 = 0; k1 < N; ++k1) {
        long temp_k0 = seq[k1];
        //hash_add(hash_table,temp_k0);
        for (int k2 = k1; k2 < N; ++k2) {
            long temp_gcd = gcd(seq[k2], temp_k0);
            if (temp_gcd == 1) {
                gcd_hash.set_value(1,N-k2);
                break;
            }
            gcd_hash.set_value(temp_gcd,1);
            temp_k0 = temp_gcd;
        }
    }
    for (int l = 0; l < M; ++l) {
        cout << gcd_hash.get_value(m_seq[l])<< " ";
    }
    return 0;

}

