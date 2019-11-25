#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    long vex_out;
    long vex_in;
    long weight;
    long vex_in_ord = -1;
    long vex_out_ord = -1;

    Node(long v1, long v2, long w);
};

Node::Node(long v1, long v2, long w) : vex_out(v1), vex_in(v2), weight(w) {}

class Min_Heap {
public:
    Node **Main_array;
    long cur_size = 0;
    long max_size;

    Min_Heap(long max_size);

    ~Min_Heap();

    void percolate(long index);

    void stable_push(Node *element);

    void malongain_up(long index);

    void stable_pop();

    Node *top();

};

Min_Heap::Min_Heap(long m) : max_size(m) {
    Main_array = new Node *[max_size + 1];
}

Min_Heap::~Min_Heap() {
    delete[]Main_array;  // necessary empty()
}


void Min_Heap::stable_push(Node *element) {
//    if (!is_full()) {
    cur_size++;
    Main_array[cur_size] = element;
    malongain_up(cur_size);
    //}
}

void Min_Heap::percolate(long index) {

    while (index < cur_size) {
        long child_index;
        if (index * 2 + 1 <= cur_size) {
            child_index = Main_array[2 * index + 1]->weight < Main_array[2 * index]->weight ? 2 * index + 1 : 2 * index;
            if (Main_array[index]->weight > Main_array[child_index]->weight) {
                swap(Main_array[index], Main_array[child_index]);
                index = child_index;
            } else { break; }
        } else if (index * 2 == cur_size && index * 2 + 1 > cur_size) {
            child_index = index * 2;
            if (Main_array[index]->weight > Main_array[child_index]->weight) {
                swap(Main_array[index], Main_array[child_index]);
                index = child_index;
            } else { break; }
        } else { break; }
    }
}

Node *Min_Heap::top() {
    return Main_array[1];
}


void Min_Heap::malongain_up(long index) {
    long temp_index = index;
    while (temp_index > 1) {
        if (Main_array[temp_index]->weight < Main_array[temp_index >> 1]->weight) {
            long parent_index;
            parent_index = temp_index >> 1;
            swap(Main_array[temp_index], Main_array[parent_index]);
            temp_index = parent_index;
        } else { break; }
    }
}


void Min_Heap::stable_pop() {
    if (cur_size > 1) {
        swap(Main_array[cur_size], Main_array[1]);
        //Main_array[cur_size]=NULL;
        cur_size--;
        percolate(1);
    } else { cur_size--; }
    //    if (cur_size > 1 ) {
//        for (long i = cur_size / 2; i > 0; i--) {
//            percolate(i);
//        }

}

class Graph {
public:
    long vex_num;
    long edge_num;
    long **Graph_Matrix;
    long **Insert_Matrix;

    Graph(long v, long e);

    ~Graph();

    void Floyd();
};

Graph::Graph(long v, long e) : vex_num(v), edge_num(e) {
    Graph_Matrix = new long *[v];
    Insert_Matrix = new long *[v];
    for (long i = 0; i < v; i++) {
        Graph_Matrix[i] = new long[v];
        Insert_Matrix[i] = new long[v];
    }
    for (long j = 0; j < v; ++j) {
        for (long i = 0; i < v; ++i) {
            if (i != j) {
                Graph_Matrix[j][i] = 1000000001;
                Insert_Matrix[j][i] = 1000000001;
            } else {
                Graph_Matrix[j][i] = 0;
                Insert_Matrix[j][i] = 0;
            }
        }
    }
}

Graph::~Graph() {
    delete[]Graph_Matrix;
    delete[]Insert_Matrix;
}

void Graph::Floyd() {
    for (long k = 0; k < vex_num; ++k) {
        for (long i = 0; i < vex_num; ++i) {
            for (long j = 0; j < vex_num; ++j) {
                if (Graph_Matrix[i][j] > Graph_Matrix[i][k] + Graph_Matrix[k][j]) {
                    Insert_Matrix[i][j] = Insert_Matrix[i][k];
                    Graph_Matrix[i][j] = Graph_Matrix[i][k] + Graph_Matrix[k][j];
                }
            }
        }
    }
}


