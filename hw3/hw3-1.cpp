#include <iostream>
using namespace std;

class Min_Heap {
public:
    long *Main_array;
    long cur_size=0;
    long max_size;

    Min_Heap(long max_size);

    ~Min_Heap();

    void percolate(long index);

    void raw_push(long element);

    void maintain_up(long index);

    void stable_pop();

    long top();

    void renormalize(long cost,long temp_index);
};

Min_Heap::Min_Heap(long m) : max_size(m) {
    Main_array = new long[max_size + 1];
}

Min_Heap::~Min_Heap() {
    delete[]Main_array;  // necessary empty()
}


void Min_Heap::raw_push(long element) {
//    if (!is_full()) {
    cur_size++;
    Main_array[cur_size] = element;
    //}
}

void Min_Heap::percolate(long index) {

    while (index < cur_size) {
        long child_index;
        if(index*2+1<=cur_size){
            child_index = Main_array[2 * index+1] < Main_array[2 * index] ? 2 * index + 1 : 2 * index;
            if(Main_array[index]>Main_array[child_index]){
                swap(Main_array[index],Main_array[child_index]);
                index=child_index;}
            else{ break;}
        }
        else if (index*2==cur_size && index*2+1>cur_size){
            child_index=index*2;
            if(Main_array[index]>Main_array[child_index]){
                swap(Main_array[index],Main_array[child_index]);
                index=child_index;}
            else{ break;}
        }
        else{ break;}
    }
}

long Min_Heap::top() {
    return Main_array[1];
}


void Min_Heap::maintain_up(long index){
    long temp_index = index;
    while (temp_index > 1) {
        if (Main_array[temp_index] < Main_array[temp_index >>1]) {
            long parent_index;
            parent_index = temp_index >> 1;
            swap(Main_array[temp_index], Main_array[parent_index]);
            temp_index = parent_index;
        }
        else { break; }
    }
}


void Min_Heap::stable_pop(){
    if(cur_size>1){
        swap(Main_array[cur_size], Main_array[1]);
        Main_array[cur_size]=999999;
        cur_size--;
        percolate(1);} else{cur_size--;}
    //    if (cur_size > 1 ) {
//        for (long i = cur_size / 2; i > 0; i--) {
//            percolate(i);
//        }
    //}
}

int main(){
    long iter_times;
    long cost_sum=0;
    long * cost_value_set;
    long * gpu_set;
    //long rest_gpu;
    cin>>iter_times;
    cost_value_set=new long[iter_times];
    gpu_set=new long[iter_times];
    Min_Heap cost_heap(iter_times);
    for(long j=0;j<iter_times;j++){
        cin>>gpu_set[j];
    }
    for (long k=0;k<iter_times;k++){
        cin>>cost_value_set[k];
    }
    for (long x=0;x<iter_times;x++){
        cost_sum=0;
        cost_heap.raw_push(gpu_set[x]);
        cost_heap.maintain_up(cost_heap.cur_size);
        //rest_gpu=cost_heap.cur_size;
        for(long y=1;y<cost_heap.cur_size+1;y++){
            cost_heap.Main_array[y]-=cost_value_set[x];
        }
        //cost_heap.malongain_up(cost_heap.cur_size);
        while(cost_heap.top()<0){
            cost_sum+=cost_heap.top()+cost_value_set[x];
            cost_heap.stable_pop();
            if(cost_heap.cur_size==0){ break;}
        }
        cost_sum+=cost_heap.cur_size*cost_value_set[x];
        cout<<cost_sum<<" ";
    }
    return 0;

};