void quickSort(long s[], long l, long r) {
    if (l < r) {
        long i = l, j = r, x = s[l];
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

int main() {
    long vex_N;
    long edge_M;
    long final_K;
    Node **node_array;
    Node **mid_array;
    cin >> vex_N >> edge_M >> final_K;
    Min_Heap k_heap(2 * edge_M);
    node_array = new Node *[2 * edge_M];
    for (long l = 0; l < edge_M; l++) {
        long x, y, w;
        cin >> x >> y >> w;
        node_array[2 * l] = new Node(x, y, w);
        node_array[2 * l + 1] = new Node(y, x, w);
        k_heap.stable_push(node_array[2 * l]);
        k_heap.stable_push(node_array[2 * l + 1]);
    }
    for (long l = 0; l < 2 * edge_M; l++) {
        k_heap.stable_pop();
    }
    mid_array = new Node *[2 * final_K];
    long count = 0;
    for (long k = 2 * edge_M; k > 2 * (edge_M - final_K); k--) {
        mid_array[count] = k_heap.Main_array[k];
        count++;
    }

//    //
//    for (int n = 0; n < 2*final_K; ++n) {
//        cout<<mid_array[n]->weight<<" "<<mid_array[n]->vex_in<<" "<<mid_array[n]->vex_out<<endl;
//    }
//    //

    long *count_array = new long[2 * final_K];
    for (long l = 0; l < 2*final_K; l++) {
        count_array[l] = mid_array[l]->vex_in;
    }
    quickSort(count_array,0,2*final_K-1);
//    for (long i = 0; i < 4 * final_K; ++i) {
//        for (long j = i; j < 4 * final_K; ++j) {
//            if (count_array[i] > count_array[j]) {
//                swap(count_array[i], count_array[j]);
//            }
//        }
//    }
    long final_vex = unique(count_array, count_array + 2 * final_K) - count_array;
//    //
//    for (int i1 = 0; i1 < 2*final_K; ++i1) {
//        cout<<count_array[i1]<<" ";
//    }
//    //
    for (long i = 0; i < 2 * final_K; ++i) {
        for (long j = i; j < 2 * final_K; ++j) {
            if (mid_array[i]->vex_in > mid_array[j]->vex_in) {
                swap(mid_array[i], mid_array[j]);
            }
        }
    }
//    //
//    for (int n = 0; n <2*final_K ; ++n) {
//        cout<<mid_array[n]->vex_in<<" "<<mid_array[n]->weight<<"    ";
//    }
//    cout<<"\n";
//    //
    long in2 = 0, out2 = 0;
    for (long in1 = 0; in1 < 2 * final_K; ++in1) {
        if (in1 != 2 * final_K - 1) {
            if (mid_array[in1]->vex_in != mid_array[in1 + 1]->vex_in) {
                mid_array[in1]->vex_in_ord = in2;
                in2++;
            }
            else { mid_array[in1]->vex_in_ord = in2; }
        }
        else { mid_array[in1]->vex_in_ord = in2; }
    }


    for (long i = 0; i < 2 * final_K; ++i) {
        for (long j = i; j < 2 * final_K; ++j) {
            if (mid_array[i]->vex_out > mid_array[j]->vex_out) {
                swap(mid_array[i], mid_array[j]);
            }
        }
    }

    for (long out1 = 0; out1 < 2 * final_K; ++out1) {
        if (out1 != 2 * final_K - 1) {
            if (mid_array[out1]->vex_out != mid_array[out1 + 1]->vex_out) {
                mid_array[out1]->vex_out_ord = out2;
                out2++;
            } else { mid_array[out1]->vex_out_ord = out2; }
        } else { mid_array[out1]->vex_out_ord = out2; }
    }

    Graph final_matrix(final_vex, final_K);
    for (long m3 = 0; m3 < 2 * final_K; ++m3) {
        final_matrix.Graph_Matrix[mid_array[m3]->vex_in_ord][mid_array[m3]->vex_out_ord] = mid_array[m3]->weight;
        final_matrix.Insert_Matrix[mid_array[m3]->vex_in_ord][mid_array[m3]->vex_out_ord] = mid_array[m3]->vex_out_ord;
    }
    final_matrix.Floyd();
//    //
//    for (long n = 0; n <final_vex ; ++n) {
//        for (long i = 0; i <final_vex ; ++i) {
//            cout<<final_matrix.Graph_Matrix[n][i]<<"  ";
//        }
//        cout<<endl;
//    }
//    cout<<"\n";
//    //
    long *final_sort_array = new long[(final_vex) * (final_vex + 1) / 2];
    int temp_count=0;
    for (long m = 0; m < final_vex; ++m) {
        for (long i = m + 1; i < final_vex; ++i) {
            final_sort_array[temp_count] = final_matrix.Graph_Matrix[m][i];
            temp_count++;
        }
    }
    quickSort(final_sort_array, 0, (final_vex) * (final_vex - 1) / 2-1);
//    //
//    cout<<"\n";
//    for (int j1 = 0; j1 <final_vex*(final_vex-1)/2 ; ++j1) {
//        cout<<final_sort_array[j1]<<' ';
//    }
//    cout<<"\n";
//    //

    unique(final_sort_array, final_sort_array + (final_vex) * (final_vex - 1) / 2);
    cout << final_sort_array[final_K-1] << endl;
    return 0;
//    for (long i = 0; i < (final_vex)*(final_vex-1)/2; ++i) {
//        for (long j = i; j < (final_vex)*(final_vex-1)/2; ++j) {
//            if(final_sort_array[i]>final_sort_array[j]){
//                swap(final_sort_array[i],final_sort_array[j]);
//            }
//        }
//    }


//    for (long n = 0; n <final_vex ; ++n) {
//        for (long i = 0; i <final_vex ; ++i) {
//            cout<<final_matrix.Insert_Matrix[n][i]<<"  ";
//        }
//        cout<<endl;
//    }
//    cout<<"\n";

//    for (long n = 0; n <(final_vex)*(final_vex-1)/2; ++n) {
//            cout<<final_sort_array[n]<<"  ";
//    }
//
//    cout<<endl;
//    cout<<"\n";
//    cout<< sizeof(node_array)<<" "<<final_vex*final_vex<<" "<<final_vex*(final_vex+1)/2<<' '<< sizeof(final_sort_array)/
//                                                                                               sizeof(final_sort_array[0])<<" "<< sizeof(mid_array);

};


//quickSort(final_sort_array,0,(final_vex)*(final_vex+1)/2);